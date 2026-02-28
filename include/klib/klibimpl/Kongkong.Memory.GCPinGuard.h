#ifndef KLIB_KONGKONG_MEMORY_GCPINGUARD_H
#define KLIB_KONGKONG_MEMORY_GCPINGUARD_H

#include "base.h"
#include "Kongkong.Memory.GCObject.h"

namespace klib::Kongkong::Memory
{
    template <class T>
    struct GCPinGuard final {
        private:
        GCObject<T>* m_objectPtr;

        public:

        GCPinGuard(
            ::std::nullptr_t
        ) = delete;

        GCPinGuard(
            GCObject<T>* objectPtr
        ) noexcept;

        ~GCPinGuard();

        [[nodiscard]]
        constexpr GCObject<T>* operator->() const noexcept;
    };
}

namespace klib::Kongkong::Memory
{
    template <class T>
    GCPinGuard<T>::GCPinGuard(
        GCObject<T>* objectPtr
    ) noexcept
        : m_objectPtr(objectPtr)
    {
#warning GCPinGuard<T>::GCPinGuard()
        // TODO: ここに処理を書きます
    }

    template <class T>
    GCPinGuard<T>::~GCPinGuard(
    )
    {
#warning GCPinGuard<T>::~GCPinGuard()
        // TODO: ここに処理を書きます
    }

    template <class T>
    constexpr GCObject<T>*
    GCPinGuard<T>::operator->() const noexcept
    {
        return m_objectPtr;
    }
}

#endif //!KLIB_KONGKONG_MEMORY_GCPINGUARD_H