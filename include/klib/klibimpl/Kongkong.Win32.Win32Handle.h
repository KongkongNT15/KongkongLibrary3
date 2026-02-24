#ifndef KLIB_KONGKONG_WIN32_WIN32HANDLE_H
#define KLIB_KONGKONG_WIN32_WIN32HANDLE_H

#include "base.h"

#if KLIB_ENV_WINDOWS

namespace klib::Kongkong::Win32
{
    class Win32Handle final {
    private:

        [[nodiscard]]
        static ::HANDLE DuplicateRawHandleUnsafe(
            ::HANDLE rawHandle
        ) noexcept;

        ::HANDLE m_rawHandle;

    public:

        Win32Handle() noexcept;
        constexpr Win32Handle(::HANDLE rawHandle) noexcept;
        Win32Handle(::std::nullptr_t) noexcept;
        Win32Handle(Win32Handle const& other) noexcept;
        Win32Handle(Win32Handle&& other) noexcept;

        ~Win32Handle();

        Win32Handle& operator=(::std::nullptr_t) noexcept;
        Win32Handle& operator=(Win32Handle const& other) noexcept;
        Win32Handle& operator=(Win32Handle&& other) noexcept;

        [[nodiscard]]
        operator bool() const noexcept;

        [[nodiscard]]
        bool operator!() const noexcept;

        /// <summary>
        /// 以前所有していたハンドルを解放せずに新たなハンドルをアタッチ
        /// </summary>
        /// <param name="rawHandle"></param>
        void AttachUnsafe(
            ::HANDLE rawHandle
        ) noexcept;

        /// <summary>
        /// 所有しているハンドルを解放
        /// </summary>
        /// <returns>以前所有していたハンドルの開放に成功したかどうか</returns>
        bool Detach() noexcept;
        
        [[nodiscard]]
        constexpr ::HANDLE RawHandle() const noexcept;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="rawHandle"></param>
        /// <returns>以前所有していたハンドルの開放に成功したかどうか</returns>
        bool Rettach(
            ::HANDLE rawHandle
        ) noexcept;
    };

    [[nodiscard]]
    bool operator==(
        Win32Handle const& left,
        Win32Handle const& right
    ) noexcept;

    [[nodiscard]]
    bool operator==(
        Win32Handle const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    bool operator==(
        ::std::nullptr_t,
        Win32Handle const& right
    ) noexcept;

    [[nodiscard]]
    bool operator!=(
        Win32Handle const& left,
        Win32Handle const& right
    ) noexcept;

    [[nodiscard]]
    bool operator!=(
        Win32Handle const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    bool operator!=(
        ::std::nullptr_t,
        Win32Handle const& right
    ) noexcept;
}

namespace klib::Kongkong::Win32
{
    inline Win32Handle::Win32Handle(
    ) noexcept
        : Win32Handle(nullptr)
    {
    }

    constexpr Win32Handle::Win32Handle(
        ::HANDLE rawHandle
    ) noexcept
        : m_rawHandle(rawHandle)
    {
    }

    inline Win32Handle::Win32Handle(
        ::std::nullptr_t
    ) noexcept
        : m_rawHandle(INVALID_HANDLE_VALUE)
    {
    }

    inline Win32Handle::Win32Handle(
        Win32Handle&& other
    ) noexcept
        : m_rawHandle(other.m_rawHandle)
    {
        other.m_rawHandle = INVALID_HANDLE_VALUE;
    }

    inline Win32Handle::~Win32Handle()
    {
        if (m_rawHandle == INVALID_HANDLE_VALUE) return;

        ::CloseHandle(m_rawHandle);
    }

    inline Win32Handle& Win32Handle::operator=(
        ::std::nullptr_t
        ) noexcept
    {
        Detach();

        return *this;
    }

    inline Win32Handle& Win32Handle::operator=(
        Win32Handle&& other
    ) noexcept
    {
        if (&other != this) [[likely]] {
            Rettach(other.m_rawHandle);
            other.m_rawHandle = INVALID_HANDLE_VALUE;
        }

        return *this;
    }

    inline Win32Handle::operator bool() const noexcept
    {
        return m_rawHandle != nullptr;
    }

    inline bool Win32Handle::operator!() const noexcept
    {
        return m_rawHandle == nullptr;
    }

    inline void Win32Handle::AttachUnsafe(
        ::HANDLE rawhandle
    ) noexcept
    {
        m_rawHandle = rawhandle;
    }

    inline bool Win32Handle::Detach() noexcept
    {
        if (m_rawHandle == INVALID_HANDLE_VALUE) [[unlikely]] return true;

        ::BOOL result =::CloseHandle(m_rawHandle);

        m_rawHandle = INVALID_HANDLE_VALUE;

        return static_cast<bool>(
            result
        );
    }

    inline bool Win32Handle::Rettach(
        ::HANDLE rawHandle
    ) noexcept
    {
        if (m_rawHandle != INVALID_HANDLE_VALUE) {
            ::BOOL result = ::CloseHandle(m_rawHandle);

            m_rawHandle = rawHandle;

            return static_cast<bool>(
                result
            );
        }

        m_rawHandle = rawHandle;

        return true;
    }

    inline bool operator==(
        Win32Handle const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return left.RawHandle() == INVALID_HANDLE_VALUE;
    }

    inline bool operator==(
        ::std::nullptr_t,
        Win32Handle const& right
    ) noexcept
    {
        return right == nullptr;
    }

    inline bool operator!=(
        Win32Handle const& left,
        Win32Handle const& right
    ) noexcept
    {
        return !(left == right);
    }

    inline bool operator!=(
        Win32Handle const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return !(left == nullptr);
    }

    inline bool operator!=(
        ::std::nullptr_t,
        Win32Handle const& right
    ) noexcept
    {
        return !(nullptr == right);
    }
}

#endif //!KLIB_ENV_WINDOWS
#endif //!KLIB_KONGKONG_WIN32_WIN32HANDLE_H