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
}

#endif //!KLIB_MEMORY_PRIMITIVES_HEAPOBJECTBASE_H