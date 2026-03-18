#ifndef KLIB_KONGKONG_INITIALIZER_H
#define KLIB_KONGKONG_INITIALIZER_H

#include "base.h"

namespace klib::Kongkong
{
    class Initializer final {
        
        template <class TFunc>
        Initializer(
            TFunc&& func
        );
    };
}

namespace klib::Kongkong
{
    template <class TFunc>
    Initializer::Initializer(
        TFunc&& func
    )
    {
        func();
    }
}

#endif //!KLIB_KONGKONG_INITIALIZER_H