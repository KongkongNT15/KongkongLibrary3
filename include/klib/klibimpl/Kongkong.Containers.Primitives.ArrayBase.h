#ifndef KLIB_KONGKONG_CONTAINERS_PRIMITIVES_ARRAYBASE_H
#define KLIB_KONGKONG_CONTAINERS_PRIMITIVES_ARRAYBASE_H

#include "base.h"
#include "Kongkong.Containers.ContainerHelper.h"
#include "Kongkong.Containers.Primitives.ContainerBase.h"

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
}

#endif //!KLIB_KONGKONG_CONTAINERS_PRIMITIVES_ARRAYBASE_H