#ifndef KLIB_INTRINSICS_UINT32X4_H
#define KLIB_INTRINSICS_UINT32X4_H

#include "base.h"
#include "dep/klibintrinsics.h"


namespace klib::Intrinsics
{
    struct UInt32x4 final {
        private:

        uint32x4_t m_value;

        public:

        constexpr UInt32x4(
            uint32x4_t const& v
        ) noexcept;
    };
}

namespace klib::Intrinsics
{
    constexpr UInt32x4::UInt32x4(
        uint32x4_t const& v
    ) noexcept
        : m_value(v)
    {
    }
}

#endif //!KLIB_INTRINSICS_UINT32X4_H