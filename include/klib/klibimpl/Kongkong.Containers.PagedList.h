#ifndef KLIB_KONGKONG_CONTAINERS_PAGEDLIST_H
#define KLIB_KONGKONG_CONTAINERS_PAGEDLIST_H

#include "base.h"
#include "Kongkong.Containers.Primitives.ArrayBase.h"
#include "Kongkong.Containers.Primitives.PagedListHelper.h"
#include "Kongkong.Memory.VirtualMemoryRegion.h"
#include "Kongkong.Ranges.IteratorHelper.h"

#include <ranges>

namespace klib::Kongkong::Containers
{
    template <class T>
    class PagedList final : public Primitives::ArrayBase<T> {
        public:
        using ElementType = typename Primitives::ArrayBase<T>::ElementType;
        using IteratorType = typename Primitives::ArrayBase<T>::IteratorType;
        using ConstIteratorType = typename Primitives::ArrayBase<T>::ConstIteratorType;
        
        static constexpr bool IsCopyConstructible = ::std::is_copy_constructible_v<ElementType>;
        static constexpr bool IsMoveConstructible = ::std::is_move_constructible_v<ElementType>;
        static constexpr bool IsNothrowCopyConstructible = ::std::is_nothrow_copy_constructible_v<ElementType>;
        static constexpr bool IsNothrowMoveConstructible = ::std::is_nothrow_move_constructible_v<ElementType>;

        private:

        static constexpr ssize_t s_elementSize = sizeof(ElementType);
        Memory::VirtualMemoryRegion m_region;

        template <class TIterator, bool IsMove>
        void do_appendRange(
            TIterator begin,
            TIterator end
        );

        public:

        PagedList& operator=(
            PagedList&& other
        ) noexcept;

        PagedList& operator+=(
            ElementType const& value
        ) requires IsCopyConstructible;

        PagedList& operator+=(
            ElementType&& value
        ) requires IsMoveConstructible;

        void Append(
            ElementType const& value
        ) requires IsCopyConstructible;

        void Append(
            ElementType&& value
        ) requires IsMoveConstructible;

        template <class TIterable>
        void AppendRange(
            TIterable&& range
        );

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
    template <class TIterator, bool IsMove>
    void PagedList<T>::do_appendRange(
        TIterator begin,
        TIterator end
    )
    {
        ssize_t appendLength = Ranges::IteratorHelper::GetLengthUnsafe(
            begin,
            end
        );

        ssize_t newLength = this->m_length + appendLength;

        if (!m_region.ResizeUnsafe(newLength * s_elementSize)) [[unlikely]] {
            Primitives::PagedListHelper::do_throwMemoryCommitError();
        }

        constexpr bool isNothrowCopyConstructible = noexcept(ElementType(*begin));
        constexpr bool isNothrowMoveConstructible = noexcept(ElementType(::std::move(*begin)));

        // コンストラクタで例外を投げない
        if constexpr (
            (!IsMove && isNothrowCopyConstructible)
            || (IsMove && isNothrowMoveConstructible)
        ) {
            auto itr = this->end();

            while (begin != end) {

                if constexpr (IsMove) {
                    new(itr) ElementType(*begin);
                }
                else {
                    new(itr) ElementType(::std::move(*begin));
                }

                ++itr;
                ++begin;
            }
        }
        else {
            ssize_t appendedLength = 0;
            try {
                
                auto itr = this->end();

                while (begin != end) {

                    if constexpr (IsMove) {
                        new(itr) ElementType(*begin);
                    }
                    else {
                        new(itr) ElementType(::std::move(*begin));
                    }
                    ++appendedLength;
                    ++itr;
                    ++begin;
                }
            }
            catch (...) {
                ContainerHelper::DestructUnsafe(
                    this->end(),
                    this->end() + appendedLength
                );

                ::std::rethrow_exception(
                    ::std::current_exception()
                );
            }
        }

        this->m_length = newLength;
    }

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
    PagedList<T>& PagedList<T>::operator+=(
        ElementType const& value
    ) requires IsCopyConstructible
    {
        return Emplace(value);
    }

    template <class T>
    PagedList<T>& PagedList<T>::operator+=(
        ElementType&& value
    ) requires IsMoveConstructible
    {
        return Emplace(::std::move(value));
    }

    template <class T>
    void PagedList<T>::Append(
        ElementType const& value
    ) requires IsCopyConstructible
    {
        return Emplace(value);
    }

    template <class T>
    void PagedList<T>::Append(
        ElementType&& value
    ) requires IsMoveConstructible
    {
        return Emplace(::std::move(value));
    }

    template <class T>
    template <class TIterable>
    void PagedList<T>::AppendRange(
        TIterable&& range
    )
    {
        auto begin = ::std::ranges::begin(range);
        auto end = ::std::ranges::end(range);
        do_appendRange<
            decltype(begin),
            ::std::is_rvalue_reference_v<decltype(range)>
        >(
            begin,
            end
        );
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