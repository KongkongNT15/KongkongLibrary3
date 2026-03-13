#ifndef KLIB_KONGKONG_CONTAINERS_PRIMITIVES_CONTAINERBASE_H
#define KLIB_KONGKONG_CONTAINERS_PRIMITIVES_CONTAINERBASE_H

#include "base.h"

namespace klib::Kongkong::Containers::Primitives
{
    struct ContainerBase {
        protected:
        ssize_t m_length;

        constexpr ContainerBase() noexcept;
        
        constexpr ContainerBase(
            ssize_t length
        ) noexcept;

        public:

        [[nodiscard]]
        constexpr operator bool() const noexcept;

        [[nodiscard]]
        constexpr bool operator!() const noexcept;

        [[nodiscard]]
        constexpr bool IsEmpty() const noexcept;

        [[nodiscard]]
        constexpr ssize_t Length() const noexcept;
    };
}

namespace klib::Kongkong::Containers::Primitives
{
    constexpr ContainerBase::ContainerBase() noexcept
        : ContainerBase(0)
    {
    }

    constexpr ContainerBase::ContainerBase(
        ssize_t length
    ) noexcept
        : m_length(0)
    {
    }

    constexpr ContainerBase::operator bool() const noexcept
    {
        return m_length != 0;
    }

    constexpr bool ContainerBase::operator!() const noexcept
    {
        return m_length == 0;
    }

    constexpr bool ContainerBase::IsEmpty() const noexcept
    {
        return m_length == 0;
    }

    constexpr ssize_t ContainerBase::Length() const noexcept
    {
        return m_length;
    }
}

#endif //!KLIB_KONGKONG_CONTAINERS_PRIMITIVES_CONTAINERBASE_H