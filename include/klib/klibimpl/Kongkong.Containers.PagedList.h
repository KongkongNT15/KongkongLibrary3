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

        public:

        ~PagedList();

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

        void Append(
            ssize_t count,
            ElementType const& v
        ) requires IsCopyConstructible;

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

        void ReserveUnsafe(
            ssize_t minCount
        );
    };
}

namespace klib::Kongkong::Containers
{

    template <class T>
    PagedList<T>::~PagedList()
    {
        if (m_region.Data() == nullptr) return;

        ContainerHelper::DestructUnsafe(
            this->begin(),
            this->end()
        );
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
    void PagedList<T>::Append(
        ssize_t count,
        ElementType const& value
    ) requires IsCopyConstructible
    {
        if (count <= 0) [[unlikely]] return;

        ssize_t newLength = this->m_length + count;

        if (!m_region.ResizeUnsafe(newLength * s_elementSize)) [[unlikely]] {
            Primitives::PagedListHelper::do_throwMemoryCommitError();
        }

        // 末尾に書き込み
        ElementType* itr = this->end();
        ElementType* end = itr + count;

        try {
            while (itr != end) {
                new(itr) ElementType(value);
                ++itr;
            }
        }
        catch (...) {
            ContainerHelper::DestructUnsafe(
                this->end(),
                itr
            );

            ::std::rethrow_exception(
                ::std::current_exception()
            );
        }
        
        this->m_length = newLength;
    }

    template <class T>
    template <class TIterable>
    void PagedList<T>::AppendRange(
        TIterable&& range
    )
    {
        constexpr bool isMove = ::std::is_rvalue_reference_v<TIterable&&>;

        auto begin = ::std::ranges::begin(range);
        auto end = ::std::ranges::end(range);
        
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
            (!isMove && isNothrowCopyConstructible)
            || (isMove && isNothrowMoveConstructible)
        ) {
            auto itr = this->end();

            while (begin != end) {

                if constexpr (isMove) {
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

                    if constexpr (isMove) {
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

    template <class T>
    void PagedList<T>::ReserveUnsafe(
        ssize_t minCount
    )
    {
        if (!m_region.ReserveUnsafe(
            minCount * s_elementSize
        )) [[unlikely]] {
            Primitives::PagedListHelper::do_throwReserveError();
        }

        this->m_p = static_cast<ElementType*>(m_region.Data());
        this->m_length = 0;
    }
}

#endif //!KLIB_KONGKONG_CONTAINERS_PAGEDLIST_H