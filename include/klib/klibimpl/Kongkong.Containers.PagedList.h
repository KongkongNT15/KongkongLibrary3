#ifndef KLIB_KONGKONG_CONTAINERS_PAGEDLIST_H
#define KLIB_KONGKONG_CONTAINERS_PAGEDLIST_H

#include "base.h"
#include "Kongkong.Containers.Primitives.ContainerBase.h"
#include "Kongkong.Memory.VirtualMemoryRegion.h"

namespace klib::Kongkong::Containers
{
    template <class T>
    class PagedList final : Primitives::ContainerBase {
        public:
        using ElementType = ::std::remove_cvref_t<T>;
        using IteratorType = ElementType*;
        using ConstIteratorType = const ElementType*;

        private:

        Memory::VirtualMemoryRegion m_region;

        public:
    };
}

namespace klib::Kongkong::Containers
{

}

#endif //!KLIB_KONGKONG_CONTAINERS_PAGEDLIST_H