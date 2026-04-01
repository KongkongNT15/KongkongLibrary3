#ifndef KLIB_KONGKONG_CONTAINERS_BUILTINARRAY_H
#define KLIB_KONGKONG_CONTAINERS_BUILTINARRAY_H

#include "base.h"
#include "Kongkong.Containers.ArrayView.h"
#include "Kongkong.Containers.ContainerHelper.h"
#include "Kongkong.Ranges.IndexFromEnd.h"

#define KLIB_CLASS_TEMPLATE_DEF template <class T, ssize_t N> requires (N >= 1)
#define KLIB_CLASS_TEMPLATE_PARAM T, N

namespace klib::Kongkong::Containers
{
    KLIB_CLASS_TEMPLATE_DEF
    struct BuiltInArray {
        public:

        using ElementType = typename ::std::remove_cvref_t<T>;
        using IteratorType = ElementType*;
        using ConstIteratorType = const ElementType*;

        private:

        public:

        [[nodiscard]]
        consteval bool IsEmpty() noexcept;

        [[nodiscard]]
        consteval ssize_t Length() noexcept;

        ElementType Arr[N];

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
        constexpr ElementType& Back() noexcept;

        [[nodiscard]]
        constexpr ElementType const& Back() const noexcept;

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
        constexpr ElementType& Front() noexcept;

        [[nodiscard]]
        constexpr ElementType const& Front() const noexcept;

        [[nodiscard]]
        ElementType& GetAt(
            ssize_t index
        );

        [[nodiscard]]
        ElementType& GetAt(
            Ranges::IndexFromEnd indexFromEnd
        );

        [[nodiscard]]
        ElementType const& GetAt(
            ssize_t index
        ) const;

