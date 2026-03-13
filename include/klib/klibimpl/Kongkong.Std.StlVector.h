#ifndef KLIB_KONGKONG_STD_STLVECTOR_H
#define KLIB_KONGKONG_STD_STLVECTOR_H

#include "base.h"
#include "Kongkong.Containers.ContainerHelper.h"
#include <vector>

#define KLIB_CLASS_TEMPLATE_DEF template <class T, class TAllocator>
#define KLIB_CLASS_TEMPLATE_PARAM T, TAllocator

namespace klib::Kongkong::Std
{
    KLIB_CLASS_TEMPLATE_DEF
    struct StlVector {
        public:
        using Base = ::std::vector<T, TAllocator>;
        using ElementType = typename Base::value_type;
        using IteratorType = typename Base::iterator;
        using ConstIteratorType = typename Base::const_iterator;
        private:
        ::std::vector<T, TAllocator> m_vector;

        public:

        template <class... TArgs>
        constexpr StlVector(
            TArgs&&... args
        ) noexcept(
            noexcept(Base(::std::forward<TArgs>(args)...))
        );

        StlVector& operator=(
            StlVector const&
        ) = default;

        StlVector& operator=(
            StlVector&&
        ) = default;

        StlVector& operator=(
            Base const& other
        ) noexcept(::std::is_nothrow_copy_assignable_v<Base>);

        StlVector& operator=(
            Base&& other
        ) noexcept(::std::is_nothrow_move_assignable_v<Base>);

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

        constexpr void Append(
            ElementType const& value
        );

        constexpr void Append(
            ElementType&& value
        );

        constexpr void AppendRangeUnsafe(
            ssize_t length,
            const ElementType* p
        );

        constexpr void Clear() noexcept;

        [[nodiscard]]
        constexpr bool Contains(
            ElementType const& value
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType* Data() noexcept;

        [[nodiscard]]
        constexpr const ElementType* Data() const noexcept;

        template <class... TArgs>
        constexpr void Emplace(
            TArgs&&... args
        );

        template <class TPredicate>
        constexpr void ForEach(
            TPredicate pred
        );

        [[nodiscard]]
        constexpr ssize_t IndexOf(
            ElementType const& value
        ) const noexcept;

        constexpr IteratorType Insert(
            IteratorType position,
            ElementType const& value
        );

        constexpr IteratorType Insert(
            IteratorType position,
            ElementType&& value
        );

        constexpr IteratorType Insert(
            ssize_t position,
            ElementType const& value
        );

        constexpr IteratorType Insert(
            ssize_t position,
            ElementType&& value
        );

        [[nodiscard]]
        constexpr bool IsEmpty() const noexcept;

        [[nodiscard]]
        constexpr ssize_t Length() const noexcept;

        template <class TFunc>
        constexpr ssize_t RemoveIf(
            TFunc pred
        );

        [[nodiscard]]
        constexpr Base& Vector() noexcept;

        [[nodiscard]]
        constexpr Base const& Vector() const noexcept;
    };

