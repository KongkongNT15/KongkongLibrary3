#ifndef KLIB_KONGKONG_THRAEDING_THREAD_H
#define KLIB_KONGKONG_THRAEDING_THREAD_H

#include "base.h"
#include "Kongkong.Win32.Win32Handle.h"

namespace klib::Kongkong::Threading
{
    class Thread final {
        private:
#if KLIB_ENV_WINDOWS
        Win32::Win32Handle m_thread;
#elif KLIB_ENV_UNIX

#endif
        public:

        static void Sleep(
            uint32_t milliSeconds
        ) noexcept;

        void Join();

        void Start();
    };
}

namespace klib::Kongkong::Threading
{
    inline void Thread::Sleep(
        uint32_t milliSeconds
    ) noexcept
    {
#if KLIB_ENV_WINDOWS
        ::Sleep(
            static_cast<::DWORD>(milliSeconds)
        );
#elif KLIB_ENV_UNIX

#endif
    }
}

#endif //!KLIB_KONGKONG_THRAEDING_THREAD_H