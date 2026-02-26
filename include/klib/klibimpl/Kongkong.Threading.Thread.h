#ifndef KLIB_KONGKONG_THRAEDING_THREAD_H
#define KLIB_KONGKONG_THRAEDING_THREAD_H

#include "base.h"
#include "Kongkong.Win32.Win32Handle.h"
#include "Kongkong.Threading.ThreadExitCode.h"

namespace klib::Kongkong::Threading
{
    class Thread final {
        private:
#if KLIB_ENV_WINDOWS
        Win32::Win32Handle m_thread;

        constexpr Thread(
            ::HANDLE rawHandle
        ) noexcept;
#elif KLIB_ENV_UNIX

#endif
        public:

        [[nodiscard]]
        static Thread Current() noexcept;

        static void Sleep(
            uint32_t milliSeconds
        ) noexcept;

        [[nodiscard]]
        ThreadExitCode ExitCode() noexcept;

        [[nodiscard]]
        bool GetExitCode(
            int& result
        ) noexcept;

        [[nodiscard]]
        int GetExitCodeUnsafe() noexcept;

        void Join();

        void Join(
            uint32_t milliSeconds
        );

        void Start();
    };
}

namespace klib::Kongkong::Threading
{
#if KLIB_ENV_WINDOWS
    
    inline Thread Thread::Current() noexcept
    {
        return Thread(
            ::GetCurrentThread()
        );
    }

    inline void Thread::Sleep(
        uint32_t milliSeconds
    ) noexcept
    {
        ::Sleep(
            static_cast<::DWORD>(milliSeconds)
        );
    }

    constexpr Thread::Thread(
        ::HANDLE rawHandle
    ) noexcept
        : m_thread(rawHandle)
    {
    }

    inline bool Thread::GetExitCode(
        int& result
    ) noexcept
    {
        ::DWORD exitCode;
        ::BOOL r = ::GetExitCodeThread(
            m_thread.RawHandle(),
            &exitCode
        );

        if (r == FALSE) return false;

        result = static_cast<int>(exitCode);

        return true;
    }

    inline int Thread::GetExitCodeUnsafe() noexcept
    {
        ::DWORD exitCode;
        ::GetExitCodeThread(
            m_thread.RawHandle(),
            &exitCode
        );

        return static_cast<int>(exitCode);
    }
#endif
    inline ThreadExitCode Thread::ExitCode() noexcept
    {
        ThreadExitCode exitCode;

        exitCode.Success = GetExitCode(
            exitCode.Code
        );

        return exitCode;
    }

    

    inline void Thread::Join()
    {
        Join(static_cast<uint32_t>(-1));
    }
}

#endif //!KLIB_KONGKONG_THRAEDING_THREAD_H