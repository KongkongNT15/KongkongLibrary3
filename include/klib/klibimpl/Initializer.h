#ifndef KLIB_INITIALIZER_H
#define KLIB_INITIALIZER_H

#include "base.h"
#include "StatelessType.h"

namespace klib
{
    class Initializer final : public StatelessType {
        
        template <class TFunc>
        Initializer(
            TFunc&& func
        );
    };
}

namespace klib
{
    template <class TFunc>
    Initializer::Initializer(
        TFunc&& func
    )
    {
        func();
    }
}

#endif //!KLIB_INITIALIZER_H
