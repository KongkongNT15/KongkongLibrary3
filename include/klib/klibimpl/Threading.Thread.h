#ifndef KLIB_THRAEDING_THREAD_H
#define KLIB_THRAEDING_THREAD_H

#include "base.h"
#include "Foundation.HandleType.h"
#include "Foundation.ExceptionThrower.h"

#if KLIB_ENV_WINDOWS
    #include "Win32.Win32Handle.h"
#elif KLIB_OBJECTIVE_C_ENABLED
    #include "AppleDevice.ObjCHandle.h"
#elif KLIB_ENV_UNIX

#endif

#include "Threading.ThreadExitCode.h"
#include "Threading.ThreadState.h"

namespace klib::Threading
{
    class Thread final : public Foundation::HandleType {
        private:
        static uint32_t s_threadCount;

#if KLIB_ENV_WINDOWS

        template <class TFunc, bool ShouldDelete>
        static ::DWORD __stdcall EntryPoint(
            void* args
        );

        Win32::Win32Handle m_thread;

        constexpr Thread(
            ::HANDLE rawHandle
        ) noexcept;

        template <class TFunc, bool UseStackSize>
        Thread(
            TFunc&& entryPoint,
            size_t stackSize,
            ::std::bool_constant<UseStackSize>
        );

#elif KLIB_OBJECTIVE_C_ENABLED
        AppleDevice::ObjCHandle m_thread;

        constexpr Thread(
            AppleDevice::ObjCHandle&& thread
        ) noexcept;
#elif KLIB_ENV_UNIX
        ::pthread_t m_thread;
#endif

        public:

        [[nodiscard]]
        static Thread Current() noexcept;

        static void Sleep(
            uint32_t milliSeconds
        ) noexcept;

        template <class TFunc>
        Thread(
            TFunc&& entryPoint
        );

        template <class TFunc>
        Thread(
            TFunc&& entryPoint,
            size_t stackSize
        );

#if KLIB_OBJECTIVE_C_ENABLED
        Thread(
            void(^f)()
        );

        Thread(
            void(^f)(),
            size_t stackSize
        );
#endif

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

    template <class TFunc, bool ShouldDelete>
    ::DWORD __stdcall Thread::EntryPoint(
        void* args
    )
    {
        auto p = static_cast<Functional::Function<void()>*>(args);

        (*p)();

        if constexpr (ShouldDelete) {
            delete p;
        }

        return 0;
    }
    
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

    template <class TFunc, bool UseStackSize>
    Thread::Thread(
        TFunc&& entryPoint,
        size_t stackSize,
        ::std::bool_constant<UseStackSize>
    )
    {
        using TRemoved = typename ::std::remove_cvref_t<TFunc>;
        ::LPTHREAD_START_ROUTINE startAddress;
        void* args;

        constexpr bool isFunction = ::std::is_function_v<TRemoved>;
        constexpr bool isFunctionPointer = !isFunction && ::std::is_function_v<typename ::std::remove_pointer_t<TRemoved>>;
        constexpr bool isFunctionObject = !isFunction && !isFunctionPointer;

        // 関数型
        if constexpr (::std::is_function_v<TRemoved>) {
            startAddress = EntryPoint<TRemoved*, false>;
            args = &entryPoint;
        }
        // 関数ポインタ型
        else if constexpr (::std::is_function_v<typename ::std::remove_pointer_t<TRemoved>>) {
            startAddress = EntryPoint<TRemoved, false>;
            args = entryPoint;
        }
        // 関数オブジェクト型
        else {
            startAddress = EntryPoint<TRemoved, true>;
            args = new TRemoved(::std::forward(entryPoint));
        }

        ::HANDLE thread = ::CreateThread(
            nullptr,
            UseStackSize ? stackSize : 0,
            startAddress,
            args,
            UseStackSize ? STACK_SIZE_PARAM_IS_A_RESERVATION : 0,
            nullptr
        );

        if (thread == INVALID_HANDLE_VALUE) [[unlikely]] {

            if constexpr (isFunctionObject) {
                delete static_cast<TRemoved*>(args);
            }

            ExceptionThrower::ThrowMemoryAllocation();
        }

        m_thread.AttachUnsafe(thread);
    }

    template <class TFunc>
    Thread::Thread(
        TFunc&& entryPoint
    )
        : Thread(
            ::std::forward(entryPoint),
            0,
            ::std::bool_constant<false>
        )
    {
    }

    template <class TFunc>
    Thread::Thread(
        TFunc&& entryPoint,
        size_t stackSize
    )
        : Thread(
            ::std::forward(entryPoint),
            stackSize,
            ::std::bool_constant<true>
        )
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

#elif KLIB_OBJECTIVE_C_ENABLED
    constexpr Thread::Thread(
        AppleDevice::ObjCHandle&& thread
    ) noexcept
        : m_thread(::std::move(thread))
    {
    }

    template <class TFunc>
    Thread::Thread(
        TFunc&& entryPoint
    )
        : Thread(^(){ entryPoint(); })
    {
    }

    template <class TFunc>
    Thread::Thread(
        TFunc&& entryPoint,
        size_t stackSize
    )
        : Thread(
            ^(){ entryPoint(); },
            stackSize
        )
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
