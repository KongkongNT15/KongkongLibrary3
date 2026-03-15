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

        PagedList& operator=(
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
    PagedList<T>& PagedList<T>::operator=(
        PagedList<T>&& other
    ) noexcept
    {
        if (&other != this) [[likely]] {
            ContainerHelper::DestructUnsafe(
                this->begin(),
                this->end()
            );

            this->m_p = other.m_region.Data();
            this->m_length = other.m_length;
            m_region = ::std::move(other.m_region);

        }

        return *this;
    }

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
        ContainerHelper::DestructUnsafe(
            this->begin(),
            this->end()
        );

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