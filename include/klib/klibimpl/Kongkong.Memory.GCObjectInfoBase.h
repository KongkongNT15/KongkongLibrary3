#ifndef KONGKONG_MEMORY_GCOBJECTINFOBASE_H
#define KONGKONG_MEMORY_GCOBJECTINFOBASE_H

#include "base.h"

namespace klib::Kongkong::Memory
{
    struct GCObjectInfoBase {
        template <class T>
        friend struct GCObjectInfo;

        private:

        constexpr GCObjectInfoBase(
            void* address,
            ssize_t alignment,
            ssize_t size
        ) noexcept;

        GCObjectInfoBase(
            GCObjectInfoBase const&
        ) = default;

        GCObjectInfoBase(
            GCObjectInfoBase&&
        ) = default;

        GCObjectInfoBase& operator=(
            GCObjectInfoBase const&
        ) = default;

        GCObjectInfoBase& operator=(
            GCObjectInfoBase&&
        ) = default;

        public:

        void* Address;
        ssize_t Alignment;
        ssize_t Size;

        virtual void Destruct(
        ) const noexcept = 0;

        virtual void MoveConstruct(
            void* from
        ) const noexcept = 0;
    };
}

namespace klib::Kongkong::Memory
{
    constexpr GCObjectInfoBase::GCObjectInfoBase(
        void* address,
        ssize_t alignment,
        ssize_t size
    ) noexcept
        : Address(address)
        , Alignment(alignment)
        , Size(size)
    {        
    }
}

#endif //!KONGKONG_MEMORY_GCOBJECTINFOBASE_H