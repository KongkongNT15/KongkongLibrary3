#ifndef KLIB_KONGKONG_MEMORY_GCOBJECT_H
#define KLIB_KONGKONG_MEMORY_GCOBJECT_H

#include "base.h"
#include "Kongkong.Memory.GCObjectBase.h"

namespace klib::Kongkong::Memory
{
    template <class T>
    struct GCObject final : private GCObjectBase {
    public:
        using Type = typename ::std::remove_cvref_t<T>;

    private:

    public:
        Type Value;
    };
}

#endif //!KLIB_KONGKONG_MEMORY_GCOBJECT_H