#ifndef KLIB_MEMORY_GCARRAYHANDLE_H
#define KLIB_MEMORY_GCARRAYHANDLE_H

#include "base.h"
#include "Memory.Primitives.GCHandleBase.h"
#include "Memory.Primitives.GCArrayObject.h"

namespace klib::Memory
{
    template <class T>
    class GCArrayHandle final : public GCHandleBase {
        public:
        
        using ElementType = ::std::remove_cvref_t<T>;

        private:
        ssize_t m_length;
        ElementType* m_p;

        public:

        explicit GCArrayHandle(
            ssize_t length
        );

        [[nodiscard]]
        constexpr ElementType* begin() const noexcept;

        [[nodiscard]]
        constexpr ElementType* end() const noexcept;

        [[nodiscard]]
        constexpr ElementType* Data() const noexcept;

        [[nodiscard]]
        constexpr ssize_t Length() const noexcept;
    };
}

namespace klib::Memory
{
    template <class T>
    constexpr typename GCArrayHandle<T>::ElementType*
    GCArrayHandle<T>::begin() const noexcept
    {
        return m_p;
    }

    template <class T>
    constexpr typename GCArrayHandle<T>::ElementType*
    GCArrayHandle<T>::end() const noexcept
    {
        return m_p + m_length;
    }
    
    template <class T>
    constexpr typename GCArrayHandle<T>::ElementType*
    GCArrayHandle<T>::Data() const noexcept
    {
        return m_p;
    }

    template <class T>
    constexpr ssize_t
    GCArrayHandle<T>::Length() const noexcept
    {
        return m_length;
    }
}

#endif //!KLIB_MEMORY_GCARRAYHANDLE_H
