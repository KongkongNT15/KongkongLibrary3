#ifndef KLIB_KONGKONG_MEMORY_MEMORYPAGE_H
#define KLIB_KONGKONG_MEMORY_MEMORYPAGE_H

#include "base.h"
#include "Kongkong.Memory.MemoryPageHelper.h"

namespace klib::Kongkong::Memory
{
    class MemoryPage final {
        private:
        void* m_data;

        public:

        [[nodiscard]]
        static size_t PageSize() noexcept;

        constexpr MemoryPage() noexcept;

        bool AllocUnsafe() noexcept;

        [[nodiscard]]
        constexpr void* Data() const noexcept;

        bool Dispose() noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode(
        ) const noexcept;
    };
}

namespace klib::Kongkong::Memory
{
    inline size_t MemoryPage::PageSize() noexcept
    {
        return MemoryPageHelper::PageSize();
    }

    constexpr MemoryPage::MemoryPage() noexcept
        : m_data(nullptr)
    {
    }

    inline bool MemoryPage::AllocUnsafe() noexcept
    {
        void* p = MemoryPageHelper::Reserve(PageSize());

        if (!p) [[unlikely]] return false;

        MemoryPageHelper::Commit(
            p,
            PageSize()
        );

        m_data = p;

        return true;
    }

    constexpr void* MemoryPage::Data() const noexcept
    {
        return m_data;
    }

    inline bool MemoryPage::Dispose() noexcept
    {
        return MemoryPageHelper::Free(m_data, PageSize());
    }

    constexpr Hash::ResultType MemoryPage::GetHashCode(
    ) const noexcept
    {
        return ::std::hash<void*>().operator()(m_data);
    }
}

#endif //!KLIB_KONGKONG_MEMORY_MEMORYPAGE_H