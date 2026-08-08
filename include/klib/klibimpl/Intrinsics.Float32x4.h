#ifndef KLIB_INTRINSICS_FLOAT32X4_H
#define KLIB_INTRINSICS_FLOAT32X4_H

#include "base.h"
#include "dep/klibintrinsics.h"

namespace klib::Intrinsics
{
    struct Float32x4 final {
        friend Float32x8;
        friend Float64x2;
        friend Float64x4;
        friend IntBlock256;
        private:

#if KLIB_ENV_X64
        static constexpr bool s_isSupported = true;

        __m128 m_value;

#elif KLIB_ENV_ARM64
        static constexpr bool s_isSupported = true;

#else
        float m_value[4];
#endif

        public:

        [[nodiscard]]
        static Float32x4 Add(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 AddSub(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 And(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 AndNot(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Blend(
            Float32x4 const& left,
            Float32x4 const& right,
            int mask
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Blend(
            Float32x4 const& left,
            Float32x4 const& right,
            Float32x4 const& mask
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Compare(
            Float32x4 const& left,
            Float32x4 const& right,
            int imm
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Div(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 DotProduct(
            Float32x4 const& left,
            Float32x4 const& right,
            int mask
        ) noexcept;

        [[nodiscard]]
        static Float32x4 HorizontalAdd(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 HorizontalSub(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static consteval bool IsSupported() noexcept;

        [[nodiscard]]
        static Float32x4 Max(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Min(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Mul(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Or(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Sub(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Shuffle(
            Float32x4 const& left,
            Float32x4 const& right,
            int mask
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Xor(
            Float32x4 const& left,
            Float32x4 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x4 Zero() noexcept;

        Float32x4() = default;

        Float32x4(
            ::std::nullptr_t
        ) = delete;

        explicit Float32x4(
            float v
        ) noexcept;

        Float32x4(
            float v1,
            float v2,
            float v3,
            float v4
        ) noexcept;

        explicit Float32x4(
            const float* p
        ) noexcept;

#if KLIB_ENV_X64
        constexpr Float32x4(
            __m128 const& other
        ) noexcept;

#elif KLIB_ENV_ARM64
        

#else
        // なんもないお
#endif

        operator Float64x4() const noexcept;
        operator IntBlock256() const noexcept;

        [[nodiscard]]
        Float32x4 Ceiling() const noexcept;

        void Broadcast(
            ::std::nullptr_t
        ) = delete;

        void Broadcast(
            const float* p
        ) noexcept;

        void Broadcast(
            const Float32x4* p
        ) noexcept;

        [[nodiscard]]
        Float32x4 Floor() const noexcept;

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
        Float32x4 Reciprocal() const noexcept;

        [[nodiscard]]
        Float32x4 ReciprocalSqrt() const noexcept;

        [[nodiscard]]
        Float32x4 Round(
            int mask
        ) const noexcept;

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
        Float32x4 Sqrt() const noexcept;
    };

    [[nodiscard]]
    Float32x4 operator+(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x4 operator-(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x4 operator*(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x4 operator/(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x4 operator&(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x4 operator|(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x4 operator^(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept;
}

namespace klib::Intrinsics
{
    
    consteval bool Float32x4::IsSupported() noexcept
    {
        return s_isSupported;
    }

#if KLIB_ENV_X64

    inline Float32x4 Float32x4::Add(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_add_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::AddSub(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_addsub_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::And(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_and_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::AndNot(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_andnot_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::Blend(
        Float32x4 const& left,
        Float32x4 const& right,
        int mask
    ) noexcept
    {
        return _mm_blend_ps(
            left.m_value,
            right.m_value,
            mask
        );
    }

    inline Float32x4 Float32x4::Blend(
        Float32x4 const& left,
        Float32x4 const& right,
        Float32x4 const& mask
    ) noexcept
    {
        return _mm_blendv_ps(
            left.m_value,
            right.m_value,
            mask.m_value
        );
    }

    inline Float32x4 Float32x4::Compare(
        Float32x4 const& left,
        Float32x4 const& right,
        int imm
    ) noexcept
    {
        return _mm_cmp_ps(left.m_value, right.m_value, imm);
    }

    inline Float32x4 Float32x4::Div(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_div_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::DotProduct(
        Float32x4 const& left,
        Float32x4 const& right,
        int mask
    ) noexcept
    {
        return _mm_dp_ps(left.m_value, right.m_value, mask);
    }

    inline Float32x4 Float32x4::HorizontalAdd(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_hadd_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::HorizontalSub(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_hsub_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::Max(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_max_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::Min(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_min_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::Mul(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_mul_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::Or(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_or_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::Sub(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_sub_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::Shuffle(
        Float32x4 const& left,
        Float32x4 const& right,
        int mask
    ) noexcept
    {
        return _mm_shuffle_ps(
            left.m_value,
            right.m_value,
            mask
        );
    }

    inline Float32x4 Float32x4::Xor(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return _mm_xor_ps(left.m_value, right.m_value);
    }

    inline Float32x4 Float32x4::Zero() noexcept
    {
        return _mm_setzero_ps();
    }

    inline Float32x4::Float32x4(
        float v
    ) noexcept
        : m_value(_mm_set1_ps(v))
    {
    }

    inline Float32x4::Float32x4(
        float v1,
        float v2,
        float v3,
        float v4
    ) noexcept
        : m_value(
            _mm_set_ps(
                v1,
                v2,
                v3,
                v4
            )
        )
    {
    }

    inline Float32x4::Float32x4(
        const float* p
    ) noexcept
        : m_value(_mm_load_ps(p))
    {
    }

    constexpr Float32x4::Float32x4(
        __m128 const& other
    ) noexcept
        : m_value(other)
    {
    }

    inline void Float32x4::Broadcast(
        const float* p
    ) noexcept
    {
        m_value = _mm_broadcast_ss(p);
    }

    inline Float32x4 Float32x4::Ceiling() const noexcept
    {
        return _mm_ceil_ps(m_value);
    }

    inline Float32x4 Float32x4::Floor() const noexcept
    {
        return _mm_sqrt_ps(m_value);
    }

    inline void Float32x4::Load(
        const float* p
    ) noexcept
    {
        m_value = _mm_load_ps(p);
    }

    inline void Float32x4::LoadUnaligned(
        const float* p
    ) noexcept
    {
        m_value = _mm_loadu_ps(p);
    }

    inline Float32x4 Float32x4::Reciprocal() const noexcept
    {
        return _mm_rcp_ps(m_value);
    }

    inline Float32x4 Float32x4::ReciprocalSqrt() const noexcept
    {
        return _mm_rsqrt_ps(m_value);
    }

    inline Float32x4 Float32x4::Round(
        int mask
    ) const noexcept
    {
        return _mm_round_ps(m_value, mask);
    }

    inline void Float32x4::Set(
        float v
    ) noexcept
    {
        m_value = _mm_set1_ps(v);
    }

    inline void Float32x4::Set(
        float v1,
        float v2,
        float v3,
        float v4
    ) noexcept
    {
        m_value = _mm_set_ps(
            v1,
            v2,
            v3,
            v4
        );
    }

    inline void Float32x4::SetReverse(
        float v1,
        float v2,
        float v3,
        float v4
    ) noexcept
    {
        m_value = _mm_setr_ps(
            v1,
            v2,
            v3,
            v4
        );
    }

    inline void Float32x4::Store(
        float* dest
    ) const noexcept
    {
        _mm_store_ps(dest, m_value);
    }

    inline void Float32x4::StoreUnaligned(
        float* dest
    ) const noexcept
    {
        _mm_storeu_ps(dest, m_value);
    }

    inline void Float32x4::Stream(
        float* dest
    ) const noexcept
    {
        _mm_stream_ps(dest, m_value);
    }

    inline Float32x4 Float32x4::Sqrt() const noexcept
    {
        return _mm_sqrt_ps(m_value);
    }

#elif KLIB_ENV_ARM64
        static constexpr bool s_isSupported = true;

#else
        float m_value[8];
#endif

    inline Float32x4 operator+(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return Float32x4::Add(left, right);
    }

    inline Float32x4 operator-(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return Float32x4::Sub(left, right);
    }

    inline Float32x4 operator*(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return Float32x4::Mul(left, right);
    }

    inline Float32x4 operator/(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return Float32x4::Div(left, right);
    }

    inline Float32x4 operator&(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return Float32x4::And(left, right);
    }

    inline Float32x4 operator|(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return Float32x4::Or(left, right);
    }

    inline Float32x4 operator^(
        Float32x4 const& left,
        Float32x4 const& right
    ) noexcept
    {
        return Float32x4::Xor(left, right);
    }
}

#endif //!KLIB_INTRINSICS_FLOAT32X4_H