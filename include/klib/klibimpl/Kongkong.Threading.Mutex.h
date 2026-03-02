#ifndef KLIB_KONGKONG_THREADING_MUTEX_H
#define KLIB_KONGKONG_THREADING_MUTEX_H

#include "base.h"

#if KLIB_ENV_WINDOWS
    #include "Kongkong.Win32.Win32Handle.h"
#elif KLIB_ENV_UNIX

#endif

namespace klib::Kongkong::Threading
{
    class Mutex final {
        private:

#if KLIB_ENV_WINDOWS
        Win32::Win32Handle m_mutex;
#elif KLIB_ENV_UNIX

#endif

        public:

        Mutex() noexcept;

        bool Lock() noexcept;

        bool Unlock() noexcept;

    };
}

namespace klib::Kongkong::Threading
{
#if KLIB_ENV_WINDOWS
    inline Mutex::Mutex() noexcept
        : m_mutex(::CreateMutexW(nullptr, FALSE, nullptr))
    {
    }

    inline bool Mutex::Lock() noexcept
    {
        return static_cast<bool>(
            ::WaitForSingleObject(m_mutex.RawHandle(), INFINITE)
        );
    }

    inline bool Mutex::Unlock() noexcept
    {
        return static_cast<bool>(
            ::ReleaseMutex(m_mutex.RawHandle())
        );
    }

#elif KLIB_ENV_UNIX

#endif
}

#endif //!KLIB_KONGKONG_THREADING_MUTEX_H