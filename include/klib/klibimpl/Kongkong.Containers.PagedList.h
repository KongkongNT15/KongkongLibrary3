#ifndef KLIB_KONGKONG_CONTAINERS_PAGEDLIST_H
#define KLIB_KONGKONG_CONTAINERS_PAGEDLIST_H

#include "base.h"
#include "Kongkong.Containers.Primitives.ArrayBase.h"
#include "Kongkong.Containers.Primitives.PagedListHelper.h"
#include "Kongkong.Memory.VirtualMemoryRegion.h"

namespace klib::Kongkong::Containers
{
    template <class T>
    class PagedList final : public Primitives::ArrayBase<T> {
        public:
        using ElementType = typename Primitives::ArrayBase<T>::ElementType;
        using IteratorType = typename Primitives::ArrayBase<T>::IteratorType;
        using ConstIteratorType = typename Primitives::ArrayBase<T>::ConstIteratorType;
        private:

        static constexpr ssize_t s_elementSize = sizeof(ElementType);
        Memory::VirtualMemoryRegion m_region;

        public:

        PagedList() = default;

        PagedList(
            PagedList const& other
        );

        constexpr PagedList(
            PagedList&& other
        ) noexcept;

        void Append(
            ElementType const& value
        ) requires ::std::is_copy_constructible_v<ElementType>;

        void Append(
            ElementType&& value
        ) requires ::std::is_move_constructible_v<ElementType>;

        [[nodiscard]]
        constexpr ssize_t Capacity() const noexcept;

        constexpr void Clear() noexcept;

        template <class... TArgs>
        void Emplace(
            TArgs&&... args
        );


    };
}

namespace klib::Kongkong::Containers
{
    template <class T>
    void PagedList<T>::Append(
        ElementType const& value
    ) requires ::std::is_copy_constructible_v<ElementType>
    {
        return Emplace(value);
    }

    template <class T>
    void PagedList<T>::Append(
        ElementType&& value
    ) requires ::std::is_move_constructible_v<ElementType>
    {
        return Emplace(::std::move(value));
    }

    template <class T>
    constexpr ssize_t PagedList<T>::Capacity() const noexcept
    {
        return m_region.RegionSize() / s_elementSize;
    }

    template <class T>
    constexpr void PagedList<T>::Clear() noexcept
    {
        for (ElementType& e : *this) {
            e.~ElementType();
        }

        m_region.Clear();
        this->m_length = 0;
    }

    template <class T>
    template <class... TArgs>
    void PagedList<T>::Emplace(
        TArgs&&... args
    )
    {
        ssize_t newLength = this->m_length + 1;

        if (!m_region.ResizeUnsafe(newLength * s_elementSize)) [[unlikely]] {
            Primitives::PagedListHelper::do_throwMemoryCommitError();
        }

        // 末尾に書き込み
        ElementType* e = this->end();

        new(e) ElementType(::std::forward<TArgs>(args)...);

        this->m_length = newLength;
    }

    
}

#endif //!KLIB_KONGKONG_CONTAINERS_PAGEDLIST_H