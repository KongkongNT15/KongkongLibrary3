#ifndef KLIB_KONGKONG_MEMORY_PRIMITIVES_GCOBJECTFLAG_H
#define KLIB_KONGKONG_MEMORY_PRIMITIVES_GCOBJECTFLAG_H

#include "base.h"

namespace klib::Kongkong::Memory::Primitives
{
    enum struct GCObjectFlag {
        Normal = 0x0,
        Pinned = 0x1,
        

    };
}

#endif //!KLIB_KONGKONG_MEMORY_PRIMITIVES_GCOBJECTFLAG_H