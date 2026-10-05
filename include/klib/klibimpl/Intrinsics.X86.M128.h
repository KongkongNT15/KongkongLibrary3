#ifndef KLIB_INTRINSICS_X86_M128_H
#define KLIB_INTRINSICS_X86_M128_H

#include "base.h"
#include "dep/klibintrinsics.h"

namespace klib::Intrinsics::X86
{
    struct M128 final {
        public:

        using ElementType = float;

        __m128 Value;

        [[nodiscard]]
        static M128 Add(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 AddSub(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 And(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 AndNot(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 Blend(
            M128 const& left,
            M128 const& right,
            int mask
        ) noexcept;

        [[nodiscard]]
        static M128 Blend(
            M128 const& left,
            M128 const& right,
            M128 const& mask
        ) noexcept;

        [[nodiscard]]
        static UInt32x4 Compare(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 Div(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 DotProduct(
            M128 const& left,
            M128 const& right,
            int mask
        ) noexcept;

        [[nodiscard]]
        static M128 FusedMultiplyAdd(
            M128 const& a,
            M128 const& b,
            M128 const& c
        ) noexcept;

        [[nodiscard]]
        static M128 HorizontalAdd(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 HorizontalSub(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static consteval ssize_t Length() noexcept;

        [[nodiscard]]
        static M128 Max(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 Min(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 Mul(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 Mul(
            M128 const& left,
            float right
        ) noexcept;

        [[nodiscard]]
        static M128 Or(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 Sub(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 Shuffle(
            M128 const& left,
            M128 const& right,
            int mask
        ) noexcept;

        [[nodiscard]]
        static M128 Xor(
            M128 const& left,
            M128 const& right
        ) noexcept;

        [[nodiscard]]
        static M128 Zero() noexcept;

        M128() = default;

        M128(
            ::std::nullptr_t
        ) = delete;

        explicit M128(
            float v
        ) noexcept;

        M128(
            float v1,
            float v2,
            float v3,
            float v4
        ) noexcept;

        explicit M128(
            const float* p
        ) noexcept;

        constexpr M128(
            __m128 const& other
        ) noexcept;

        M128 operator-() const noexcept;

        M128& operator+=(
            M128 const& other
        ) noexcept;

        M128& operator-=(
            M128 const& other
        ) noexcept;

        M128& operator*=(
            M128 const& other
        ) noexcept;

        M128& operator*=(
            float other
        ) noexcept;

        M128& operator/=(
            M128 const& other
        ) noexcept;

        M128& operator&=(
            M128 const& other
        ) noexcept;

        M128& operator|=(
            M128 const& other
        ) noexcept;

        M128& operator^=(
            M128 const& other
        ) noexcept;

        [[nodiscard]]
        M128 AbsoluteValue() const noexcept;

        void Broadcast(
            ::std::nullptr_t
        ) = delete;

        void Broadcast(
            const float* p
        ) noexcept;

        [[nodiscard]]
        M128 Ceiling() const noexcept;

        [[nodiscard]]
        M128 Floor() const noexcept;

        void Load(
            ::std::nullptr_t
        ) = delete;

        void Load(
            const float* p
        ) noexcept;

        void LoadUnaligned(
            ::std::nullptr_t
        ) = delete;

        void LoadUnaligned(
            const float* p
        ) noexcept;

        [[nodiscard]]
        M128 Reciprocal() const noexcept;

        [[nodiscard]]
        M128 ReciprocalSqrt() const noexcept;

        [[nodiscard]]
        M128 Round() const noexcept;

        void Set(
            float v
        ) noexcept;

        void Set(
            float v1,
            float v2,
            float v3,
            float v4
        ) noexcept;

        void SetReverse(
            float v1,
            float v2,
            float v3,
            float v4
        ) noexcept;

        void Store(
            ::std::nullptr_t
        ) const = delete;

        void Store(
            float* dest
        ) const noexcept;

        void StoreUnaligned(
            ::std::nullptr_t
        ) const = delete;

        void StoreUnaligned(
            float* dest
        ) const noexcept;

        void Stream(
            ::std::nullptr_t
        ) const = delete;

        void Stream(
            float* dest
        ) const noexcept;

        [[nodiscard]]
        M128 Sqrt() const noexcept;
    };

    [[nodiscard]]
    M128 operator+(
        M128 const& left,
        M128 const& right
    ) noexcept;

    [[nodiscard]]
    M128 operator-(
        M128 const& left,
        M128 const& right
    ) noexcept;

    [[nodiscard]]
    M128 operator*(
        M128 const& left,
        M128 const& right
    ) noexcept;

    [[nodiscard]]
    M128 operator*(
        M128 const& left,
        float right
    ) noexcept;

    [[nodiscard]]
    M128 operator*(
        float left,
        M128 const& right
    ) noexcept;

    [[nodiscard]]
    M128 operator/(
        M128 const& left,
        M128 const& right
    ) noexcept;

    [[nodiscard]]
    M128 operator&(
        M128 const& left,
        M128 const& right
    ) noexcept;

    [[nodiscard]]
    M128 operator|(
        M128 const& left,
        M128 const& right
    ) noexcept;

    [[nodiscard]]
    M128 operator^(
        M128 const& left,
        M128 const& right
    ) noexcept;
}

namespace klib::Intrinsics::X86
{
    consteval ssize_t M128::Length() noexcept
    {
        return 4;
    }

    M128& M128::operator+=(
        M128 const& other
    ) noexcept
    {
        return *this = Add(*this, other);
    }

    M128& M128::operator-=(
        M128 const& other
    ) noexcept
    {
        return *this = Sub(*this, other);
    }

    M128& M128::operator*=(
        M128 const& other
    ) noexcept
    {
        return *this = Mul(*this, other);
    }

    M128& M128::operator*=(
        float other
    ) noexcept
    {
        return *this = Mul(*this, other);
    }

    M128& M128::operator/=(
        M128 const& other
    ) noexcept
    {
        return *this = Div(*this, other);
    }

    M128& M128::operator&=(
        M128 const& other
    ) noexcept
    {
        return *this = And(*this, other);
    }

    M128& M128::operator|=(
        M128 const& other
    ) noexcept
    {
        return *this = Or(*this, other);
    }

    M128& M128::operator^=(
        M128 const& other
    ) noexcept
    {
        return *this = Xor(*this, other);
    }

    inline M128 M128::Add(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_add_ps(left.Value, right.Value);
    }

    inline M128 M128::AddSub(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_addsub_ps(left.Value, right.Value);
    }

    inline M128 M128::And(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_and_ps(left.Value, right.Value);
    }

    inline M128 M128::AndNot(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_andnot_ps(left.Value, right.Value);
    }

    inline M128 M128::Blend(
        M128 const& left,
        M128 const& right,
        int mask
    ) noexcept
    {
        return _mm_blend_ps(
            left.Value,
            right.Value,
            mask
        );
    }

    inline M128 M128::Blend(
        M128 const& left,
        M128 const& right,
        M128 const& mask
    ) noexcept
    {
        return _mm_blendv_ps(
            left.Value,
            right.Value,
            mask.Value
        );
    }

    inline M128 M128::Div(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_div_ps(left.Value, right.Value);
    }

    inline M128 M128::DotProduct(
        M128 const& left,
        M128 const& right,
        int mask
    ) noexcept
    {
        return _mm_dp_ps(left.Value, right.Value, mask);
    }

    inline M128 M128::HorizontalAdd(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_hadd_ps(left.Value, right.Value);
    }

    inline M128 M128::HorizontalSub(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_hsub_ps(left.Value, right.Value);
    }

    inline M128 M128::Max(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_max_ps(left.Value, right.Value);
    }

    inline M128 M128::Min(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_min_ps(left.Value, right.Value);
    }

    inline M128 M128::Mul(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_mul_ps(left.Value, right.Value);
    }

    inline M128 M128::Mul(
        M128 const& left,
        float right
    ) noexcept
    {
        return _mm_mul_ps(left.Value, M128(right).Value);
    }

    inline M128 M128::Or(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_or_ps(left.Value, right.Value);
    }

    inline M128 M128::Sub(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_sub_ps(left.Value, right.Value);
    }

    inline M128 M128::Shuffle(
        M128 const& left,
        M128 const& right,
        int mask
    ) noexcept
    {
        return _mm_shuffle_ps(
            left.Value,
            right.Value,
            mask
        );
    }

    inline M128 M128::Xor(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return _mm_xor_ps(left.Value, right.Value);
    }

    inline M128 M128::Zero() noexcept
    {
        return _mm_setzero_ps();
    }

    inline M128::M128(
        float v
    ) noexcept
        : Value(_mm_set1_ps(v))
    {
    }

    inline M128::M128(
        float v1,
        float v2,
        float v3,
        float v4
    ) noexcept
        : Value(
            _mm_set_ps(
                v1,
                v2,
                v3,
                v4
            )
        )
    {
    }

    inline M128::M128(
        const float* p
    ) noexcept
        : Value(_mm_load_ps(p))
    {
    }

    constexpr M128::M128(
        __m128 const& other
    ) noexcept
        : Value(other)
    {
    }

    inline void M128::Broadcast(
        const float* p
    ) noexcept
    {
        Value = _mm_broadcast_ss(p);
    }

    inline M128 M128::Ceiling() const noexcept
    {
        return _mm_ceil_ps(Value);
    }

    inline M128 M128::Floor() const noexcept
    {
        return _mm_floor_ps(Value);
    }

    inline void M128::Load(
        const float* p
    ) noexcept
    {
        Value = _mm_load_ps(p);
    }

    inline void M128::LoadUnaligned(
        const float* p
    ) noexcept
    {
        Value = _mm_loadu_ps(p);
    }

    inline M128 M128::Reciprocal() const noexcept
    {
        return _mm_rcp_ps(Value);
    }

    inline M128 M128::ReciprocalSqrt() const noexcept
    {
        return _mm_rsqrt_ps(Value);
    }

    inline M128 M128::Round(
    ) const noexcept
    {
        return _mm_round_ps(Value, _MM_FROUND_CUR_DIRECTION);
    }

    inline void M128::Set(
        float v
    ) noexcept
    {
        Value = _mm_set1_ps(v);
    }

    inline void M128::Set(
        float v1,
        float v2,
        float v3,
        float v4
    ) noexcept
    {
        Value = _mm_set_ps(
            v1,
            v2,
            v3,
            v4
        );
    }

    inline void M128::SetReverse(
        float v1,
        float v2,
        float v3,
        float v4
    ) noexcept
    {
        Value = _mm_setr_ps(
            v1,
            v2,
            v3,
            v4
        );
    }

    inline void M128::Store(
        float* dest
    ) const noexcept
    {
        _mm_store_ps(dest, Value);
    }

    inline void M128::StoreUnaligned(
        float* dest
    ) const noexcept
    {
        _mm_storeu_ps(dest, Value);
    }

    inline void M128::Stream(
        float* dest
    ) const noexcept
    {
        _mm_stream_ps(dest, Value);
    }

    inline M128 M128::Sqrt() const noexcept
    {
        return _mm_sqrt_ps(Value);
    }

    inline M128 operator+(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return M128::Add(left, right);
    }

    inline M128 operator-(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return M128::Sub(left, right);
    }

    inline M128 operator*(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return M128::Mul(left, right);
    }

    inline M128 operator*(
        M128 const& left,
        float right
    ) noexcept
    {
        return M128::Mul(left, right);
    }

    inline M128 operator*(
        float left,
        M128 const& right
    ) noexcept
    {
        return M128::Mul(right, left);
    }

    inline M128 operator/(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return M128::Div(left, right);
    }

    inline M128 operator&(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return M128::And(left, right);
    }

    inline M128 operator|(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return M128::Or(left, right);
    }

    inline M128 operator^(
        M128 const& left,
        M128 const& right
    ) noexcept
    {
        return M128::Xor(left, right);
    }
}

#endif //!KLIB_INTRINSICS_X86_M128_H