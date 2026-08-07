#ifndef KLIB_FOUNDATION_NSCALCULATIONERROR_H
#define KLIB_FOUNDATION_NSCALCULATIONERROR_H

#include "base.h"

namespace klib::AppleDevice::Foundation
{
    enum struct NSCalculationError {
        NoError,
        LossOfPrecision,
        Overflow,
        Underflow,
        DivideByZero
    };
}

#endif //!KLIB_FOUNDATION_NSCALCULATIONERROR_H