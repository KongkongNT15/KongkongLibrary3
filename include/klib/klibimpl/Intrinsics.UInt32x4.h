#ifndef KLIB_INTRINSICS_UINT32X4_H
#define KLIB_INTRINSICS_UINT32X4_H

#include "base.h"
#include "dep/klibintrinsics.h"


namespace klib::Intrinsics
{
    struct UInt32x4 final {
        private:
#if KLIB_ENV_X64
        __m128i m_value;
#elif KLIB_ENV_ARM64
        uint32x4_t m_value;
#else

#endif
        

        public:

#if KLIB_ENV_X64

        constexpr UInt32x4(
            __m128i const& v
        ) noexcept;

#elif KLIB_ENV_ARM64
        constexpr UInt32x4(
            uint32x4_t const& v
        ) noexcept;
#else

#endif

        
    };
}

namespace klib::Intrinsics
{
#if KLIB_ENV_X64

    constexpr UInt32x4::UInt32x4(
        __m128i const& v
    ) noexcept
        : m_value(v)
    {
    }
    
#elif KLIB_ENV_ARM64
    constexpr UInt32x4::UInt32x4(
        uint32x4_t const& v
    ) noexcept
        : m_value(v)
    {
    }
#else

#endif
}

#endif //!KLIB_INTRINSICS_UINT32X4_H