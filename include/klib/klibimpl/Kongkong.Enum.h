#ifndef KLIB_KONGKONG_ENUM_H
#define KLIB_KONGKONG_ENUM_H

#include "base.h"
#include "Kongkong.ValueType.h"

#define KLIB_CLASS_TEMPLATE_DEF template <class TEnum> requires ::std::is_enum_v<TEnum>
#define KLIB_CLASS_TEMPLATE_PARAM TEnum

namespace klib::Kongkong
{
    template <>
    struct Enum<void> final {

        KLIB_CLASS_TEMPLATE_DEF
        [[nodiscard]]
        static constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM> BitAnd(
            KLIB_CLASS_TEMPLATE_PARAM left,
            KLIB_CLASS_TEMPLATE_PARAM right
        ) noexcept;

        KLIB_CLASS_TEMPLATE_DEF
        [[nodiscard]]
        static constexpr KLIB_CLASS_TEMPLATE_PARAM BitOr(
            KLIB_CLASS_TEMPLATE_PARAM left,
            KLIB_CLASS_TEMPLATE_PARAM right
        ) noexcept;

        KLIB_CLASS_TEMPLATE_DEF
        [[nodiscard]]
        static constexpr KLIB_CLASS_TEMPLATE_PARAM ClearFlag(
            KLIB_CLASS_TEMPLATE_PARAM flags,
            KLIB_CLASS_TEMPLATE_PARAM target
        ) noexcept;
    };

    template <class TEnum> requires ::std::is_enum_v<TEnum>
    struct Enum : ValueType {
        public:
        using Base = typename ::std::underlying_type_t<TEnum>;

        TEnum Value;

        constexpr Enum() = default;

        constexpr Enum(
            TEnum value
        ) noexcept;

        constexpr Enum(
            Base value
        ) noexcept;

        [[nodiscard]]
        constexpr operator bool() const noexcept;

        [[nodiscard]]
        constexpr operator TEnum() const noexcept;

        constexpr Enum& operator|=(
            TEnum value
        ) noexcept;

        constexpr Enum& operator|=(
            Enum value
        ) noexcept;

        constexpr Enum& operator&=(
            TEnum value
        ) noexcept;

        constexpr Enum& operator&=(
            Enum value
        ) noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode(
        ) const noexcept;
    };

    KLIB_CLASS_TEMPLATE_DEF
    [[nodiscard]] constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM> operator|(
        Enum<KLIB_CLASS_TEMPLATE_PARAM> left,
        Enum<KLIB_CLASS_TEMPLATE_PARAM> right
    ) noexcept;

    KLIB_CLASS_TEMPLATE_DEF
    [[nodiscard]] constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM> operator&(
        Enum<KLIB_CLASS_TEMPLATE_PARAM> left,
        Enum<KLIB_CLASS_TEMPLATE_PARAM> right
    ) noexcept;
}

namespace klib::Kongkong
{
    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM>
    Enum<void>::BitAnd(
        KLIB_CLASS_TEMPLATE_PARAM left,
        KLIB_CLASS_TEMPLATE_PARAM right
    ) noexcept
    {
        using base = typename ::std::underlying_type_t<KLIB_CLASS_TEMPLATE_PARAM>;

        base b1 = static_cast<base>(left);
        base b2 = static_cast<base>(right);

        return b1 & b2;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr KLIB_CLASS_TEMPLATE_PARAM
    Enum<void>::BitOr(
        KLIB_CLASS_TEMPLATE_PARAM left,
        KLIB_CLASS_TEMPLATE_PARAM right
    ) noexcept
    {
        using base = typename ::std::underlying_type_t<KLIB_CLASS_TEMPLATE_PARAM>;

        base b1 = static_cast<base>(left);
        base b2 = static_cast<base>(right);

        return static_cast<KLIB_CLASS_TEMPLATE_PARAM>(
            b1 | b2
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr KLIB_CLASS_TEMPLATE_PARAM
    Enum<void>::ClearFlag(
        KLIB_CLASS_TEMPLATE_PARAM flags,
        KLIB_CLASS_TEMPLATE_PARAM target
    ) noexcept
    {
        using base = typename ::std::underlying_type_t<KLIB_CLASS_TEMPLATE_PARAM>;

        base b1 = static_cast<base>(flags);
        base b2 = static_cast<base>(target);

        return static_cast<KLIB_CLASS_TEMPLATE_PARAM>(
            b1 & ~b2
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM>::Enum(
        TEnum value
    ) noexcept
        : Value(value)
    {
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM>::Enum(
        Base value
    ) noexcept
        : Value(static_cast<KLIB_CLASS_TEMPLATE_PARAM>(value))
    {
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM>::operator
    bool() const noexcept
    {
        return static_cast<bool>(Value);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM>::operator
    KLIB_CLASS_TEMPLATE_PARAM() const noexcept
    {
        return Value;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM>&
    Enum<KLIB_CLASS_TEMPLATE_PARAM>::operator|=(
        KLIB_CLASS_TEMPLATE_PARAM value
    ) noexcept
    {
        Value = Enum<>::BitOr(Value, value);
        return *this;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM>&
    Enum<KLIB_CLASS_TEMPLATE_PARAM>::operator|=(
        Enum<KLIB_CLASS_TEMPLATE_PARAM> value
    ) noexcept
    {
        return *this |= value.Value;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM>&
    Enum<KLIB_CLASS_TEMPLATE_PARAM>::operator&=(
        KLIB_CLASS_TEMPLATE_PARAM value
    ) noexcept
    {
        return *this = Enum<>::BitAnd(Value, value);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM>&
    Enum<KLIB_CLASS_TEMPLATE_PARAM>::operator&=(
        Enum<KLIB_CLASS_TEMPLATE_PARAM> value
    ) noexcept
    {
        return *this &= value.Value;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Hash::ResultType
    Enum<KLIB_CLASS_TEMPLATE_PARAM>::GetHashCode(
    ) const noexcept
    {
        return ::std::hash<Base>().operator()(
            static_cast<Base>(Value)
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM> operator|(
        Enum<KLIB_CLASS_TEMPLATE_PARAM> left,
        Enum<KLIB_CLASS_TEMPLATE_PARAM> right
    ) noexcept
    {
        return Enum<>::BitOr(
            left.Value,
            right.Value
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Enum<KLIB_CLASS_TEMPLATE_PARAM> operator&(
        Enum<KLIB_CLASS_TEMPLATE_PARAM> left,
        Enum<KLIB_CLASS_TEMPLATE_PARAM> right
    ) noexcept
    {
        return Enum<>::BitAnd(
            left.Value,
            right.Value
        );
    }
}

#undef KLIB_CLASS_TEMPLATE_DEF
#undef KLIB_CLASS_TEMPLATE_PARAM

#endif //!KLIB_KONGKONG_ENUM_H