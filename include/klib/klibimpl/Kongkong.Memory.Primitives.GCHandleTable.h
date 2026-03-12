#ifndef KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLETABLE_H
#define KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLETABLE_H

#include "base.h"
#include "Kongkong.Memory.Primitives.GCHandleEntry.h"
#include "Kongkong.Threading.Mutex.h"

#include <vector>
#include <list>
#include <atomic>

namespace klib::Kongkong::Memory::Primitives
{
    struct GCHandleTable final {
        private:

        ::std::vector<::std::atomic<GCHandleEntry>> m_entries;
        ::std::vector<ssize_t> m_freeList;

        Threading::Mutex m_freeListMutex;

        public:

        explicit GCHandleTable(
            ssize_t maxHandleCount
        );
    };
}

#endif //!KLIB_KONGKONG_MEMORY_PRIMITIVES_GCHANDLETABLE_H