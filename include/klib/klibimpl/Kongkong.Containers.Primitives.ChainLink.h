#ifndef KLIB_KONGKONG_CONTAINERS_PRIMITIVES_CHAINLINK_H
#define KLIB_KONGKONG_CONTAINERS_PRIMITIVES_CHAINLINK_H

#include "base.h"
#include "Kongkong.ValueType.h"
#include "Kongkong.Memory.MemoryPage.h"

namespace klib::Kongkong::Containers::Primitives
{
    template <class T>
    struct ChainLink : public ValueType {
        private:
        Memory::MemoryPage m_page;
        public:

        ChainLink();

        ~ChainLink();

        [[nodiscard]]
        constexpr T* End() const noexcept;

        [[nodiscard]]
        constexpr T* Front() const noexcept;

        [[nodiscard]]
        constexpr T* Last() const noexcept;

        [[nodiscard]]
        ChainLink<T>* Next() const noexcept;

        void Next(
            ChainLink<T>* next
        ) noexcept;
    };
}

namespace klib::Kongkong::Containers::Primitives
{
    template <class T>
    ChainLink<T>::ChainLink()
        : m_page()
    {
        m_page.AllocUnsafe();
    }

    template <class T>
    ChainLink<T>::~ChainLink()
    {
        m_page.Dispose();
    }

    template <class T>
    constexpr T* ChainLink<T>::End() const noexcept
    {
        ssize_t maxCount = (m_page.PageSize() - sizeof(T*)) / sizeof(T);
        byte* p = static_cast<byte*>(m_page.Data());
        return reinterpret_cast<T*>(p + maxCount);
    }

    template <class T>
    constexpr T* ChainLink<T>::Front() const noexcept
    {
        return static_cast<T*>(m_page.Data());
    }

    template <class T>
    constexpr T* ChainLink<T>::Last() const noexcept
    {
        return End() - 1;
    }

    template <class T>
    ChainLink<T>* ChainLink<T>::Next() const noexcept
    {
        void* data = m_page.Data();

        return static_cast<ChainLink<T>*>(data);
    }

    template <class T>
    void ChainLink<T>::Next(
        ChainLink<T>* next
    ) noexcept
    {
        void* data = m_page.Data();

        *static_cast<ChainLink<T>*>(data) = next;
    }
}

#endif //!KLIB_KONGKONG_CONTAINERS_PRIMITIVES_CHAINLINK_H