#ifndef KLIB_KONGKONG_EXCEPTION_H
#define KLIB_KONGKONG_EXCEPTION_H

#include "base.h"
#include "Kongkong.ErrorCode.h"
#include "Kongkong.NonType.h"

namespace klib::Kongkong
{
    struct Exception {
        private:
        static constexpr char16_t s_defaultMessage[] = u"klib::Kongkong::Exception";

        const char16_t* m_message;
        Kongkong::ErrorCode m_errorCode;
        bool m_shouldCopy;

        protected:

        constexpr Exception(
            Kongkong::ErrorCode errorCode,
            const char16_t* message,
            NonType
        ) noexcept;

        public:

        constexpr Exception() noexcept;

        constexpr Exception(
            Kongkong::ErrorCode errorCode
        ) noexcept;

        Exception(
            Kongkong::ErrorCode errorCode,
            const char16_t* message
        );

        Exception(
            Kongkong::ErrorCode errorCode,
            const char16_t* message,
            bool shouldCopy
        );

        ~Exception();

        [[nodiscard]]
        constexpr Kongkong::ErrorCode ErrorCode() const noexcept;

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

namespace klib::Kongkong
{
    constexpr Exception::Exception(
        Kongkong::ErrorCode errorCode,
        const char16_t* message,
        NonType
    ) noexcept
        : m_message(message)
        , m_errorCode(errorCode)
        , m_shouldCopy(false)
    {
    }

    constexpr Exception::Exception() noexcept
        : Exception(Kongkong::ErrorCode::Unknown)
    {
    }

    constexpr Exception::Exception(
        Kongkong::ErrorCode errorCode
    ) noexcept
        : m_message(s_defaultMessage)
        , m_errorCode(errorCode)
        , m_shouldCopy(false)
    {
    }

    inline Exception::Exception(
        Kongkong::ErrorCode errorCode,
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
}

#endif //!KLIB_KONGKONG_EXCEPTION_H