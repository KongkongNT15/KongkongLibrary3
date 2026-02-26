#ifndef KLIB_KONGKONG_INTERFACEVALUE_H
#define KLIB_KONGKONG_INTERFACEVALUE_H

#include "base.h"

namespace klib::Kongkong
{
    template <class TStruct>
    struct InterfaceValue<TStruct> {};

    template <class TStruct, class... TOtherStructs>
    struct InterfaceValue : InterfaceValue<TOtherStructs...> {

    };
}

#endif //!KLIB_KONGKONG_INTERFACEVALUE_H