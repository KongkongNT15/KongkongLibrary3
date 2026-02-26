#ifndef KLIB_KONGKONG_NUMERICS_VECTOR2_H
#define KLIB_KONGKONG_NUMERICS_VECTOR2_H

#include "base.h"

#define KLIB_CLASS_TEMPLATE_DEF template <CNumber TNum>
#define KLIB_CLASS_TEMPLATE_PARAM TNum

namespace klib::Kongkong::Numerics
{
    KLIB_CLASS_TEMPLATE_DEF
    struct Vector2 {
        public:

        using ElementType = TNum;

        ElementType X;
        ElementType Y;

        constexpr Vector2() noexcept;

        constexpr Vector2(
            ElementType x,
            ElementType y
        ) noexcept;

        template <CNumber TNum1>
        [[nodiscard]] constexpr operator Vector2<TNum1>() const noexcept;

        template <CNumber TNum1>
        [[nodiscard]] constexpr Vector2<TNum1> Cast() const noexcept;
    };

    template <CNumber TNum1, CNumber TNum2>
    [[nodiscard]] constexpr bool operator==(
        Vector2<TNum1> left,
        Vector2<TNum2> right
    ) noexcept;

    template <CNumber TNum1, CNumber TNum2>
    [[nodiscard]] constexpr bool operator!=(
        Vector2<TNum1> left,
        Vector2<TNum2> right
    ) noexcept;

    template <CNumber TNum1, CNumber TNum2>
    [[nodiscard]] constexpr Vector2<decltype(TNum1() + TNum2())>
    operator+(
        Vector2<TNum1> left,
        Vector2<TNum2> right
    ) noexcept;

    template <CNumber TNum1, CNumber TNum2>
    [[nodiscard]] constexpr Vector2<decltype(TNum1() - TNum2())>
    operator-(
        Vector2<TNum1> left,
        Vector2<TNum2> right
    ) noexcept;
}

namespace klib::Kongkong::Numerics
{
    KLIB_CLASS_TEMPLATE_DEF
    constexpr Vector2<KLIB_CLASS_TEMPLATE_PARAM>::Vector2(
    ) noexcept
        : X(0)
        , Y(0)
    {
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr Vector2<KLIB_CLASS_TEMPLATE_PARAM>::Vector2(
        ElementType x,
        ElementType y
    ) noexcept
        : X(x)
        , Y(y)
    {
    }

    KLIB_CLASS_TEMPLATE_DEF
    template <CNumber TNum1>
    constexpr Vector2<KLIB_CLASS_TEMPLATE_PARAM>::operator Vector2<TNum1>()
    const noexcept
    {
        return Cast<TNum1>();
    }

    KLIB_CLASS_TEMPLATE_DEF
    template <CNumber TNum1>
    constexpr Vector2<TNum1>
    Vector2<KLIB_CLASS_TEMPLATE_PARAM>::Cast() const noexcept
    {
        return Vector2<TNum1>(
            static_cast<TNum1>(X),
            static_cast<TNum1>(Y)
        );
    }

    template <CNumber TNum1, CNumber TNum2>
    constexpr bool operator==(
        Vector2<TNum1> left,
        Vector2<TNum2> right
    ) noexcept
    {
        return left.X == right.X && left.Y == right.Y;
    }

    template <CNumber TNum1, CNumber TNum2>
    constexpr bool operator!=(
        Vector2<TNum1> left,
        Vector2<TNum2> right
    ) noexcept
    {
        return !(left == right);
    }

    template <CNumber TNum1, CNumber TNum2>
    constexpr Vector2<decltype(TNum1() + TNum2())>
    operator+(
        Vector2<TNum1> left,
        Vector2<TNum2> right
    ) noexcept
    {
        return { left.X + right.X, left.Y + right.Y };
    }

    template <CNumber TNum1, CNumber TNum2>
    constexpr Vector2<decltype(TNum1() - TNum2())>
    operator-(
        Vector2<TNum1> left,
        Vector2<TNum2> right
    ) noexcept
    {
        return { left.X - right.X, left.Y - right.Y };
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_VECTOR2_H