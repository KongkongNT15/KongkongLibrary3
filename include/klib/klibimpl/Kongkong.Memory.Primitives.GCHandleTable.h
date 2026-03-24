#ifndef KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLETABLE_H
#define KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLETABLE_H

#include "base.h"
#include "Kongkong.Containers.PagedList.h"
#include "Kongkong.Memory.Primitives.GCHandleEntry.h"
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

        [[nodiscard]]
        static constexpr uintptr_t do_alignUp(
            uintptr_t addr,
            size_t alignment
        ) noexcept;

        [[nodiscard]]
        constexpr void* do_computeNextPos(
            void* objectPtr
        ) const noexcept;

        static void do_destroyObject(
            void* objectPtr
        ) noexcept;

        static void do_relocateObject(
            void* oldPtr,
            void* newPtr
        ) noexcept;

        void do_returnIndices(
            const uint32_t* indices,
            size_t count
        );

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
    constexpr uintptr_t GCHandleTable::do_alignUp(
        uintptr_t addr,
        size_t alignment
    ) noexcept
    {
        return (addr + (alignment - 1)) & ~(alignment - 1);
    }

    constexpr void* GCHandleTable::do_computeNextPos(
        void* objectPtr
    ) const noexcept
    {
        GCObjectHeader<>* header = static_cast<GCObjectHeader<>*>(objectPtr) - 1;
    
        // 現在のオブジェクトの末尾アドレスｳﾋｮｯ
        uintptr_t current_end = reinterpret_cast<uintptr_t>(objectPtr) + header->Size();
        
        // 次の「ヘッダー」が要求するアラインメント（例：16バイト）で切り上げｳﾋｮｯ
        uintptr_t next_header_start = do_alignUp(current_end, alignof(GCObjectHeader<>));
        
        // 次の「オブジェクト実体」の位置を返す（ヘッダー直後とは限らない）ｳﾋｮｯ
        GCObjectHeader<>* next_header = reinterpret_cast<GCObjectHeader<>*>(next_header_start);
        
        // 次のオブジェクトのアラインメントに合わせてオフセットを計算ｳﾋｮｯ
        uintptr_t next_obj_start = do_alignUp(
            next_header_start + sizeof(GCObjectHeader<>),
            next_header->Alignment()
        );
        
        return reinterpret_cast<void*>(next_obj_start);
    }

    inline void GCHandleTable::do_destroyObject(
        void* objectPtr
    ) noexcept
    {
        GCObjectHeader<>* header = static_cast<GCObjectHeader<>*>(objectPtr) - 1;

        header->Destruct(objectPtr);
    }

    inline void GCHandleTable::do_relocateObject(
        void* oldPtr,
        void* newPtr
    ) noexcept
    {
        GCObjectHeader<>* old_header = static_cast<GCObjectHeader<>*>(oldPtr) - 1;
        GCObjectHeader<>* new_header = static_cast<GCObjectHeader<>*>(newPtr) - 1;
        
        // ヘッダー情報をコピー（ヘッダー自体は単純コピーでOK）ｳﾋｮｯ
        *new_header = *old_header;
    
    // 型固有のムーブ関数を呼び出して、実体を移動させますｳﾋｮｯ
        old_header->MoveConstruct(oldPtr, newPtr);
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
                {nullptr, 0, GCObjectFlag::Normal},
                std::memory_order_relaxed
            );

            m_freeList.Append(indices[i]);
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
        void* nextFreePos = heap.Data(); // 移動先の先頭アドレスｳﾋｮｯ

        // 全てのハンドルエントリを走査しますｳﾋｮｯ
        for (uint32_t i = 0; i < m_entries.Length(); ++i) {
            auto& entry = m_entries[i];
            GCHandleEntry current = entry.load(::std::memory_order_acquire);

            // 1. 生きていない（マークなし）ハンドルの回収ｳﾋｮｯ
            if (!(current.Flags & GCObjectFlag::Marked)) {
                if (current.ObjectPtr != nullptr) {
                    // デストラクタを呼び、インデックスをフリーリストへ返却ｳﾋｮｯ
                    do_destroyObject(current.ObjectPtr); 
                    do_returnIndices(&i, 1); 
                }
                continue;
            }

            // 2. ピン留め（Pinned）のチェックｳﾋｮｯ
            if (current.Flags & GCObjectFlag::Pinned) {
                // ピン留めされている場合は移動させず、次の空き位置を更新するだけｳﾋｮｯ
                nextFreePos = do_computeNextPos(current.ObjectPtr);
                // 次回のためにマークだけ外しておくｳﾋｮｯ
                unmark_handle(i);
                continue;
            }

            // 3. 移動（リロケーション）の実行ｳﾋｮｯ
            void* oldPtr = current.ObjectPtr;
            void* newPtr = nextFreePos;

            if (oldPtr != newPtr) {
                // 型固有のムーブ関数を使用して実体を移動させますｳﾋｮｯ
                do_relocateObject(oldPtr, newPtr);

                // 16バイトCASでハンドルテーブルを更新ｳﾋｮｯ
                // 失敗した場合はユーザーがピン留めした可能性があるので、元の位置に戻す等のケアが必要ｳﾋｮｯ
                if (!TryRelocateUnsafe(i, oldPtr, newPtr)) {
                    rollback_relocation(newPtr, oldPtr);
                }
            }

            // 次のオブジェクトを置く位置を進めるｳﾋｮｯ
            nextFreePos = do_computeNextPos(newPtr);
            
            // 次回のGCのためにマークをクリアするｳﾋｮｯ
            unmark_handle(i);
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