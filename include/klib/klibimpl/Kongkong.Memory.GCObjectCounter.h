#ifndef KLIB_KONGKONG_MEMORY_GCOBJECTCOUNTER_H
#define KLIB_KONGKONG_MEMORY_GCOBJECTCOUNTER_H

#include "base.h"
#include <atomic>

namespace klib::Kongkong::Memory
{
    struct GCObjectCounter {
    private:
        ::std::atomic<ssize_t> m_activeCount;

        /// <summary>
        /// 参照カウント
        /// </summary>
        ::std::atomic<ssize_t> m_referenceCount;
    public:
    };
}

#endif //!KLIB_KONGKONG_MEMORY_GCOBJECTCOUNTER_H