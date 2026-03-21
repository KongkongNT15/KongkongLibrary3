#ifndef KLIB_KONGKONG_CONTAINERS_ARRAYVIEW_H
#define KLIB_KONGKONG_CONTAINERS_ARRAYVIEW_H

#include "base.h"
#include "Kongkong.Containers.ContainerHelper.h"
#include "Kongkong.Containers.Primitives.ContainerBase.h"
#include "Kongkong.Ranges.IndexFromEnd.h"

namespace klib::Kongkong::Containers
{
    template <class T>
    struct ArrayView final : public Primitives::ContainerBase {
        public:
        using ElementType = ::std::remove_cvref_t<T>;
        using IteratorType = ElementType*;
        using ConstIteratorType = const ElementType*;
        protected:

        const ElementType* m_p;
        
        public:

        constexpr ArrayView() noexcept;

        constexpr ArrayView(
            ssize_t length,
            const ElementType* p
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType const& operator[](
            ssize_t index
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType const& operator[](
            Ranges::IndexFromEnd indexFromEnd
        ) const noexcept;

        [[nodiscard]]
        constexpr ConstIteratorType begin() const noexcept;

        [[nodiscard]]
        constexpr ConstIteratorType end() const noexcept;

        [[nodiscard]]
        ElementType const& Back() const;
        
        [[nodiscard]]
        constexpr bool Contains(
            ElementType const& value
        ) const noexcept;

        [[nodiscard]]
        constexpr const ElementType* Data() const noexcept;

        [[nodiscard]]
        ElementType const& Front() const;

        [[nodiscard]]
        ElementType const& GetAt(
            ssize_t index
        ) const;

        [[nodiscard]]
        ElementType const& GetAt(
            Ranges::IndexFromEnd indexFromEnd
        ) const;

        [[nodiscard]]
        ElementType const& GetAtFromEnd(
            ssize_t indexFromEnd
        ) const;

        [[nodiscard]]
        constexpr ElementType const& GetAtFromEndUnsafe(
            ssize_t index
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType const& GetAtUnsafe(
            ssize_t index
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType const& GetAtUnsafe(
            Ranges::IndexFromEnd indexFromEnd
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType const& GetBackUnsafe(
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType const& GetFrontUnsafe(
        ) const noexcept;

        [[nodiscard]]
        constexpr ArrayView GetView() const noexcept;

        [[nodiscard]]
        constexpr ArrayView GetViewUnsafe(
            ssize_t offset
        ) const noexcept;

        [[nodiscard]]
        constexpr ArrayView GetViewUnsafe(
            ssize_t offset,
            ssize_t end
        ) const noexcept;

        [[nodiscard]]
        constexpr ssize_t IndexOf(
            ElementType const& value
        ) const noexcept;
    };
}

namespace klib::Kongkong::Containers
{
    template <class T>
    constexpr ArrayView<T>::ArrayView() noexcept
        : ContainerBase(0)
        , m_p(nullptr)
    {
    }

    template <class T>
    constexpr ArrayView<T>::ArrayView(
        ssize_t length,
        const ElementType* p
    ) noexcept
        : ContainerBase(length)
        , m_p(p)
    {
    }

    template <class T>
    constexpr typename ArrayView<T>::ElementType const&
    ArrayView<T>::operator[](
        ssize_t index
    ) const noexcept
    {
        return m_p[index];
    }

    template <class T>
    constexpr typename ArrayView<T>::ElementType const&
    ArrayView<T>::operator[](
        Ranges::IndexFromEnd indexFromEnd
    ) const noexcept
    {
        return GetAtFromEndUnsafe(indexFromEnd.Value);
    }

    template <class T>
    constexpr typename ArrayView<T>::ConstIteratorType
    ArrayView<T>::begin() const noexcept
    {
        return m_p;
    }

    template <class T>
    constexpr typename ArrayView<T>::ConstIteratorType
    ArrayView<T>::end() const noexcept
    {
        return m_p + this->m_length;
    }

    template <class T>
    typename ArrayView<T>::ElementType const&
    ArrayView<T>::Back() const
    {
        ContainerHelper::CheckLengthZero(m_length);
        return m_p[m_length - 1];
    }

    template <class T>
    constexpr bool ArrayView<T>::Contains(
        ElementType const& value
    ) const noexcept
    {
        return ContainerHelper::ContainsUnsafe(
            this->m_length,
            m_p,
            value
        );
    }

    template <class T>
    constexpr const typename ArrayView<T>::ElementType*
    ArrayView<T>::Data() const noexcept
    {
        return m_p;
    }

    template <class T>
    typename ArrayView<T>::ElementType const&
    ArrayView<T>::Front() const
    {
        ContainerHelper::CheckLengthZero(this->m_length);
        return m_p[0];
    }

    template <class T>
    typename ArrayView<T>::ElementType const&
    ArrayView<T>::GetAt(
        ssize_t index
    ) const
    {
        ContainerHelper::CheckIndex(
            index,
            this->m_length
        );
        return m_p[index];
    }

    template <class T>
    typename ArrayView<T>::ElementType const&
    ArrayView<T>::GetAt(
        Ranges::IndexFromEnd indexFromEnd
    ) const
    {
        return GetAtFromEnd(indexFromEnd.Value);
    }

    template <class T>
    typename ArrayView<T>::ElementType const&
    ArrayView<T>::GetAtFromEnd(
        ssize_t indexFromEnd
    ) const
    {
        ssize_t index = ContainerHelper::CheckIndexFromEnd(
            indexFromEnd,
            this->m_length
        );
        return m_p[index];
    }

    template <class T>
    constexpr typename ArrayView<T>::ElementType const&
    ArrayView<T>::GetAtFromEndUnsafe(
        ssize_t index
    ) const noexcept
    {
        return m_p[this->m_length - index];
    }

    template <class T>
    constexpr typename ArrayView<T>::ElementType const&
    ArrayView<T>::GetAtUnsafe(
        ssize_t index
    ) const noexcept
    {
        return m_p[index];
    }

    template <class T>
    constexpr typename ArrayView<T>::ElementType const&
    ArrayView<T>::GetAtUnsafe(
        Ranges::IndexFromEnd indexFromEnd
    ) const noexcept
    {
        return GetAtFromEndUnsafe(indexFromEnd.Value);
    }

    template <class T>
    constexpr typename ArrayView<T>::ElementType const&
    ArrayView<T>::GetBackUnsafe(
    ) const noexcept
    {
        return m_p[m_length - 1];
    }

    template <class T>
    constexpr typename ArrayView<T>::ElementType const&
    ArrayView<T>::GetFrontUnsafe(
    ) const noexcept
    {
        return m_p[0];
    }

    template <class T>
    constexpr ArrayView<T>
    ArrayView<T>::GetView() const noexcept
    {
        return *this;
    }

    template <class T>
    constexpr ArrayView<T> ArrayView<T>::GetViewUnsafe(
        ssize_t offset
    ) const noexcept
    {
        return GetViewUnsafe(
            offset,
            this->m_length
        );
    }

    template <class T>
    constexpr ArrayView<T> ArrayView<T>::GetViewUnsafe(
        ssize_t offset,
        ssize_t end
    ) const noexcept
    {
        return ArrayView<T>(
            end,
            m_p + offset
        );
    }

    template <class T>
    constexpr ssize_t ArrayView<T>::IndexOf(
        ElementType const& value
    ) const noexcept
    {
        return ContainerHelper::IndexOfUnsafe(
            this->m_length,
            m_p,
            value
        );
    }
}

#endif //!KLIB_KONGKONG_CONTAINERS_ARRAYVIEW_H