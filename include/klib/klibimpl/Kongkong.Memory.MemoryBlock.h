#ifndef KLIB_KONGKONG_MEMORY_MEMORYBLOCK_H
#define KLIB_KONGKONG_MEMORY_MEMORYBLOCK_H

#include "base.h"
#include "Kongkong.Memory.MemoryResource.h"

namespace klib::Kongkong::Memory
{
    class MemoryBlock final {
        private:

        MemoryResource m_resource;
        ssize_t m_length;

        public:

        MemoryBlock() = default;

        [[nodiscard]]
        constexpr byte& operator[](
            ssize_t index
        ) noexcept;

        [[nodiscard]]
        constexpr byte const& operator[](
            ssize_t index
        ) const noexcept;

        [[nodiscard]]
        constexpr void* Data() noexcept;

        [[nodiscard]]
        constexpr const void* Data() const noexcept;

        [[nodiscard]]
        constexpr ssize_t Length() const noexcept;

        [[nodiscard]]
        constexpr ssize_t RegionSize() const noexcept;

        bool Reserve(
            ssize_t maxLength
        ) noexcept;

        bool ReserveUnsafe(
            ssize_t maxLength
        ) noexcept;

        bool Resize(
            ssize_t length
        ) noexcept;

        bool ResizeUnsafe(
            ssize_t length
        ) noexcept;

        [[nodiscard]]
        constexpr MemoryResource const& Resource() const noexcept;
    };

    [[nodiscard]]
    constexpr bool operator==(
        MemoryBlock const& left,
        MemoryBlock const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        MemoryBlock const& left,
        MemoryBlock const& right
    ) noexcept;
}

namespace klib::Kongkong::Memory
{
    constexpr byte& MemoryBlock::operator[](
        ssize_t index
    ) noexcept
    {
        return static_cast<byte*>(
            Data()
        )[index];
    }

    constexpr byte const& MemoryBlock::operator[](
        ssize_t index
    ) const noexcept
    {
        return static_cast<const byte*>(
            Data()
        )[index];
    }

    constexpr void* MemoryBlock::Data() noexcept
    {
        return m_resource.Data();
    }

    constexpr const void* MemoryBlock::Data() const noexcept
    {
        return m_resource.Data();
    }

    constexpr ssize_t MemoryBlock::Length() const noexcept
    {
        return m_length;
    }

    constexpr ssize_t MemoryBlock::RegionSize() const noexcept
    {
        return static_cast<ssize_t>(
            m_resource.RegionSize()
        );
    }

    inline bool MemoryBlock::Reserve(
        ssize_t maxLength
    ) noexcept
    {
        return m_resource.Reserve(
            static_cast<size_t>(maxLength)
        );
    }

    inline bool MemoryBlock::ReserveUnsafe(
        ssize_t maxLength
    ) noexcept
    {
        return m_resource.ReserveUnsafe(
            static_cast<size_t>(maxLength)
        );
    }

    inline bool MemoryBlock::Resize(
        ssize_t length
    ) noexcept
    {
        if (length < 0) [[unlikely]] return false;
        return ResizeUnsafe(length);
    }

    constexpr MemoryResource const&
    MemoryBlock::Resource() const noexcept
    {
        return m_resource;
    }
}

#endif //!KLIB_KONGKONG_MEMORY_MEMORYBLOCK_H