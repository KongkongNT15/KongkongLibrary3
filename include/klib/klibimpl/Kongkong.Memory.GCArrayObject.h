#ifndef KLIB_KONGKONG_MEMORY_GCARRAYOBJECT_H
#define KLIB_KONGKONG_MEMORY_GCARRAYOBJECT_H

#include "base.h"

namespace klib::Kongkong::Memory
{
    template <class T>
    struct GCArrayObject final {
        public:

        using ElementType = ::std::remove_cvref_t<T>;

        [[nodiscard]]
        static constexpr ssize_t GetArraySize(
            ssize_t length
        ) noexcept;

        [[nodiscard]]
        static ElementType* GetArrayPointer(
            GCArrayObject* p
        ) noexcept;

        alignas(alignof(ElementType)) byte m_placeHolder;
    };
}

namespace klib::Kongkong::Memory
{
    template <class T>
    constexpr ssize_t GCArrayObject<T>::GetArraySize(
        ssize_t length
    ) noexcept
    {
        sizeof(GCArrayObject<T>) - sizeof(byte) + sizeof(ElementType) * length;
    }

    template <class T>
    typename GCArrayObject<T>::ElementType*
    GCArrayObject<T>::GetArrayPointer(
        GCArrayObject<T>* p
    ) noexcept
    {
        void* pVoid = p + 1;
        byte* pByte = static_cast<byte*>(pVoid) - 1;
        pVoid = pByte;

        return static_cast<ElementType*>(pVoid);
    }
}

#endif //!KLIB_KONGKONG_MEMORY_GCARRAYOBJECT_H