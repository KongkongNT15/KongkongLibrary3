#ifndef KONGKONG_MEMORY_GCOOBJECTHEADERBASE_PRIMITIVES_H
#define KONGKONG_MEMORY_GCOOBJECTHEADERBASE_PRIMITIVES_H

#include "base.h"

namespace klib::Kongkong::Memory::Primitives
{
    struct GCObjectHeaderBase {
        template <class T>
        friend struct GCObjectHeader;

        private:

        constexpr GCObjectHeaderBase(
            ssize_t alignment,
            ssize_t size
        ) noexcept;

        GCObjectHeaderBase(
            GCObjectHeaderBase const&
        ) = default;

        GCObjectHeaderBase(
            GCObjectHeaderBase&&
        ) = default;

        GCObjectHeaderBase& operator=(
            GCObjectHeaderBase const&
        ) = default;

        GCObjectHeaderBase& operator=(
            GCObjectHeaderBase&&
        ) = default;

        public:
        ssize_t Alignment;
        ssize_t Size;

        virtual void Destruct(
            void* dest
        ) const noexcept = 0;

        virtual void MoveConstruct(
            void* dest,
            void* from
        ) const noexcept = 0;
    };
}

namespace klib::Kongkong::Memory::Primitives
{
    constexpr GCObjectHeaderBase::GCObjectHeaderBase(
        ssize_t alignment,
        ssize_t size
    ) noexcept
        : Alignment(alignment)
        , Size(size)
    {        
    }
}

#endif //!KONGKONG_MEMORY_GCOOBJECTHEADERBASE_PRIMITIVES_H