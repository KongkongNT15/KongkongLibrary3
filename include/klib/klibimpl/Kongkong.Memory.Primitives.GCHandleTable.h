#ifndef KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLETABLE_H
#define KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLETABLE_H

#include "base.h"
#include "Kongkong.Containers.PagedList.h"
#include "Kongkong.Memory.MemoryAddress.h"
#include "Kongkong.Memory.Primitives.GCHandleEntry.h"
#include "Kongkong.Memory.Primitives.GCObject.h"
#include "Kongkong.Memory.VirtualMemoryRegion.h"
#include "Kongkong.Threading.Mutex.h"
#include "Kongkong.Threading.ScopedLock.h"

#include <atomic>

namespace klib::Kongkong::Memory::Primitives
{
    struct GCHandleTable final {
        private:

        Containers::PagedList<::std::atomic<GCHandleEntry>> m_entries;
        Containers::PagedList<ssize_t> m_freeList;

        Threading::Mutex m_freeListMutex;

        static void do_relocateObject(
            GCObject<>&& oldValue,
            GCObject<>* newPtr
        ) noexcept;

        static void do_rollbackRelocation(
            GCObject<>* oldPtr,
            GCObject<>* newPtr
        ) noexcept;

        void do_returnIndices(
            const uint32_t* indices,
            size_t count
        );

        void do_unmarkHandle(
            ssize_t index
        ) noexcept;

        public:

        explicit GCHandleTable(
            ssize_t maxHandleCount
        );

        [[nodiscard]]
        void* GetObjectUnsafe(
            ssize_t index
        ) noexcept;

        void MarkHandleUnsafe(
            ssize_t index
        ) noexcept;

        void SweepAndCompact(
            VirtualMemoryRegion& heap
        );

        bool TryRelocateUnsafe(
            ssize_t index,
            void* oldObjectPtr,
            void* newObjectPtr
        ) noexcept;
    };
}

namespace klib::Kongkong::Memory::Primitives
{
    inline void GCHandleTable::do_relocateObject(
        GCObject<>&& oldValue,
        GCObject<>* newPtr
    ) noexcept
    {
        
        new(newPtr) GCObject<>(::std::move(oldValue));
    }

    inline void GCHandleTable::do_returnIndices(
        const uint32_t* indices,
        size_t count
    )
    {
        Threading::ScopedLock lock(m_freeListMutex);
        for (size_t i = 0; i < count; ++i) {
            // 解放前にエントリをクリアしておくのが安全ですｳﾋｮｯ
            m_entries[indices[i]].store(
                {
                    nullptr,
                    0,
                    0,
                    GCObjectFlag::Normal
                },
                std::memory_order_relaxed
            );

            m_freeList.Append(indices[i]);
        }
    }

    void GCHandleTable::do_unmarkHandle(
        ssize_t index
    ) noexcept
    {
        auto& entry = m_entries[index];
        GCHandleEntry expected = entry.load(::std::memory_order_relaxed);
        
        while (true) {

            // 既にマーク済みなら何もしないｳﾋｮｯ
            if (!(expected.Flags & GCObjectFlag::Marked)) {
                return;
            }

            using baseType = ::std::underlying_type_t<decltype(expected.Flags)>;
            GCHandleEntry desired = expected;

            {
                baseType v = static_cast<baseType>(desired.Flags);
                baseType hanten = ~static_cast<baseType>(GCObjectFlag::Marked);

                baseType newValue = v & hanten;

                desired.Flags = static_cast<GCObjectFlag>(newValue);
            }

            // 16バイトCASでフラグを更新ｳﾋｮｯ
            if (
                entry.compare_exchange_weak(
                    expected,
                    desired,
                    ::std::memory_order_release,
                    ::std::memory_order_acquire
                )
            ) {
                return; // マーク成功ｳﾋｮｯ
            }
            // 失敗（他スレッドが更新した）場合は、最新の expected でリトライｳﾋｮｯ
        }
    }

    GCHandleTable::GCHandleTable(
        ssize_t maxHandleCount
    )
    {
        m_entries.ReserveUnsafe(maxHandleCount);
        m_freeList.ReserveUnsafe(maxHandleCount);
    }

    inline void* GCHandleTable::GetObjectUnsafe(
        ssize_t index
    ) noexcept
    {
        return m_entries[index]
            .load(::std::memory_order_acquire)
            .ObjectPtr;
    }

