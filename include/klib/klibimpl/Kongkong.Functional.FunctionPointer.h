#ifndef KLIB_KONGKONG_FUNCTIONAL_FUNCTIONPOINTER_H
#define KLIB_KONGKONG_FUNCTIONAL_FUNCTIONPOINTER_H

#include "base.h"
#include "Kongkong.Functional.FunctionPointer.h"

namespace klib::Kongkong::Functional
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

namespace klib::Kongkong::Functional
{

}

#endif //!KLIB_KONGKONG_FUNCTIONAL_FUNCTIONPOINTER_H