#ifndef KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLETABLE_H
#define KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLETABLE_H

#include "base.h"
#include "Kongkong.Containers.PagedList.h"
#include "Kongkong.Memory.Primitives.GCHandleEntry.h"
#include "Kongkong.Threading.Mutex.h"

#include <atomic>

namespace klib::Kongkong::Memory::Primitives
{
    struct GCHandleTable final {
        private:

        Containers::PagedList<::std::atomic<GCHandleEntry>> m_entries;
        Containers::PagedList<ssize_t> m_freeList;

        Threading::Mutex m_freeListMutex;

        public:

        explicit GCHandleTable(
            ssize_t maxHandleCount
        );

        [[nodiscard]]
        void* GetObjectUnsafe(
            ssize_t index
        ) noexcept;

        bool TryRelocateUnsafe(
            ssize_t index,
            void* oldObjectPtr,
            void* newObjectPtr
        ) noexcept;
    };
}

namespace klib::Kongkong::Memory::Primitives
{
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