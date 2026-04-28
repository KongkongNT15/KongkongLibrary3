#ifndef KLIB_FOUNDATION_INTERFACEVALUE_H
#define KLIB_FOUNDATION_INTERFACEVALUE_H

#include "base.h"

namespace klib::Foundation
{
    template <class TStruct>
    struct InterfaceValue<TStruct> {};

    template <class TStruct, class... TOtherStructs>
    struct InterfaceValue : InterfaceValue<TOtherStructs...> {

    };
}

#endif //!KLIB_FOUNDATION_INTERFACEVALUE_H
