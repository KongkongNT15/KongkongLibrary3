#ifndef KLIB_INTERFACEVALUE_H
#define KLIB_INTERFACEVALUE_H

#include "base.h"

namespace klib
{
    template <class TStruct>
    struct InterfaceValue<TStruct> {};

    template <class TStruct, class... TOtherStructs>
    struct InterfaceValue : InterfaceValue<TOtherStructs...> {

    };
}

#endif //!KLIB_INTERFACEVALUE_H
