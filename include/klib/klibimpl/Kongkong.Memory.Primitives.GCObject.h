#ifndef KLIB_KONGKONG_MEMORY_PRIMITIVES_GCOBJECT_H
#define KLIB_KONGKONG_MEMORY_PRIMITIVES_GCOBJECT_H

#include "base.h"
#include "Kongkong.Memory.MemoryAddress.h"
#include "Kongkong.Memory.Primitives.GCObjectHeader.h"

namespace klib::Kongkong::Memory::Primitives
{
    template <>
    struct GCObject<void> {
        private:
        GCObjectHeader<> m_header;
        void* m_objectPtr;
        GCObject<>* m_next;

        public:

        [[nodiscard]]
        static constexpr GCObject<>* GetObject(
            GCObjectHeader<>* header
        ) noexcept;

        constexpr GCObject(
            GCObjectHeader<> header,
            void* objectPtr
        ) noexcept;

        GCObject(
            GCObject&& other
        ) noexcept;

        ~GCObject();

        [[nodiscard]]
        constexpr GCObject<>* Next() const noexcept;

        constexpr void Next(
            GCObject<>* value
        ) noexcept;
    };

    template <class T>
    struct GCObject : public GCObject<void> {
        public:
        using ElementType = typename ::std::remove_cvref_t<T>;

        ElementType Value;

        template <class... TArgs>
        constexpr GCObject(
            TArgs&&... args
        );
    };
}

namespace klib::Kongkong::Memory::Primitives
{
    constexpr GCObject<>*
    GCObject<void>::GetObject(
        GCObjectHeader<>* header
    ) noexcept
    {
        return reinterpret_cast<GCObject<>*>(header);
    }

    constexpr GCObject<void>::GCObject(
        GCObjectHeader<> header,
        void* objectPtr
    ) noexcept
        : m_header(header)
        , m_objectPtr(objectPtr)
        , m_next(nullptr)
    {
    }

    inline GCObject<void>::GCObject(
        GCObject<void>&& other
    ) noexcept
        : m_header(::std::move(other.m_header))
        , m_objectPtr(
            MemoryAddress::AlignUpUnsafe(
                this + 1,
                other.m_header.Alignment()
            )
        )
    {
        m_header.MoveConstruct(m_objectPtr, other.m_objectPtr);
    }

    inline GCObject<void>::~GCObject()
    {
        m_header.Destruct(m_objectPtr);
    }

    constexpr GCObject<>*
    GCObject<void>::Next() const noexcept
    {
        return m_next;
    }

    constexpr void GCObject<void>::Next(
        GCObject<>* value
    ) noexcept
    {
        m_next = value;
    }
    
    template <class T>
    template <class... TArgs>
    constexpr GCObject<T>::GCObject(
        TArgs&&... args
    )
        : GCObject<void>(
            GCObjectHeader<ElementType>(),
            &Value
        )
        , Value(::std::forward<TArgs>(args)...)
    {
    }

}

#endif //!KLIB_KONGKONG_MEMORY_PRIMITIVES_GCOBJECT_H