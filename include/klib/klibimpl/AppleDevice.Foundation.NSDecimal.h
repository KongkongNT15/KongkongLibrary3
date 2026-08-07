#ifndef KLIB_FOUNDATION_NSDECIMAL_H
#define KLIB_FOUNDATION_NSDECIMAL_H

#include "base.h"
#include "Foundation.ValueType.h"

namespace klib::AppleDevice::Foundation
{
    struct alignas(4) NSDecimal final : public ValueType {
        private:
        int m_placeHolder[5];
        public:

        NSDecimal() noexcept;

        NSDecimal(
            NSDecimal const& other
        ) noexcept;

        NSDecimal& operator=(
            NSDecimal const& other
        ) noexcept;


    };

    [[nodiscard]]
    ::std::strong_ordering operator<=>(
        NSDecimal const& left,
        NSDecimal const& right
    ) noexcept;

    
}

#endif //!KLIB_FOUNDATION_NSDECIMAL_H