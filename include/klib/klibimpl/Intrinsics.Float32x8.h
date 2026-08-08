#ifndef KLIB_INTRINSICS_FLOAT32X8_H
#define KLIB_INTRINSICS_FLOAT32X8_H

#include "base.h"
#include "dep/klibintrinsics.h"

namespace klib::Intrinsics
{
    struct Float32x8 final {
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
        static Float32x8 Div(
            Float32x8 const& left,
            Float32x8 const& right
        ) noexcept;

        [[nodiscard]]
        static Float32x8 DotProduct(
            Float32x8 const& left,
            Float32x8 const& right
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
        static Float32x8 Shuffle(
            Float32x8 const& left,
            Float32x8 const& right,
            Float32x8 const& mask
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

        void Broadcast(
            ::std::nullptr_t
        ) = delete;

        void Broadcast(
            const float* p
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
            const float* p
        ) noexcept;

        void Set1(
            float v
        ) noexcept;

        void Store(
            ::std::nullptr_t
        ) const = delete;

        void Store(
            float* dest
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

    inline Float32x8 Float32x8::Mul(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return _mm256_mul_ps(left.m_value, right.m_value);
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

    inline void Float32x8::Set1(
        float v
    ) noexcept
    {
        m_value = _mm256_set1_ps(v);
    }

    void Float32x8::Store(
        float* dest
    ) const noexcept
    {
        _mm256_store_ps(dest, m_value);
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

    inline Float32x8 operator*(
        Float32x8 const& left,
        Float32x8 const& right
    ) noexcept
    {
        return Float32x8::Mul(left, right);
    }
}

#endif //!KLIB_INTRINSICS_FLOAT32X8_H