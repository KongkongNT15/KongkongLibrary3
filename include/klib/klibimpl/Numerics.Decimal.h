#ifndef KLIB_NUMERICS_DECIMAL_H
#define KLIB_NUMERICS_DECIMAL_H

#include "base.h"
#include "Foundation.ValueType.h"

#include <stdint.h>

#define decimal ::klib::Numerics::Decimal

namespace klib::Numerics
{
    struct alignas(16) Decimal final : public ValueType {
        private:

        union {
            // ① 演算器（ALU）や多倍長演算でまとめて処理するための生データ表現ｳﾋｮｯ。
            struct {
                uint64_t m_low;   // 仮数部の下位64ビットｳﾋｮｯ
                uint64_t m_high;  // 仮数部の上位48ビット + 指数部15ビット + 符号1ビットｳﾋｮｯ
            };

            // ② 人間が直感的に各要素へアクセスするためのビットフィールド表現ｳﾋｮｯ。
            // ※Windows(AMD)やmacOS(Apple Silicon)などのリトルエンディアンを前提としていますｳﾋｮｯ。
            struct {
                uint64_t m_coeff_low;             // 仮数部の下位64ビット (m_lowと完全に一致)ｳﾋｮｯ
                uint64_t m_coeff_high      : 48;  // 仮数部の上位48ビット (m_highの 0〜47ビット目)ｳﾋｮｯ
                uint64_t m_exponent        : 15;  // 指数部 (m_highの 48〜62ビット目)ｳﾋｮｯ
                uint64_t m_sign            : 1;   // 符号部 (m_highの 63ビット目)ｳﾋｮｯ
            };
        };

        public:

        consteval Decimal() noexcept;

        constexpr Decimal(
            const char* numStr
        );

        [[nodiscard]]
        constexpr uint16_t Exponent() const noexcept;

        [[nodiscard]]
        constexpr bool IsMinus() const noexcept;

        [[nodiscard]]
        constexpr bool IsZero() const noexcept;
    };
}

namespace klib::Numerics
{
    constexpr uint16_t Decimal::Exponent() const noexcept
    {
        return m_exponent;
    }

    constexpr bool Decimal::IsMinus() const noexcept
    {
        return static_cast<bool>(
            m_sign
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
        return decimal(d);
    }
}

#endif //!KLIB_NUMERICS_DECIMAL_H