#ifndef KLIB_KONGKONG_MEMORY_PRIMITIVES_GCOBJECTFLAG_H
#define KLIB_KONGKONG_MEMORY_PRIMITIVES_GCOBJECTFLAG_H

#include "base.h"

namespace klib::Kongkong::Memory::Primitives
{
    enum struct GCObjectFlag : int16_t {
        Normal    = 0x0, // フラグなし
        Pinned    = 0x1, // こいつは回収するとまずい！！！
        Marked    = 0x2, // 回収フラグ
    };

    KLIB_CREATE_ENUM_CREATE_OPERATOR_AND_OR(GCObjectFlag)
}

#endif //!KLIB_KONGKONG_MEMORY_PRIMITIVES_GCOBJECTFLAG_H