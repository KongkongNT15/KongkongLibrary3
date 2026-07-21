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
        static constexpr String s_defaultMessage = u"ふぁ！？っく";

        String m_message;
        klib::Foundation::ErrorCode m_errorCode;

        protected:

        public:

        consteval Exception() noexcept;

        constexpr Exception(
            klib::Foundation::ErrorCode errorCode
        ) noexcept;

        constexpr Exception(
            klib::Foundation::ErrorCode errorCode,
            String const& message
        ) noexcept;

        constexpr Exception(
            klib::Foundation::ErrorCode errorCode,
            String&& message
        ) noexcept;

        [[nodiscard]]
        constexpr klib::Foundation::ErrorCode ErrorCode() const noexcept;

        [[nodiscard]]
        constexpr String const& Message() const noexcept;
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

    consteval Exception::Exception() noexcept
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
    ) noexcept
        : m_message(message)
        , m_errorCode(errorCode)
    {
    }

    constexpr Exception::Exception(
        klib::Foundation::ErrorCode errorCode,
        String&& message
    ) noexcept
        : m_message(::std::move(message))
        , m_errorCode(errorCode)
    {
    }

    constexpr klib::Foundation::ErrorCode
    Exception::ErrorCode() const noexcept
    {
        return m_errorCode;
    }

    constexpr String const&
    Exception::Message() const noexcept
    {
        return m_message;
    }

    constexpr bool operator==(
        Exception const& left,
        Exception const& right
    ) noexcept
    {
        return
            left.ErrorCode() == right.ErrorCode()
            && left.Message() == right.Message();
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
