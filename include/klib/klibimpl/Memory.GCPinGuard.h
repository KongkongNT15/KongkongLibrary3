#ifndef KLIB_MEMORY_GCPINGUARD_H
#define KLIB_MEMORY_GCPINGUARD_H

#include "base.h"
#include "Memory.GCHandle.h"
#include "Memory.Primitives.GCHandleEntry.h"

#include <atomic>

namespace klib::Memory
{
    template <class T>
    struct GCPinGuard final {
        public:
        private:
        ::std::atomic<Primitives::GCHandleEntry>* m_handleEntry;
        T* m_p;

        GCPinGuard(
            ::std::nullptr_t
        ) = delete;

        GCPinGuard(
            ::std::atomic<Primitives::GCHandleEntry>* objectPtr
        ) noexcept;

        ~GCPinGuard();

        [[nodiscard]]
        constexpr T* operator->() const noexcept;
    };
}

namespace klib::Memory
{
    template <class T>
    GCPinGuard<T>::GCPinGuard(
        ::std::atomic<Primitives::GCHandleEntry>* objectPtr
    ) noexcept
        : m_handleEntry(objectPtr)
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
    constexpr T*
    GCPinGuard<T>::operator->() const noexcept
    {
        return m_p;
    }
}

#endif //!KLIB_MEMORY_GCPINGUARD_H