    KLIB_CLASS_TEMPLATE_DEF
    [[nodiscard]]
    constexpr bool operator==(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept;

    KLIB_CLASS_TEMPLATE_DEF
    [[nodiscard]]
    constexpr bool operator!=(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept;

    KLIB_CLASS_TEMPLATE_DEF
    [[nodiscard]]
    constexpr bool operator<(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept;

    KLIB_CLASS_TEMPLATE_DEF
    [[nodiscard]]
    constexpr bool operator<=(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept;

    KLIB_CLASS_TEMPLATE_DEF
    [[nodiscard]]
    constexpr bool operator>(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept;

    KLIB_CLASS_TEMPLATE_DEF
    [[nodiscard]]
    constexpr bool operator>=(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept;

    KLIB_CLASS_TEMPLATE_DEF
    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept;
}

namespace klib::Kongkong::Std
{
    KLIB_CLASS_TEMPLATE_DEF
    template <class... TArgs>
    constexpr StlVector<KLIB_CLASS_TEMPLATE_PARAM>::StlVector(
        TArgs&&... args
    ) noexcept(noexcept(Base(::std::forward<TArgs>(args)...)))
        : m_vector(::std::forward<TArgs>(args)...)
    {
    }

    KLIB_CLASS_TEMPLATE_DEF
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>&
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::operator=(
        Base const& other
    ) noexcept(::std::is_nothrow_copy_assignable_v<Base>)
    {
        m_vector = other;

        return *this;
    }

    KLIB_CLASS_TEMPLATE_DEF
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>&
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::operator=(
        Base&& other
    ) noexcept(::std::is_nothrow_move_assignable_v<Base>)
    {
        m_vector = ::std::move(other);

        return *this;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::operator[](
        ssize_t index
    ) noexcept
    {
        return m_vector.operator[](index);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::operator[](
        ssize_t index
    ) const noexcept
    {
        return m_vector.operator[](index);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::IteratorType
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::begin() noexcept
    {
        return m_vector.begin();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::ConstIteratorType
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::begin() const noexcept
    {
        return m_vector.begin();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::IteratorType
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::end() noexcept
    {
        return m_vector.end();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::ConstIteratorType
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::end() const noexcept
    {
        return m_vector.end();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr void StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Append(
        ElementType const& value
    )
    {
        m_vector.push_back(value);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr void StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Append(
        ElementType&& value
    )
    {
        m_vector.push_back(::std::move(value));
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr void
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Clear() noexcept
    {
        m_vector.clear();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr bool StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Contains(
        ElementType const& value
    ) const noexcept
    {
        for (auto const& v : m_vector) {
            if (v == value) return true;
        }

        return false;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::ElementType*
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Data() noexcept
    {
        return m_vector.data();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr const typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::ElementType*
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Data() const noexcept
    {
        return m_vector.data();
    }

    KLIB_CLASS_TEMPLATE_DEF
    template <class... TArgs>
    constexpr void StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Emplace(
        TArgs&&... args
    )
    {
        m_vector.emplace_back(
            ::std::forward<TArgs>(args)...
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    template <class TPredicate>
    constexpr void
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::ForEach(
        TPredicate pred
    )
    {
        auto itr = m_vector.begin();
        auto end = m_vector.end();

        while (itr != end) {
            pred(*itr);
            ++itr;
        }
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr ssize_t StlVector<KLIB_CLASS_TEMPLATE_PARAM>::IndexOf(
        ElementType const& value
    ) const noexcept
    {
        auto itr = m_vector.begin();
        auto end = m_vector.end();

        while (itr != end) {
            if (*itr == value) return itr - m_vector.begin();
            ++itr;
        }

        return Containers::ContainerHelper::NotFound();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::IteratorType
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Insert(
        IteratorType position,
        ElementType const& value
    )
    {
        return m_vector.insert(
            position,
            value
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::IteratorType
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Insert(
        IteratorType position,
        ElementType&& value
    )
    {
        return m_vector.insert(
            position,
            ::std::move(value)
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::IteratorType
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Insert(
        ssize_t position,
        ElementType const& value
    )
    {
        return m_vector.insert(
            m_vector.begin() + position,
            value
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::IteratorType
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Insert(
        ssize_t position,
        ElementType&& value
    )
    {
        return m_vector.insert(
            m_vector.begin() + position,
            ::std::move(value)
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr bool
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::IsEmpty() const noexcept
    {
        return m_vector.empty();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr ssize_t
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Length() const noexcept
    {
        return static_cast<ssize_t>(
            m_vector.size()
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    template <class TFunc>
    constexpr ssize_t StlVector<KLIB_CLASS_TEMPLATE_PARAM>::RemoveIf(
        TFunc pred
    )
    {
        return ::std::erase_if(m_vector, pred);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Base&
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Vector() noexcept
    {
        return m_vector;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Base const&
    StlVector<KLIB_CLASS_TEMPLATE_PARAM>::Vector() const noexcept
    {
        return m_vector;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr bool operator==(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept
    {
        return left.Vector() == right.Vector();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr bool operator!=(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept
    {
        return left.Vector() != right.Vector();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr bool operator<(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept
    {
        return left.Vector() < right.Vector();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr bool operator<=(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept
    {
        return left.Vector() <= right.Vector();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr bool operator>(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept
    {
        return left.Vector() > right.Vector();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr bool operator>=(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept
    {
        return left.Vector() >= right.Vector();
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr ::std::strong_ordering operator<=>(
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& left,
        StlVector<KLIB_CLASS_TEMPLATE_PARAM> const& right
    ) noexcept
    {
        return left.Vector() <=> right.Vector();
    }
}

#undef KLIB_CLASS_TEMPLATE_DEF
#undef KLIB_CLASS_TEMPLATE_PARAM

#endif //!KLIB_KONGKONG_STD_STLVECTOR_H