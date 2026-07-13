#ifndef KLIB_FUNCTIONAL_FUNCTIONBASE_H
#define KLIB_FUNCTIONAL_FUNCTIONBASE_H

#include "base.h"

namespace klib::Functional
{
    template <class TResult, class... TArgs>
    struct FunctionBase {
        public:

        virtual ~FunctionBase() = default;

        virtual TResult operator()(
            TArgs&&... args
        ) = 0;
    };
}

#endif //!KLIB_FUNCTIONAL_FUNCTIONBASE_H
