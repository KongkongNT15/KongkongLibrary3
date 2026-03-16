#ifndef KLIB_KONGKONG_CONTAINERS_PRIMITIVES_ARRAYBASE_H
#define KLIB_KONGKONG_CONTAINERS_PRIMITIVES_ARRAYBASE_H

#include "base.h"
#include "Kongkong.Containers.ArrayView.h"
#include "Kongkong.Containers.ContainerHelper.h"
#include "Kongkong.Containers.Primitives.ContainerBase.h"
#include "Kongkong.Ranges.IndexFromEnd.h"

namespace klib::Kongkong::Containers::Primitives
{
    template <class T>
    struct ArrayBase : public ContainerBase {
        public:
        using ElementType = ::std::remove_cvref_t<T>;
        using IteratorType = ElementType*;
        using ConstIteratorType = const ElementType*;
        protected:

        ElementType* m_p;

        constexpr ArrayBase() noexcept;

        constexpr ArrayBase(
            ssize_t length,
            ElementType* p
        ) noexcept;

        ArrayBase(
            ArrayBase const&
        ) = default;

        ArrayBase(
            ArrayBase&&
        ) = default;

        ArrayBase& operator=(
            ArrayBase const&
        ) = default;

        ArrayBase& operator=(
            ArrayBase&&
        ) = default;

        public:

