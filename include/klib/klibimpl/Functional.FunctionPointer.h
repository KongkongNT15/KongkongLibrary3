#ifndef KLIB_FUNCTIONAL_FUNCTIONPOINTER_H
#define KLIB_FUNCTIONAL_FUNCTIONPOINTER_H

#include "base.h"
#include "Functional.FunctionPointer.h"

namespace klib::Functional
{
    template <class TResult, class... TArgs>
    struct FunctionPointer {
        public:
        using FuncType = TResult(*)(TArgs&&...);
        private:

        FuncType m_funcPointer;

        public:

        constexpr FunctionPointer(
            FuncType func
        ) noexcept;

        TResult operator()(
            TArgs&&... args
        ) override;
    };
}

namespace klib::Functional
{

}

#endif //!KLIB_FUNCTIONAL_FUNCTIONPOINTER_H