        [[nodiscard]]
        ElementType const& GetAt(
            Ranges::IndexFromEnd indexFromEnd
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
        constexpr ElementType& GetAtUnsafe(
            Ranges::IndexFromEnd indexFromEnd
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType const& GetAtUnsafe(
            ssize_t index
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType const& GetAtUnsafe(
            Ranges::IndexFromEnd indexFromEnd
        ) const noexcept;

        [[nodiscard]]
        constexpr ElementType& GetBackUnsafe(
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType const& GetBackUnsafe(
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
        constexpr ArrayView<T> GetViewUnsafe(
            ssize_t offset
        ) const noexcept;

        [[nodiscard]]
        constexpr ArrayView<T> GetViewUnsafe(
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
    KLIB_CLASS_TEMPLATE_DEF
    consteval bool
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::IsEmpty() noexcept
    {
        return false;
    }

    KLIB_CLASS_TEMPLATE_DEF
    consteval ssize_t
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::Length() noexcept
    {
        return N;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::operator[](
        ssize_t index
    ) noexcept
    {
        return Arr[index];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::operator[](
        ssize_t index
    ) const noexcept
    {
        return Arr[index];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::operator[](
        Ranges::IndexFromEnd indexFromEnd
    ) noexcept
    {
        return GetAtFromEndUnsafe(indexFromEnd.Value);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::operator[](
        Ranges::IndexFromEnd indexFromEnd
    ) const noexcept
    {
        return GetAtFromEndUnsafe(indexFromEnd.Value);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::IteratorType
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::begin() noexcept
    {
        return Arr;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ConstIteratorType
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::begin() const noexcept
    {
        return Arr;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::IteratorType
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::end() noexcept
    {
        return Arr + N;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ConstIteratorType
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::end() const noexcept
    {
        return Arr + N;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::Back() noexcept
    {
        return Arr[N - 1];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::Back() const noexcept
    {
        return Arr[N - 1];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr bool BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::Contains(
        ElementType const& value
    ) const noexcept
    {
        return ContainerHelper::ContainsUnsafe(
            N,
            Arr,
            value
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType*
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::Data() noexcept
    {
        return Arr;
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr const typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType*
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::Data() const noexcept
    {
        return Arr;
    }

    KLIB_CLASS_TEMPLATE_DEF
    template <class TPredicate>
    constexpr void BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ForEach(
        TPredicate pred
    )
    {
        auto itr = begin();
        auto e = end();

        while (itr != e) {
            pred(*itr);
            ++itr;
        }
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::Front() noexcept
    {
        return Arr[0];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::Front() const noexcept
    {
        return Arr[0];
    }

    KLIB_CLASS_TEMPLATE_DEF
    typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAt(
        ssize_t index
    )
    {
        ContainerHelper::CheckIndex(
            index,
            N
        );
        return Arr[index];
    }

    KLIB_CLASS_TEMPLATE_DEF
    typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAt(
        Ranges::IndexFromEnd indexFromEnd
    )
    {
        return GetAtFromEnd(indexFromEnd.Value);
    }

    KLIB_CLASS_TEMPLATE_DEF
    typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAt(
        ssize_t index
    ) const
    {
        ContainerHelper::CheckIndex(
            index,
            N
        );
        return Arr[index];
    }

    KLIB_CLASS_TEMPLATE_DEF
    typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAt(
        Ranges::IndexFromEnd indexFromEnd
    ) const
    {
        return GetAtFromEnd(indexFromEnd.Value);
    }

    KLIB_CLASS_TEMPLATE_DEF
    typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAtFromEnd(
        ssize_t indexFromEnd
    )
    {
        ssize_t index = ContainerHelper::CheckIndexFromEnd(
            indexFromEnd,
            N
        );
        return Arr[index];
    }

    KLIB_CLASS_TEMPLATE_DEF
    typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAtFromEnd(
        ssize_t indexFromEnd
    ) const
    {
        ssize_t index = ContainerHelper::CheckIndexFromEnd(
            indexFromEnd,
            N
        );
        return Arr[index];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAtFromEndUnsafe(
        ssize_t indexFromEnd
    ) noexcept
    {
        return Arr[N - indexFromEnd];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAtFromEndUnsafe(
        ssize_t indexFromEnd
    ) const noexcept
    {
        return Arr[N - indexFromEnd];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAtUnsafe(
        Ranges::IndexFromEnd indexFromEnd
    ) noexcept
    {
        return GetAtFromEndUnsafe(indexFromEnd.Value);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAtUnsafe(
        ssize_t index
    ) noexcept
    {
        return Arr[index];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAtUnsafe(
        ssize_t index
    ) const noexcept
    {
        return Arr[index];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetAtUnsafe(
        Ranges::IndexFromEnd indexFromEnd
    ) const noexcept
    {
        return GetAtFromEndUnsafe(indexFromEnd.Value);
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetBackUnsafe(
    ) noexcept
    {
        return Arr[N - 1];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetBackUnsafe(
    ) const noexcept
    {
        return Arr[N - 1];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetFrontUnsafe(
    ) noexcept
    {
        return Arr[0];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr typename BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::ElementType const&
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetFrontUnsafe(
    ) const noexcept
    {
        return Arr[0];
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr ArrayView<T>
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetView() const noexcept
    {
        return ArrayView<T>(
            N,
            Arr
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr ArrayView<T>
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetViewUnsafe(
        ssize_t offset
    ) const noexcept
    {
        return GetViewUnsafe(
            offset,
            N
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr ArrayView<T>
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::GetViewUnsafe(
        ssize_t offset,
        ssize_t end
    ) const noexcept
    {
        return ArrayView<T>(
            end,
            Arr + offset
        );
    }

    KLIB_CLASS_TEMPLATE_DEF
    constexpr ssize_t
    BuiltInArray<KLIB_CLASS_TEMPLATE_PARAM>::IndexOf(
        ElementType const& value
    ) const noexcept
    {
        return ContainerHelper::IndexOfUnsafe(
            N,
            Arr,
            value
        );
    }
}

#undef KLIB_CLASS_TEMPLATE_DEF
#undef KLIB_CLASS_TEMPLATE_PARAM

#endif //!KLIB_KONGKONG_CONTAINERS_BUILTINARRAY_H