    // Geminiが作ったよ！
    inline void GCHandleTable::MarkHandleUnsafe(
        ssize_t index
    ) noexcept
    {
        auto& entry = m_entries[index];
        GCHandleEntry expected = entry.load(::std::memory_order_relaxed);
        
        while (true) {

            // 既にマーク済みなら何もしないｳﾋｮｯ
            if (expected.Flags & GCObjectFlag::Marked) {
                return;
            }
            
            GCHandleEntry desired = expected;
            desired.Flags |= GCObjectFlag::Marked; // マークビットを立てるｳﾋｮｯ

            // 16バイトCASでフラグを更新ｳﾋｮｯ
            if (
                entry.compare_exchange_weak(
                    expected,
                    desired,
                    ::std::memory_order_release,
                    ::std::memory_order_acquire
                )
            ) {
                return; // マーク成功ｳﾋｮｯ
            }
            // 失敗（他スレッドが更新した）場合は、最新の expected でリトライｳﾋｮｯ
        }
    }

    inline void GCHandleTable::SweepAndCompact(
        VirtualMemoryRegion& heap
    )
    {
        GCObject<>* nextObject = static_cast<GCObject<>*>(heap.Data()); // 移動先の先頭アドレスｳﾋｮｯ

        // 全てのハンドルエントリを走査しますｳﾋｮｯ
        for (uint32_t i = 0; i < m_entries.Length(); ++i) {
            auto& entry = m_entries[i];
            GCHandleEntry current = entry.load(::std::memory_order_acquire);
            GCObject<>* currentObject = current.GetObject();

            // 1. 生きていない（マークなし）ハンドルの回収ｳﾋｮｯ
            if (!(current.Flags & GCObjectFlag::Marked)) {
                if (current.ObjectPtr != nullptr) {
                    // デストラクタを呼び、インデックスをフリーリストへ返却ｳﾋｮｯ
                    currentObject->~GCObject();
                    do_returnIndices(&i, 1); 
                }
                continue;
            }

            // 2. ピン留め（Pinned）のチェックｳﾋｮｯ
            if (current.Flags & GCObjectFlag::Pinned) {
                // ピン留めされている場合は移動させず、次の空き位置を更新するだけｳﾋｮｯ
                nextObject = currentObject->Next();
                // 次回のためにマークだけ外しておくｳﾋｮｯ
                do_unmarkHandle(i);
                continue;
            }

            // 3. 移動（リロケーション）の実行ｳﾋｮｯ
            GCObject<>* oldPtr = currentObject;
            GCObject<>* newPtr = nextObject;

            if (oldPtr != newPtr) {
                // 型固有のムーブ関数を使用して実体を移動させますｳﾋｮｯ
                do_relocateObject(::std::move(*oldPtr), newPtr);

                // 16バイトCASでハンドルテーブルを更新ｳﾋｮｯ
                // 失敗した場合はユーザーがピン留めした可能性があるので、元の位置に戻す等のケアが必要ｳﾋｮｯ
                if (!TryRelocateUnsafe(i, oldPtr, newPtr)) {
                    do_rollbackRelocation(oldPtr, newPtr);
                }
            }

            // 次のオブジェクトを置く位置を進めるｳﾋｮｯ
            nextObject = nextObject->Next();
            
            // 次回のGCのためにマークをクリアするｳﾋｮｯ
            do_unmarkHandle(i);
        }
    }

    inline bool GCHandleTable::TryRelocateUnsafe(
        ssize_t index,
        void* oldObjectPtr,
        void* newObjectPtr
    ) noexcept
    {
        auto& entry = m_entries[index];

        GCHandleEntry expected = entry.load(
            std::memory_order_relaxed
        );

        if (
            expected.ObjectPtr != oldObjectPtr
            || (expected.Flags & GCObjectFlag::Pinned)
        ) {
            return false; // 他の理由で移動できない場合は失敗ｳﾋｮｯ
        }

        GCHandleEntry desired = expected;
        desired.ObjectPtr = newObjectPtr;

        // DWCAS（16バイトCAS）で一気にポインタを書き換えますｳﾋｮｯ
        return entry.compare_exchange_strong(
            expected,
            desired,
            ::std::memory_order_release,
            ::std::memory_order_acquire
        );
    }
}

#endif //!KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLETABLE_H