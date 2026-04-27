#ifndef KLIB_EXCEPTION_H
#define KLIB_EXCEPTION_H

#include "base.h"
#include "ErrorCode.h"
#include "NonType.h"

namespace klib
{
    struct Exception {
        private:
        static constexpr char16_t s_defaultMessage[] = u"klib::Exception";

        const char16_t* m_message;
        ErrorCode m_errorCode;
        bool m_shouldCopy;

        protected:

        constexpr Exception(
            ErrorCode errorCode,
            const char16_t* message,
            NonType
        ) noexcept;

        public:

        constexpr Exception() noexcept;

        constexpr Exception(
            ErrorCode errorCode
        ) noexcept;

        Exception(
            ErrorCode errorCode,
            const char16_t* message
        );

        Exception(
            ErrorCode errorCode,
            const char16_t* message,
            bool shouldCopy
        );

        ~Exception();

        [[nodiscard]]
        constexpr ErrorCode ErrorCode() const noexcept;

        [[nodiscard]]
        constexpr const char16_t* Message() const noexcept;
    };

    [[nodiscard]]
    constexpr bool operator==(
        Exception const& left,
        Exception const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        Exception const& left,
        Exception const& right
    ) noexcept;
}

namespace klib
{
    constexpr Exception::Exception(
        ErrorCode errorCode,
        const char16_t* message,
        NonType
    ) noexcept
        : m_message(message)
        , m_errorCode(errorCode)
        , m_shouldCopy(false)
    {
    }

    constexpr Exception::Exception() noexcept
        : Exception(ErrorCode::Unknown)
    {
    }

    constexpr Exception::Exception(
        ErrorCode errorCode
    ) noexcept
        : m_message(s_defaultMessage)
        , m_errorCode(errorCode)
        , m_shouldCopy(false)
    {
    }

    inline Exception::Exception(
        ErrorCode errorCode,
        const char16_t* message
    )
        : Exception(
            errorCode,
            message,
            true
        )
    {
    }

    constexpr ErrorCode
    Exception::ErrorCode() const noexcept
    {
        return m_errorCode;
    }

    constexpr const char16_t*
    Exception::Message() const noexcept
    {
        return m_message;
    }

    constexpr bool operator!=(
        Exception const& left,
        Exception const& right
    ) noexcept
    {
        return !(left == right);
    }
}

#endif //!KLIB_EXCEPTION_H
