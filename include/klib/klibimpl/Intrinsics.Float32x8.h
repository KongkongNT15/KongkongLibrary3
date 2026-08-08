#ifndef KLIB_INTRINSICS_FLOAT32X8_H
#define KLIB_INTRINSICS_FLOAT32X8_H

#include "base.h"
#include "dep/klibintrinsics.h"

namespace klib::Intrinsics
{
    struct Float32x8 final {
        friend Float32x4;
        friend Float64x2;
        friend Float64x4;
        friend IntBlock256;
        private:

#if KLIB_ENV_X64
        static constexpr bool s_isSupported = true;

        __m256 m_value;

#elif KLIB_ENV_ARM64
        static constexpr bool s_isSupported = true;

#else
        float m_value[8];
#endif

        public:

        [[nodiscard]]
        static Float32x8 Add(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 AddSub(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 And(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 AndNot(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Blend(
            Float32x8 const& left,
            Float32x8 const& right,
            int mask
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Blend(
            Float32x8 const& left,
            Float32x8 const& right,
            Float32x8 const& mask
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Compare(
            Float32x8 const& left,
            Float32x8 const& right,
            int imm
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Div(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 DotProduct(
            Float32x8 const& left,
            Float32x8 const& right,
            int mask
        ) noexcept;

        [[nodiscard]]
        static Float32x8 HorizontalAdd(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 HorizontalSub(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static consteval bool IsSupported() noexcept;

        [[nodiscard]]
        static Float32x8 Max(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Min(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Mul(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Or(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Sub(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Shuffle(
            Float32x8 const& left,
            Float32x8 const& right,
            int mask
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Xor(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 Zero() noexcept;

        Float32x8() = default;

        Float32x8(
            ::std::nullptr_t
        ) = delete;

        explicit Float32x8(
            float v
        ) noexcept;

        Float32x8(
            float v1,
            float v2,
            float v3,
            float v4,
            float v5,
            float v6,
            float v7,
            float v8
        ) noexcept;

        explicit Float32x8(
            const float* p
        ) noexcept;

#if KLIB_ENV_X64
        constexpr Float32x8(
            __m256 const& other
        ) noexcept;

#elif KLIB_ENV_ARM64
        

#else
        // なんもないお
#endif

        operator Float64x4() const noexcept;
        operator IntBlock256() const noexcept;

        void Broadcast(
            ::std::nullptr_t
        ) = delete;

        void Broadcast(
            const float* p
        ) noexcept;

        void Broadcast(
            const Float32x4* p
        ) noexcept;

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
            ::std::nullptr_t,
            const float*
        ) = delete;

        void LoadUnaligned(
            const float*,
            ::std::nullptr_t
        ) = delete;

        void LoadUnaligned(
            ::std::nullptr_t,
            ::std::nullptr_t
        ) = delete;

        void LoadUnaligned(
            const float* p
        ) noexcept;

        void LoadUnaligned(
            const float* highAddress,
            const float* lowAddress
        ) noexcept;

        void Set(
            float v1,
            float v2,
            float v3,
            float v4,
            float v5,
            float v6,
            float v7,
            float v8
        ) noexcept;

        void Set1(
            float v
        ) noexcept;

        void SetReverse(
            float v1,
            float v2,
            float v3,
            float v4,
            float v5,
            float v6,
            float v7,
            float v8
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
            ::std::nullptr_t,
            float*
        ) const = delete;

        void StoreUnaligned(
            float*,
            ::std::nullptr_t
        ) const = delete;

        void StoreUnaligned(
            ::std::nullptr_t,
            ::std::nullptr_t
        ) const = delete;

        void StoreUnaligned(
            float* dest
        ) const noexcept;

        void StoreUnaligned(
            float* highAddress,
            float* lowAddress
        ) const noexcept;
    };

    [[nodiscard]]
    Float32x8 operator+(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x8 operator-(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x8 operator*(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x8 operator/(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x8 operator&(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x8 operator|(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept;

    [[nodiscard]]
    Float32x8 operator^(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept;
}

namespace klib::Intrinsics
{
    
    consteval bool Float32x8::IsSupported() noexcept
    {
        return s_isSupported;
    }

#if KLIB_ENV_X64

    inline Float32x8 Float32x8::Add(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_add_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::AddSub(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_addsub_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::And(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_and_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::AndNot(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_andnot_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::Blend(
        Float32x8 const& left,
        Float32x8 const& right,
        int mask
    ) noexcept
    {
        return _mm256_blend_ps(
            left.m_value,
            right.m_value,
            mask
        );
    }

    inline Float32x8 Float32x8::Blend(
        Float32x8 const& left,
        Float32x8 const& right,
        Float32x8 const& mask
    ) noexcept
    {
        return _mm256_blendv_ps(
            left.m_value,
            right.m_value,
            mask.m_value
        );
    }

    inline Float32x8 Float32x8::Compare(
        Float32x8 const& left,
        Float32x8 const& right,
        int imm
    ) noexcept
    {
        return _mm256_cmp_ps(left.m_value, right.m_value, imm);
    }

    inline Float32x8 Float32x8::Div(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_div_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::DotProduct(
        Float32x8 const& left,
        Float32x8 const& right,
        int mask
    ) noexcept
    {
        return _mm256_dp_ps(left.m_value, right.m_value, mask);
    }

    inline Float32x8 Float32x8::HorizontalAdd(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_hadd_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::HorizontalSub(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_hsub_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::Max(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_max_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::Min(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_min_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::Mul(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_mul_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::Or(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_or_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::Sub(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_sub_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::Shuffle(
        Float32x8 const& left,
        Float32x8 const& right,
        int mask
    ) noexcept
    {
        return _mm256_shuffle_ps(
            left.m_value,
            right.m_value,
            mask
        );
    }

    inline Float32x8 Float32x8::Xor(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_xor_ps(left.m_value, right.m_value);
    }

    inline Float32x8 Float32x8::Zero() noexcept
    {
        return _mm256_setzero_ps();
    }

    inline Float32x8::Float32x8(
        float v
    ) noexcept
        : m_value(_mm256_set1_ps(v))
    {
    }

    inline Float32x8::Float32x8(
        float v1,
        float v2,
        float v3,
        float v4,
        float v5,
        float v6,
        float v7,
        float v8
    ) noexcept
        : m_value(
            _mm256_set_ps(
                v1,
                v2,
                v3,
                v4,
                v5,
                v6,
                v7,
                v8
            )
        )
    {
    }

    inline Float32x8::Float32x8(
        const float* p
    ) noexcept
        : m_value(_mm256_load_ps(p))
    {
    }

    constexpr Float32x8::Float32x8(
        __m256 const& other
    ) noexcept
        : m_value(other)
    {
    }

    inline void Float32x8::Broadcast(
        const float* p
    ) noexcept
    {
        m_value = _mm256_broadcast_ss(p);
    }

    inline void Float32x8::Load(
        const float* p
    ) noexcept
    {
        m_value = _mm256_load_ps(p);
    }

    inline void Float32x8::LoadUnaligned(
        const float* p
    ) noexcept
    {
        m_value = _mm256_loadu_ps(p);
    }

    inline void Float32x8::LoadUnaligned(
        const float* highAddress,
        const float* lowAddress
    ) noexcept
    {
        m_value = _mm256_loadu2_m128(highAddress, lowAddress);
    }

    inline void Float32x8::Set(
        float v1,
        float v2,
        float v3,
        float v4,
        float v5,
        float v6,
        float v7,
        float v8
    ) noexcept
    {
        m_value = _mm256_set_ps(
            v1,
            v2,
            v3,
            v4,
            v5,
            v6,
            v7,
            v8
        );
    }

    inline void Float32x8::Set1(
        float v
    ) noexcept
    {
        m_value = _mm256_set1_ps(v);
    }

    inline void Float32x8::SetReverse(
        float v1,
        float v2,
        float v3,
        float v4,
        float v5,
        float v6,
        float v7,
        float v8
    ) noexcept
    {
        m_value = _mm256_setr_ps(
            v1,
            v2,
            v3,
            v4,
            v5,
            v6,
            v7,
            v8
        );
    }

    void Float32x8::Store(
        float* dest
    ) const noexcept
    {
        _mm256_store_ps(dest, m_value);
    }

    void Float32x8::StoreUnaligned(
        float* dest
    ) const noexcept
    {
        _mm256_storeu_ps(dest, m_value);
    }

    void Float32x8::StoreUnaligned(
        float* highAddress,
        float* lowAddress
    ) const noexcept
    {
        _mm256_storeu2_m128(highAddress, lowAddress, m_value);
    }

#elif KLIB_ENV_ARM64
        static constexpr bool s_isSupported = true;

#else
        float m_value[8];
#endif

    inline Float32x8 operator+(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return Float32x8::Add(left, right);
    }

    inline Float32x8 operator-(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return Float32x8::Sub(left, right);
    }

    inline Float32x8 operator*(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return Float32x8::Mul(left, right);
    }

    inline Float32x8 operator/(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return Float32x8::Div(left, right);
    }

    inline Float32x8 operator&(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return Float32x8::And(left, right);
    }

    inline Float32x8 operator|(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return Float32x8::Or(left, right);
    }

    inline Float32x8 operator^(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return Float32x8::Xor(left, right);
    }
}

#endif //!KLIB_INTRINSICS_FLOAT32X8_H