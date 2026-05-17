#ifndef KLIB_MEMORY_PRIMITIVES_GCOBJECT_H
#define KLIB_MEMORY_PRIMITIVES_GCOBJECT_H

#include "base.h"
#include "Memory.MemoryAddress.h"
#include "Memory.Primitives.GCObjectHeader.h"

#ifdef GetObject
    #undef GetObject
#endif

#include <atomic>

namespace klib::Memory::Primitives
{
    template <>
    struct GCObject<void> {
        private:
        GCObjectHeader<> m_header;
        void* m_objectPtr;
        GCObject<>* m_previus;
        GCObject<>* m_next;
        ::std::atomic<GCHandleEntry>* m_handle;

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
        constexpr ::std::atomic<GCHandleEntry>* GetHandle() const noexcept;

        [[nodiscard]]
        constexpr void* GetValue() const noexcept;

        [[nodiscard]]
        constexpr GCObject<>* Previus() const noexcept;

        constexpr void Previus(
            GCObject<>* value
        ) noexcept;

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

namespace klib::Memory::Primitives
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

    constexpr ::std::atomic<GCHandleEntry>*
    GCObject<void>::GetHandle() const noexcept
    {
        return m_handle;
    }

    constexpr void*
    GCObject<void>::GetValue() const noexcept
    {
        return m_objectPtr;
    }

    constexpr GCObject<>*
    GCObject<void>::Previus() const noexcept
    {
        return m_previus;
    }

    constexpr void GCObject<void>::Previus(
        GCObject<>* value
    ) noexcept
    {
        m_previus = value;
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

#endif //!KLIB_MEMORY_PRIMITIVES_GCOBJECT_H
