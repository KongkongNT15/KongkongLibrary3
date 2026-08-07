#ifndef KLIB_NUMERICS_DECIMAL_H
#define KLIB_NUMERICS_DECIMAL_H

#include "base.h"

#include <stdint.h>

#define decimal ::klib::Numerics::Decimal

namespace klib::Numerics
{
    struct alignas(16) Decimal {
        private:

        uint64_t m_low;   // 仮数部の下位64ビットｳﾋｮｯ
        uint64_t m_high;  // 仮数部の上位48ビット + 指数部15ビット + 符号1ビットｳﾋｮｯ

        constexpr void m_setSign(
            bool minus
        ) noexcept;

        public:

        [[nodiscard]]
        constexpr bool IsMinus() const noexcept;
    };
}

namespace klib::Numerics
{
    constexpr void Decimal::m_setSign(
        bool minus
    ) noexcept
    {
        uint64_t v = static_cast<uint64_t>(minus);

        m_high = m_high & (~(v << 63));
    }

    constexpr bool Decimal::IsMinus() const noexcept
    {
        return static_cast<bool>(
            m_high & (uint64_t(1) << 63)
        );
    }
}

namespace klib::Literals
{
    consteval Numerics::Decimal
    operator""_d(
        const char* d
    )
    {

    }
}

#endif //!KLIB_NUMERICS_DECIMAL_H