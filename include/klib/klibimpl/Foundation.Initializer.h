#ifndef KLIB_FOUNDATION_INITIALIZER_H
#define KLIB_FOUNDATION_INITIALIZER_H

#include "base.h"
#include "Foundation.StatelessType.h"

namespace klib::Foundation
{
    class Initializer final : public StatelessType {
        public:
        
        template <class TFunc>
        Initializer(
            TFunc&& func
        );
    };
}

namespace klib::Foundation
{
    template <class TFunc>
    Initializer::Initializer(
        TFunc&& func
    )
    {
        func();
    }
}

#endif //!KLIB_FOUNDATION_INITIALIZER_H
