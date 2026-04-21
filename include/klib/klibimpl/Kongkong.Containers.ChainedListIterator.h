#ifndef KLIB_KONGKONG_CONTAINERS_CHAINEDLISTITERATOR_H
#define KLIB_KONGKONG_CONTAINERS_CHAINEDLISTITERATOR_H

#include "base.h"
#include "Kongkong.ValueType.h"
#include "Kongkong.Containers.Primitives.ChainLink.h"

namespace klib::Kongkong::Containers
{
    template <class T>
    class ChainedListIterator : public ValueType {
        private:
        using s_elementType = typename ::std::remove_cvref_t<T>;
        using ElementType = typename ::std::remove_volatile_t<typename ::std::remove_reference_t<T>>;
        Primitives::ChainLink<s_elementType>* m_pLink;
        s_elementType* m_p;
        s_elementType* m_end;
        ssize_t m_nokori;
        ssize_t m_maxChainElementCount;

        void do_add() noexcept;
        void do_moveLinkUnsafe(
            ssize_t count
        ) noexcept;

        public:

        constexpr ChainedListIterator(
            ssize_t length,
            Primitives::ChainLink<s_elementType>* pLink,
            ssize_t maxChainElementCount
        ) noexcept;

        ChainedListIterator& operator++() noexcept;
        ChainedListIterator operator++(int) noexcept;

        ChainedListIterator& operator+=(
            ssize_t length
        ) noexcept;

        ChainedListIterator& operator-=(
            ssize_t length
        ) noexcept;

        void MoveBackward(
            size_t length
        ) noexcept;

        void MoveForward(
            size_t length
        ) noexcept;

        [[nodiscard]]
        constexpr bool Equals(
            ChainedListIterator other
        ) const noexcept;
    };

    template <class T>
    [[nodiscard]]
    constexpr bool operator==(
        ChainedListIterator<T> left,
        ChainedListIterator<T> right
    ) noexcept;

    template <class T>
    [[nodiscard]]
    constexpr bool operator!=(
        ChainedListIterator<T> left,
        ChainedListIterator<T> right
    ) noexcept;

    template <class T>
    [[nodiscard]]
    ChainedListIterator<T> operator+(
        ChainedListIterator<T> left,
        ssize_t right
    ) noexcept;

    template <class T>
    [[nodiscard]]
    constexpr bool operator+(
        ssize_t left,
        ChainedListIterator<T> right
    ) noexcept;

    template <class T>
    [[nodiscard]]
    ChainedListIterator<T> operator-(
        ChainedListIterator<T> left,
        ssize_t right
    ) noexcept;

    template <class T>
    [[nodiscard]]
    constexpr bool operator-(
        ssize_t left,
        ChainedListIterator<T> right
    ) noexcept;
}

namespace klib::Kongkong::Containers
{
    template <class T>
    void ChainedListIterator<T>::do_add() noexcept
    {
        if (++m_p == m_end) {
            m_pLink = m_pLink->Next();
            m_p = m_pLink->Front();
            m_end = m_pLink->End();
        }
    }

    template <class T>
    void ChainedListIterator<T>::do_moveLinkUnsafe(
        ssize_t count
    ) noexcept
    {
        auto link = m_pLink;

        for (ssize_t i = 0; i < count; i++) {
            link = link->Next();
        }

        m_pLink = link;
    }
    
    template <class T>
    constexpr ChainedListIterator<T>::ChainedListIterator(
        ssize_t length,
        Primitives::ChainLink<s_elementType>* pLink,
        ssize_t maxChainElementCount
    ) noexcept
        : m_nokori(length)
        , m_pLink(pLink)
        , m_maxChainElementCount(maxChainElementCount)
    {
        if (pLink != nullptr) {
            m_p = pLink->Front();
            m_end = pLink->End();
        }
    }

    template <class T>
    ChainedListIterator<T>&
    ChainedListIterator<T>::operator++() noexcept
    {
        do_add();

        return *this;
    }

    template <class T>
    ChainedListIterator<T>
    ChainedListIterator<T>::operator++(int) noexcept
    {
        auto result = *this;

        do_add();

        return result;
    }

    template <class T>
    ChainedListIterator<T>&
    ChainedListIterator<T>::operator+=(
        ssize_t length
    ) noexcept
    {
        if (length > 0) MoveForward(length);
        else if (length < 0) MoveBackward(-length);
        
        return *this;
    }

    template <class T>
    ChainedListIterator<T>&
    ChainedListIterator<T>::operator-=(
        ssize_t length
    ) noexcept
    {
        return operator+=(-length);
    }

    template <class T>
    constexpr bool ChainedListIterator<T>::Equals(
        ChainedListIterator<T> other
    ) const noexcept
    {
        return m_nokori == other.m_nokori && m_pLink == other.m_pLink;
    }

    template <class T>
    void ChainedListIterator<T>::MoveBackward(
        size_t length
    ) noexcept
    {

    }

    template <class T>
    void ChainedListIterator<T>::MoveForward(
        size_t length
    ) noexcept
    {
        auto moveChainCount = length / m_maxChainElementCount;
        
        auto p = m_p + length;

        if (p < m_end) {
            m_p = p;
            m_nokori -= length;

            return;
        }

        
    }

    template <class T>
    constexpr bool operator==(
        ChainedListIterator<T> left,
        ChainedListIterator<T> right
    ) noexcept
    {
        return left.Equals(right);
    }

    template <class T>
    constexpr bool operator!=(
        ChainedListIterator<T> left,
        ChainedListIterator<T> right
    ) noexcept
    {
        return !left.Equals(right);
    }

    template <class T>
    ChainedListIterator<T> operator+(
        ChainedListIterator<T> left,
        ssize_t right
    ) noexcept
    {
        return left += right;
    }

    template <class T>
    constexpr bool operator+(
        ssize_t left,
        ChainedListIterator<T> right
    ) noexcept
    {
        return right += left;
    }

    template <class T>
    ChainedListIterator<T> operator-(
        ChainedListIterator<T> left,
        ssize_t right
    ) noexcept
    {
        return left -= right;
    }

    template <class T>
    constexpr bool operator-(
        ssize_t left,
        ChainedListIterator<T> right
    ) noexcept
    {
        return right -= left;
    }
}

#endif //!KLIB_KONGKONG_CONTAINERS_CHAINEDLISTITERATOR_H