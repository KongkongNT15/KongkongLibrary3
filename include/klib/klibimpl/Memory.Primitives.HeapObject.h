#ifndef KLIB_MEMORY_PRIMITIVES_HEAPOBJECT_H
#define KLIB_MEMORY_PRIMITIVES_HEAPOBJECT_H

#include "base.h"
#include "Memory.Primitives.HeapObjectBase.h"

namespace klib::Memory::Primitives
{
    template <class T>
    struct HeapObject final : public HeapObjectBase {
        public:

        using Type = T;

        private:

        static constexpr void Delete(
            void* pValue
        );

        public:

        Type Value;

        template <class... TArgs>
        constexpr HeapObject(
            TArgs&&... args
        );
    };
}

namespace klib::Memory::Primitives
{
    template <class T>
    constexpr void HeapObject<T>::Delete(
        void* pValue
    )
    {
        static_cast<Type*>(pValue)->~Type();
    }

    template <class T>
    template <class... TArgs>
    constexpr HeapObject<T>::HeapObject(
        TArgs&&... args
    )
        : HeapObjectBase(
            Delete,
            &Value
        ),
        Value(
            ::std::forward<TArgs>(args)...
        )
    {
    }
}

#endif //!KLIB_MEMORY_PRIMITIVES_HEAPOBJECT_H