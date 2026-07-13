#ifndef KLIB_FUNCTIONAL_RAWFUNCTION_H
#define KLIB_FUNCTIONAL_RAWFUNCTION_H

#include "base.h"
#include "Functional.FunctionBase.h"

namespace klib::Functional
{
    template <class TResult, class... TArgs>
    struct RawFunction : public FunctionBase<TResult, TArgs...> {
        
    };
}

#endif //!KLIB_FUNCTIONAL_RAWFUNCTION_H