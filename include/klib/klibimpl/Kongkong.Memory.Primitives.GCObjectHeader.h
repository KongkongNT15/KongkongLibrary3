#ifndef KONGKONG_MEMORY_PRIMITIVES_GCOBJECTHEADER_H
#define KONGKONG_MEMORY_PRIMITIVES_GCOBJECTHEADER_H

#include "base.h"

namespace klib::Kongkong::Memory::Primitives
{
    template <>
    struct GCObjectHeader<void> {
        template <class T>
        friend struct GCObjectHeader;

        friend GCHandleTable;

        private:

        using DestructFuncType = void(*)(void*);
        using MoveFuncType = void(*)(void*, void*);

        DestructFuncType m_destruct;
        MoveFuncType m_move;
        ssize_t m_alignment;
        ssize_t m_size;

        constexpr GCObjectHeader(
            DestructFuncType destruct,
            MoveFuncType move,
            ssize_t alignment,
            ssize_t size
        ) noexcept;

        GCObjectHeader(
            GCObjectHeader const&
        ) = default;

        GCObjectHeader(
            GCObjectHeader&&
        ) = default;

        GCObjectHeader& operator=(
            GCObjectHeader const&
        ) = default;

        GCObjectHeader& operator=(
            GCObjectHeader&&
        ) = default;

        public:
        [[nodiscard]]
        constexpr ssize_t Alignment() const noexcept;

        [[nodiscard]]
        constexpr ssize_t Size() const noexcept;

        void Destruct(
            void* dest
        ) const noexcept;

        void MoveConstruct(
            void* dest,
            void* from
        ) const noexcept;
    };

    template <class T>
    struct GCObjectHeader : public GCObjectHeader<void> {

        static void do_destruct(
            void* dest
        ) noexcept;

        static void do_move(
            void* dest,
            void* from
        ) noexcept;

        public:

        using ElementType = ::std::remove_cvref_t<T>;

        constexpr GCObjectHeader(
        ) noexcept;
    };
}

namespace klib::Kongkong::Memory::Primitives
{
    constexpr GCObjectHeader<void>::GCObjectHeader(
        DestructFuncType destruct,
        MoveFuncType move,
        ssize_t alignment,
        ssize_t size
    ) noexcept
        : m_destruct(destruct)
        , m_move(move)
        , m_alignment(alignment)
        , m_size(size)
    {        
    }

    constexpr ssize_t GCObjectHeader<void>::Alignment() const noexcept
    {
        return m_alignment;
    }

    constexpr ssize_t GCObjectHeader<void>::Size() const noexcept
    {
        return m_size;
    }

    inline void GCObjectHeader<void>::Destruct(
        void* dest
    ) const noexcept
    {
        m_destruct(dest);
    }

    inline void GCObjectHeader<void>::MoveConstruct(
        void* dest,
        void* from
    ) const noexcept
    {
        m_move(dest, from);
    }

    template <class T>
    void GCObjectHeader<T>::do_destruct(
        void* dest
    ) noexcept
    {
        ElementType* ep = static_cast<ElementType*>(
            dest
        );

        ep->~ElementType();
    }

    template <class T>
    void GCObjectHeader<T>::do_move(
        void* dest,
        void* from
    ) noexcept
    {
        ElementType* ep = static_cast<ElementType*>(
            dest
        );

        ElementType* eFrom = static_cast<ElementType*>(
            from
        );

        new (ep) ElementType(::std::move(*eFrom));
    }

    template <class T>
    constexpr GCObjectHeader<T>::GCObjectHeader(
    ) noexcept
        : GCObjectHeader<void>(
            do_destruct,
            do_move,
            alignof(ElementType),
            sizeof(ElementType)
        )
    {        
    }
}

#endif //!KONGKONG_MEMORY_PRIMITIVES_GCOBJECTHEADER_H