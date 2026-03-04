#ifndef KONGKONG_MEMORY_GCOBJECTINFO_H
#define KONGKONG_MEMORY_GCOBJECTINFO_H

#include "base.h"

namespace klib::Kongkong::Memory
{
    struct GCObjectInfo {
        public:
        using DestructorType = void(*)(void*);

        template <class T>
        static constexpr void DefaultDestruct(
            void* p
        ) noexcept;

        void* Address;
        ssize_t Alignment;
        DestructorType Destructor;
        ssize_t Size;

        template <class T>
        constexpr GCObjectInfo(
            T& value
        ) noexcept;
    };
}

namespace klib::Kongkong::Memory
{
    template <class T>
    constexpr void GCObjectInfo::DefaultDestruct(
        void* p
    ) noexcept
    {
        T* pT = static_cast<T*>(p);

        pT->~T();
    }

    template <class T>
    constexpr GCObjectInfo::GCObjectInfo(
        T& value
    ) noexcept
        : Address(&value)
        , Alignment(alignof(T))
        , Destructor(DefaultDestruct<T>)
        , Size(sizeof(T))
    {        
    }
}

#endif //!KONGKONG_MEMORY_GCOBJECTINFO_H