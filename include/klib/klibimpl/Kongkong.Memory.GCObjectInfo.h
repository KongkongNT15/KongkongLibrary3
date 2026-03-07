#ifndef KONGKONG_MEMORY_GCOBJECTINFO_H
#define KONGKONG_MEMORY_GCOBJECTINFO_H

#include "base.h"
#include "Kongkong.Memory.GCObjectInfoBase.h"

namespace klib::Kongkong::Memory
{
    template <class T>
    struct GCObjectInfo : public GCObjectInfoBase {
        public:

        using ElementType = ::std::remove_cvref_t<T>;

        constexpr GCObjectInfo(
            ElementType& value
        ) noexcept;

        void Destruct(
        ) const noexcept override;

        void MoveConstruct(
            void* from
        ) const noexcept override;
    };
}

namespace klib::Kongkong::Memory
{

    template <class T>
    constexpr GCObjectInfo<T>::GCObjectInfo(
        ElementType& value
    ) noexcept
        : GCObjectInfoBase(
            &value,
            alignof(ElementType),
            sizeof(ElementType)
        )
    {        
    }

    template <class T>
    void GCObjectInfo<T>::Destruct(
    ) const noexcept
    {
        ElementType* ep = static_cast<ElementType*>(
            this->Address
        );

        ep->~ElementType();
    }

    template <class T>
    void GCObjectInfo<T>::MoveConstruct(
        void* from
    ) const noexcept
    {
        ElementType* ep = static_cast<ElementType*>(
            this->Address
        );

        ElementType* eFrom = static_cast<ElementType*>(
            from
        );

        new (ep) ElementType(::std::move(*eFrom));
    }
}

#endif //!KONGKONG_MEMORY_GCOBJECTINFO_H