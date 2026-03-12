#ifndef KONGKONG_MEMORY_GCOBJECTHEADER_PRIMITIVES_H
#define KONGKONG_MEMORY_GCOBJECTHEADER_PRIMITIVES_H

#include "base.h"
#include "Kongkong.Memory.Primitives.GCObjectHeaderBase.h"

namespace klib::Kongkong::Memory::Primitives
{
    template <class T>
    struct GCObjectHeader : public GCObjectHeaderBase {
        public:

        using ElementType = ::std::remove_cvref_t<T>;

        constexpr GCObjectHeader(
        ) noexcept;

        void Destruct(
            void* dest
        ) const noexcept override;

        void MoveConstruct(
            void* dest,
            void* from
        ) const noexcept override;
    };
}

namespace klib::Kongkong::Memory::Primitives
{

    template <class T>
    constexpr GCObjectHeader<T>::GCObjectHeader(
    ) noexcept
        : GCObjectHeaderBase(
            alignof(ElementType),
            sizeof(ElementType)
        )
    {        
    }

    template <class T>
    void GCObjectHeader<T>::Destruct(
        void* dest
    ) const noexcept
    {
        ElementType* ep = static_cast<ElementType*>(
            dest
        );

        ep->~ElementType();
    }

    template <class T>
    void GCObjectHeader<T>::MoveConstruct(
        void* dest,
        void* from
    ) const noexcept
    {
        ElementType* ep = static_cast<ElementType*>(
            dest
        );

        ElementType* eFrom = static_cast<ElementType*>(
            from
        );

        new (ep) ElementType(::std::move(*eFrom));
    }
}

#endif //!KONGKONG_MEMORY_GCOBJECTHEADER_PRIMITIVES_H