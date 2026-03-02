#ifndef KLIB_KONGKONG_THREADING_SCOPEDLOCK_H
#define KLIB_KONGKONG_THREADING_SCOPEDLOCK_H

#include "base.h"
#include "Kongkong.Threading.Mutex.h"

namespace klib::Kongkong::Threading
{
    class ScopedLock final {
        private:
        Mutex* m_pMutex;

        public:

        constexpr ScopedLock(
            Mutex& mutex
        ) noexcept;

        ScopedLock(
            ScopedLock const&
        ) = delete;

        ~ScopedLock();

        ScopedLock& operator=(
            ScopedLock const&
        ) = delete;
    };
}

namespace klib::Kongkong::Threading
{
    constexpr ScopedLock::ScopedLock(
        Mutex& mutex
    ) noexcept
        : m_pMutex(&mutex)
    {
        mutex.Lock();
    }

    inline ScopedLock::~ScopedLock()
    {
        m_pMutex->Unlock();
    }
}

#endif //!KLIB_KONGKONG_THREADING_SCOPEDLOCK_H