#ifndef KLIB_KONGKONG_FUNCTIONAL_FUNCTIONBASE_H
#define KLIB_KONGKONG_FUNCTIONAL_FUNCTIONBASE_H

#include "base.h"

namespace klib::Kongkong::Functional
{
    template <class TResult, class... TArgs>
    struct FunctionBase {
        public:

        virtual TResult operator()(
            TArgs&&... args
        ) = 0;
    };
}

#endif //!KLIB_KONGKONG_FUNCTIONAL_FUNCTIONBASE_H