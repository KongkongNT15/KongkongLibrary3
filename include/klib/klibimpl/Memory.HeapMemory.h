#ifndef KLIB_MEMORY_HEAPMEMORY_H
#define KLIB_MEMORY_HEAPMEMORY_H

#include "base.h"

#include <stdlib.h>

namespace klib::Memory
{
    template <class T>
    class HeapMemory final {
        public:

        using ElementType = ::std::remove_cvref_t<T>;

        private:
        ElementType* m_p;
        ssize_t m_length;

        public:

        HeapMemory(
            ssize_t length
        ) noexcept;

        constexpr HeapMemory(
            HeapMemory&& other
        ) noexcept;

        ~HeapMemory();

        [[nodiscard]]
        constexpr operator bool() const noexcept;

        [[nodiscard]]
        constexpr bool operator!() const noexcept;

        HeapMemory& operator=(
            HeapMemory&& other
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType* Data() const noexcept;

        bool Dispose() noexcept;

        void DisposeUnsafe() noexcept;

        [[nodiscard]]
        constexpr bool IsEmpty() const noexcept;

        [[nodiscard]]
        constexpr bool IsNull() const noexcept;

        [[nodiscard]]
        constexpr ssize_t Length() const noexcept;

        bool Resize(
            ssize_t newLength
        ) noexcept;

        void ResizeUnsafe(
            ssize_t newLength
        ) noexcept;
    };

    template <class T>
    [[nodiscard]]
    constexpr bool operator==(
        HeapMemory<T> const& left,
        HeapMemory<T> const& right
    ) noexcept;

    template <class T>
    [[nodiscard]]
    constexpr bool operator==(
        HeapMemory<T> const& left,
        ::std::nullptr_t
    ) noexcept;

    template <class T>
    [[nodiscard]]
    constexpr bool operator==(
        ::std::nullptr_t,
        HeapMemory<T> const& right
    ) noexcept;

    template <class T>
    [[nodiscard]]
    constexpr bool operator!=(
        HeapMemory<T> const& left,
        HeapMemory<T> const& right
    ) noexcept;

    template <class T>
    [[nodiscard]]
    constexpr bool operator!=(
        HeapMemory<T> const& left,
        ::std::nullptr_t
    ) noexcept;

    template <class T>
    [[nodiscard]]
    constexpr bool operator!=(
        ::std::nullptr_t,
        HeapMemory<T> const& right
    ) noexcept;

}

namespace klib::Memory
{
    template <class T>
    HeapMemory<T>::HeapMemory(
        ssize_t length
    ) noexcept
        : m_p(
            ::malloc(
                sizeof(ElementType) * length
            )
        )
        , m_length(length)
    {
        if (m_p == nullptr) [[unlikely]] {
            m_length = 0;
        }
    }

    template <class T>
    constexpr HeapMemory<T>::HeapMemory(
        HeapMemory<T>&& other
    ) noexcept
        : m_p(other.m_p)
        , m_length(other.m_length)
    {
        other.m_p = nullptr;
    }

    template <class T>
    HeapMemory<T>::~HeapMemory()
    {
        if (m_p == nullptr) return;

        ::free(m_p);
    }

    template <class T>
    constexpr HeapMemory<T>::operator
    bool() const noexcept
    {
        return m_p != nullptr;
    }

    template <class T>
    constexpr bool
    HeapMemory<T>::operator!() const noexcept
    {
        return m_p == nullptr;
    }
    
    template <class T>
    HeapMemory<T>&
    HeapMemory<T>::operator=(
        HeapMemory<T>&& other
    ) noexcept
    {
        if (&other != this) [[likely]] {
            if (m_p != nullptr) ::free(m_p);

            m_p = other.m_p;
            m_length = other.m_length;

            other.m_p = nullptr;
        }

        return *this;
    }

    template <class T>
    constexpr typename HeapMemory<T>::ElementType*
    HeapMemory<T>::Data() const noexcept
    {
        return m_p;
    }

    template <class T>
    bool HeapMemory<T>::Dispose() noexcept
    {
        if (m_p == nullptr) [[unlikely]] return false;

        if (!free(m_p)) [[unlikely]] return false;

        m_p = nullptr;
        m_lenght = 0;

        return true;
    }

    template <class T>
    void HeapMemory<T>::DisposeUnsafe() noexcept
    {
        ::free(m_p);

        m_p = nullptr;
        m_lenght = 0;
    }

    template <class T>
    constexpr bool
    HeapMemory<T>::IsEmpty() const noexcept
    {
        return m_length == 0;
    }

    template <class T>
    constexpr bool
    HeapMemory<T>::IsNull() const noexcept
    {
        return m_p == nullptr;
    }

    template <class T>
    constexpr ssize_t
    HeapMemory<T>::Length() const noexcept
    {
        return m_length;
    }

    template <class T>
    bool HeapMemory<T>::Resize(
        ssize_t newLength
    ) noexcept
    {
        ElementType* p = static_cast<ElementType*>(
            ::realloc(m_p, newLength * sizeof(ElementType))
        );

        if (p == nullptr) [[unlikely]] return false;

        m_p = p;
        m_length = newLength;
    }

    template <class T>
    void HeapMemory<T>::ResizeUnsafe(
        ssize_t newLength
    ) noexcept
    {
        m_p = static_cast<ElementType*>(
            ::realloc(m_p, newLength * sizeof(ElementType))
        );

        m_length = newLength;
    }

    template <class T>
    constexpr bool operator==(
        HeapMemory<T> const& left,
        HeapMemory<T> const& right
    ) noexcept
    {
        return left.IsEmpty() && right.IsEmpty();
    }

    template <class T>
    constexpr bool operator==(
        HeapMemory<T> const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return left.IsNull();
    }

    template <class T>
    constexpr bool operator==(
        ::std::nullptr_t,
        HeapMemory<T> const& right
    ) noexcept
    {
        return right.IsNull();
    }

    template <class T>
    constexpr bool operator!=(
        HeapMemory<T> const& left,
        HeapMemory<T> const& right
    ) noexcept
    {
        return !(left == right);
    }

    template <class T>
    constexpr bool operator!=(
        HeapMemory<T> const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return !(left == nullptr);
    }

    template <class T>
    constexpr bool operator!=(
        ::std::nullptr_t,
        HeapMemory<T> const& right
    ) noexcept
    {
        return !(nullptr == right);
    }
}

#endif //!KLIB_MEMORY_HEAPMEMORY_H