        [[nodiscard]]
        constexpr ElementType& operator[](
            ssize_t index
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType const& operator[](
            ssize_t index
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType& operator[](
            Ranges::IndexFromEnd indexFromEnd
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType const& operator[](
            Ranges::IndexFromEnd indexFromEnd
        ) const noexcept;

        [[nodiscard]]
        constexpr IteratorType begin() noexcept;

        [[nodiscard]]
        constexpr ConstIteratorType begin() const noexcept;

        [[nodiscard]]
        constexpr IteratorType end() noexcept;

        [[nodiscard]]
        constexpr ConstIteratorType end() const noexcept;
        
        [[nodiscard]]
        constexpr bool Contains(
            ElementType const& value
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType* Data() noexcept;

        [[nodiscard]]
        constexpr const ElementType* Data() const noexcept;

        template <class TPredicate>
        constexpr void ForEach(
            TPredicate pred
        );

        [[nodiscard]]
        ElementType& Front();

        [[nodiscard]]
        ElementType const& Front() const;

        [[nodiscard]]
        ElementType& GetAt(
            ssize_t index
        );

        [[nodiscard]]
        ElementType const& GetAt(
            ssize_t index
        ) const;

        [[nodiscard]]
        ElementType& GetAtFromEnd(
            ssize_t indexFromEnd
        ) noexcept;

        [[nodiscard]]
        ElementType const& GetAtFromEnd(
            ssize_t indexFromEnd
        ) const;

        [[nodiscard]]
        constexpr ElementType& GetAtFromEndUnsafe(
            ssize_t indexFromEnd
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType const& GetAtFromEndUnsafe(
            ssize_t indexFromEnd
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType& GetAtUnsafe(
            ssize_t index
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType const& GetAtUnsafe(
            ssize_t index
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType& GetFrontUnsafe(
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType const& GetFrontUnsafe(
        ) const noexcept;

        [[nodiscard]]
        constexpr ArrayView<T> GetView() const noexcept;

        [[nodiscard]]
        constexpr ssize_t IndexOf(
            ElementType const& value
        ) const noexcept;
    };
}

namespace klib::Kongkong::Containers::Primitives
{
    template <class T>
    constexpr ArrayBase<T>::ArrayBase() noexcept
        : ContainerBase(0)
        , m_p(nullptr)
    {
    }

    template <class T>
    constexpr ArrayBase<T>::ArrayBase(
        ssize_t length,
        ElementType* p
    ) noexcept
        : ContainerBase(length)
        , m_p(p)
    {
    }

    template <class T>
    constexpr typename ArrayBase<T>::ElementType&
    ArrayBase<T>::operator[](
        ssize_t index
    ) noexcept
    {
        return m_p[index];
    }

    template <class T>
    constexpr typename ArrayBase<T>::ElementType const&
    ArrayBase<T>::operator[](
        ssize_t index
    ) const noexcept
    {
        return m_p[index];
    }

    template <class T>
    constexpr typename ArrayBase<T>::ElementType&
    ArrayBase<T>::operator[](
        Ranges::IndexFromEnd indexFromEnd
    ) noexcept
    {
        return GetAtFromEndUnsafe(indexFromEnd.Value);
    }

    template <class T>
    constexpr typename ArrayBase<T>::ElementType const&
    ArrayBase<T>::operator[](
        Ranges::IndexFromEnd indexFromEnd
    ) const noexcept
    {
        return GetAtFromEndUnsafe(indexFromEnd.Value);
    }

    template <class T>
    constexpr typename ArrayBase<T>::IteratorType
    ArrayBase<T>::begin() noexcept
    {
        return m_p;
    }

    template <class T>
    constexpr typename ArrayBase<T>::ConstIteratorType
    ArrayBase<T>::begin() const noexcept
    {
        return m_p;
    }

    template <class T>
    constexpr typename ArrayBase<T>::IteratorType
    ArrayBase<T>::end() noexcept
    {
        return m_p + this->m_length;
    }

    template <class T>
    constexpr typename ArrayBase<T>::ConstIteratorType
    ArrayBase<T>::end() const noexcept
    {
        return m_p + this->m_length;
    }

    template <class T>
    constexpr bool ArrayBase<T>::Contains(
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
    constexpr typename ArrayBase<T>::ElementType*
    ArrayBase<T>::Data() noexcept
    {
        return m_p;
    }

    template <class T>
    constexpr const typename ArrayBase<T>::ElementType*
    ArrayBase<T>::Data() const noexcept
    {
        return m_p;
    }

    template <class T>
    template <class TPredicate>
    constexpr void ArrayBase<T>::ForEach(
        TPredicate pred
    )
    {
        auto itr = begin();
        auto end = end();

        while (itr != end) {
            pred(*itr);
            ++itr;
        }
    }

    template <class T>
    typename ArrayBase<T>::ElementType&
    ArrayBase<T>::Front()
    {
        ContainerHelper::CheckLengthZero(this->m_length);
        return m_p[0];
    }

    template <class T>
    typename ArrayBase<T>::ElementType const&
    ArrayBase<T>::Front() const
    {
        ContainerHelper::CheckLengthZero(this->m_length);
        return m_p[0];
    }

    template <class T>
    typename ArrayBase<T>::ElementType&
    ArrayBase<T>::GetAt(
        ssize_t index
    )
    {
        ContainerHelper::CheckIndex(
            index,
            this->m_length
        );
        return m_p[index];
    }

    template <class T>
    typename ArrayBase<T>::ElementType const&
    ArrayBase<T>::GetAt(
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
    typename ArrayBase<T>::ElementType&
    ArrayBase<T>::GetAtFromEnd(
        ssize_t indexFromEnd
    )
    {
        ssize_t index = ContainerHelper::CheckIndexFromEnd(
            indexFromEnd,
            this->m_length
        );
        return m_p[index];
    }

    template <class T>
    typename ArrayBase<T>::ElementType const&
    ArrayBase<T>::GetAtFromEnd(
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
    constexpr typename ArrayBase<T>::ElementType&
    ArrayBase<T>::GetAtFromEndUnsafe(
        ssize_t indexFromEnd
    ) noexcept
    {
        return m_p[this->m_length - indexFromEnd];
    }

    template <class T>
    constexpr typename ArrayBase<T>::ElementType const&
    ArrayBase<T>::GetAtFromEndUnsafe(
        ssize_t indexFromEnd
    ) const noexcept
    {
        return m_p[this->m_length - indexFromEnd];
    }

    template <class T>
    constexpr typename ArrayBase<T>::ElementType&
    ArrayBase<T>::GetAtUnsafe(
        ssize_t index
    ) noexcept
    {
        return m_p[index];
    }

    template <class T>
    constexpr typename ArrayBase<T>::ElementType const&
    ArrayBase<T>::GetAtUnsafe(
        ssize_t index
    ) const noexcept
    {
        return m_p[index];
    }

    template <class T>
    constexpr typename ArrayBase<T>::ElementType&
    ArrayBase<T>::GetFrontUnsafe(
    ) noexcept
    {
        return m_p[0];
    }

    template <class T>
    constexpr typename ArrayBase<T>::ElementType const&
    ArrayBase<T>::GetFrontUnsafe(
    ) const noexcept
    {
        return m_p[0];
    }

    template <class T>
    constexpr ArrayView<T> ArrayBase<T>::GetView() const noexcept
    {
        return ArrayView<T>(
            this->m_length,
            m_p
        );
    }

    template <class T>
    constexpr ssize_t ArrayBase<T>::IndexOf(
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

#endif //!KLIB_KONGKONG_CONTAINERS_PRIMITIVES_ARRAYBASE_H