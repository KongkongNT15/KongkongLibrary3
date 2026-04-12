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