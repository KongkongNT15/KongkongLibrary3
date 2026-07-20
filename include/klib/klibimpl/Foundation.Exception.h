#ifndef KLIB_FOUNDATION_EXCEPTION_H
#define KLIB_FOUNDATION_EXCEPTION_H

#include "base.h"
#include "Foundation.ErrorCode.h"
#include "Foundation.NonType.h"
#include "Text.GenericString.h"

namespace klib::Foundation
{
    struct Exception {
        private:
        static constexpr String s_defaultMessage = u"klib::Foundation::Exception";

        String m_message;
        klib::Foundation::ErrorCode m_errorCode;

        protected:

        public:

        constexpr Exception() noexcept;

        constexpr Exception(
            klib::Foundation::ErrorCode errorCode
        ) noexcept;

        constexpr Exception(
            klib::Foundation::ErrorCode errorCode,
            String const& message
        );

        constexpr Exception(
            klib::Foundation::ErrorCode errorCode,
            String&& message
        );

        [[nodiscard]]
        constexpr klib::Foundation::ErrorCode ErrorCode() const noexcept;

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

namespace klib::Foundation
{

    constexpr Exception::Exception() noexcept
        : Exception(ErrorCode::Unknown)
    {
    }

    constexpr Exception::Exception(
        klib::Foundation::ErrorCode errorCode
    ) noexcept
        : m_message(s_defaultMessage)
        , m_errorCode(errorCode)
    {
    }

    constexpr Exception::Exception(
        klib::Foundation::ErrorCode errorCode,
        String const& message
    )
        : m_message(message)
        , m_errorCode(errorCode)
    {
    }

    constexpr Exception::Exception(
        klib::Foundation::ErrorCode errorCode,
        String&& message
    )
        : m_message(::std::move(message))
        , m_errorCode(errorCode)
    {
    }

    constexpr klib::Foundation::ErrorCode
    Exception::ErrorCode() const noexcept
    {
        return m_errorCode;
    }

    constexpr const char16_t*
    Exception::Message() const noexcept
    {
        return m_message.c_str();
    }

    constexpr bool operator!=(
        Exception const& left,
        Exception const& right
    ) noexcept
    {
        return !(left == right);
    }
}

#endif //!KLIB_FOUNDATION_EXCEPTION_H
