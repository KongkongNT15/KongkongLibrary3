#ifndef KLIB_MEMORY_PRIMITIVES_HEAPOBJECTBASE_H
#define KLIB_MEMORY_PRIMITIVES_HEAPOBJECTBASE_H

#include "base.h"

#include <atomic>

namespace klib::Memory::Primitives
{
    struct HeapObjectBase {
        protected:
        using DeleteFunc = void(*)(void*);

        DeleteFunc m_destructor;
        void* m_pValue;
        ::std::atomic<size_t> m_refCount;
        
        constexpr HeapObjectBase(
            DeleteFunc func,
            void* pValue
        ) noexcept;

        public:

        constexpr size_t AddRefCount() noexcept;

        constexpr void Dispose() noexcept;

        [[nodiscard]]
        constexpr void* Get() const noexcept;

        constexpr size_t RemoveRefCount() noexcept;
    };
}

namespace klib::Memory::Primitives
{
    constexpr HeapObjectBase::HeapObjectBase(
        DeleteFunc func,
        void* pValue
    ) noexcept
        : m_destructor(func)
        , m_pValue(pValue)
        , m_refCount(1)
    {
    }

    constexpr size_t HeapObjectBase::AddRefCount() noexcept
    {
        return ++m_refCount;
    }

    constexpr void HeapObjectBase::Dispose() noexcept
    {
        m_destructor(m_pValue);
    }

    constexpr void* HeapObjectBase::Get() const noexcept
    {
        return m_pValue;
    }

    constexpr size_t HeapObjectBase::RemoveRefCount() noexcept
    {
        return --m_refCount;
    }
}

#endif //!KLIB_MEMORY_PRIMITIVES_HEAPOBJECTBASE_H