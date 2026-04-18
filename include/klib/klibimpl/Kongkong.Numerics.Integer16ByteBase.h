#ifndef KLIB_KONGKONG_NUMERICS_INTEGER16BYTEBASE_H
#define KLIB_KONGKONG_NUMERICS_INTEGER16BYTEBASE_H

#include "base.h"
#include "Kongkong.ValueType.h"

#include <inttypes.h>

namespace klib::Kongkong::Numerics
{
    struct Integer16ByteBase : public ValueType {
        protected:

        uint_least64_t m_lowPart;
        uint_least64_t m_highPart;

        constexpr Integer16ByteBase() = default;

        constexpr Integer16ByteBase(
            uint_least64_t lowPart,
            uint_least64_t highPart
        ) noexcept;

        constexpr void do_increment() noexcept;

        constexpr void do_setValue(
            int_least64_t value
        ) noexcept;

        constexpr void do_setValue(
            uint_least64_t value
        ) noexcept;

        public:

        [[nodiscard]]
        constexpr bool operator!() const noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;

        [[nodiscard]]
        constexpr uint_least64_t HighPart() const noexcept;

        [[nodiscard]]
        constexpr bool IsZero() const noexcept;

        [[nodiscard]]
        constexpr uint_least64_t LowPart() const noexcept;
    };
}

namespace klib::Kongkong::Numerics
{
    constexpr void Integer16ByteBase::do_increment() noexcept
    {
        if (++m_lowPart == 0) ++m_highPart;
    }

    constexpr void Integer16ByteBase::do_setValue(
        int_least64_t value
    ) noexcept
    {
        if (value < 0) {
            m_highPart = -1;
        }
        else {
            m_highPart = 0;
        }

        m_lowPart = value;
    }

    constexpr void Integer16ByteBase::do_setValue(
        uint_least64_t value
    ) noexcept
    {
        m_highPart = 0;
        m_lowPart = value;
    }

    constexpr bool Integer16ByteBase::operator!() const noexcept
    {
        return IsZero();
    }

    constexpr Hash::ResultType
    Integer16ByteBase::GetHashCode() const noexcept
    {
        auto h1 = Hash::Get(m_lowPart);
        auto h2 = Hash::Get(m_highPart);

        return h1 + h2;
    }

    constexpr uint_least64_t
    Integer16ByteBase::HighPart() const noexcept
    {
        return m_highPart;
    }

    constexpr bool Integer16ByteBase::IsZero() const noexcept
    {
        return m_lowPart == 0 && m_highPart == 0;
    }

    constexpr uint_least64_t
    Integer16ByteBase::LowPart() const noexcept
    {
        return m_lowPart;
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_INTEGER16BYTEBASE_H