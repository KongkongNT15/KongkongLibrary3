#ifndef KLIB_THRAEDING_THREAD_H
#define KLIB_THRAEDING_THREAD_H

#include "base.h"
#include "Foundation.HandleType.h"

#if KLIB_ENV_WINDOWS
    #include "Win32.Win32Handle.h"
#elif KLIB_OBJECTIVE_C_ENABLED
    #include "AppleDevice.ObjCHandle.h"
#elif KLIB_ENV_UNIX

#endif

#include "Functional.Function.h"
#include "Threading.ThreadExitCode.h"
#include "Threading.ThreadState.h"

namespace klib::Threading
{
    class Thread final : public Foundation::HandleType {
        private:
        static uint32_t s_threadCount;

#if KLIB_ENV_WINDOWS

        static ::DWORD __stdcall EntryPoint(
            void* args
        );

        Win32::Win32Handle m_thread;

        constexpr Thread(
            ::HANDLE rawHandle
        ) noexcept;

#elif KLIB_OBJECTIVE_C_ENABLED
        AppleDevice::ObjCHandle m_thread;

        constexpr Thread(
            AppleDevice::ObjCHandle&& thread
        ) noexcept;
#elif KLIB_ENV_UNIX
        ::pthread_t m_thread;
#endif

        Functional::Function<void()> m_entryPoint;

        public:

        [[nodiscard]]
        static Thread Current() noexcept;

        static void Sleep(
            uint32_t milliSeconds
        ) noexcept;

        Thread(
            Functional::Function<void()>&& entryPoint
        );

        Thread(
            Functional::Function<void()>&& entryPoint,
            size_t stackSize
        );

        [[nodiscard]]
        ThreadExitCode ExitCode() noexcept;

        [[nodiscard]]
        bool GetExitCode(
            int& result
        ) noexcept;

        [[nodiscard]]
        int GetExitCodeUnsafe() noexcept;

        [[nodiscard]]
        int Id() const noexcept;

        void Join();

        void Join(
            uint32_t milliSeconds
        );

        void Start();
    };

    [[nodiscard]]
    bool operator==(
        Thread const& left,
        Thread const& right
    ) noexcept;

    [[nodiscard]]
    bool operator!=(
        Thread const& left,
        Thread const& right
    ) noexcept;

    [[nodiscard]]
    bool operator<(
        Thread const& left,
        Thread const& right
    ) noexcept;

    [[nodiscard]]
    bool operator<=(
        Thread const& left,
        Thread const& right
    ) noexcept;

    [[nodiscard]]
    bool operator>(
        Thread const& left,
        Thread const& right
    ) noexcept;

    [[nodiscard]]
    bool operator>=(
        Thread const& left,
        Thread const& right
    ) noexcept;

    [[nodiscard]]
    ::std::strong_ordering operator<=>(
        Thread const& left,
        Thread const& right
    ) noexcept;
}

namespace klib::Threading
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

    inline int Thread::Id() const noexcept
    {
        return ::GetThreadId(m_thread.RawHandle());
    }

    inline void Thread::Start()
    {
        ::ResumeThread(m_thread.RawHandle());
    }

#elif KLIB_OBJECTIVE_C_ENABLED
    constexpr Thread::Thread(
        AppleDevice::ObjCHandle&& thread
    ) noexcept
        : m_thread(::std::move(thread))
    {
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

    inline bool operator==(
        Thread const& left,
        Thread const& right
    ) noexcept
    {
        return left.Id() == right.Id();
    }

    inline bool operator!=(
        Thread const& left,
        Thread const& right
    ) noexcept
    {
        return left.Id() != right.Id();
    }

    inline bool operator<(
        Thread const& left,
        Thread const& right
    ) noexcept
    {
        return left.Id() < right.Id();
    }

    inline bool operator<=(
        Thread const& left,
        Thread const& right
    ) noexcept
    {
        return left.Id() <= right.Id();
    }

    inline bool operator>(
        Thread const& left,
        Thread const& right
    ) noexcept
    {
        return left.Id() > right.Id();
    }

    inline bool operator>=(
        Thread const& left,
        Thread const& right
    ) noexcept
    {
        return left.Id() >= right.Id();
    }

    inline ::std::strong_ordering operator<=>(
        Thread const& left,
        Thread const& right
    ) noexcept
    {
        return left.Id() <=> right.Id();
    }
}

#endif //!KLIB_THRAEDING_THREAD_H
