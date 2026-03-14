#ifndef KLIB_KONGKONG_MEMORY_VIRTUALMEMORYREGION_H
#define KLIB_KONGKONG_MEMORY_VIRTUALMEMORYREGION_H

#include "base.h"
#include "Kongkong.Memory.MemoryResource.h"

namespace klib::Kongkong::Memory
{
    class VirtualMemoryRegion final {
        private:

        MemoryResource m_resource;
        ssize_t m_length;

        /// @brief ここでlength == 0 は考慮しない
        /// @param length 
        /// @return 
        bool do_resizeUnsafe(
            ssize_t length
        ) noexcept;

        public:

        VirtualMemoryRegion() = default;

        [[nodiscard]]
        constexpr byte& operator[](
            ssize_t index
        ) noexcept;

        [[nodiscard]]
        constexpr byte const& operator[](
            ssize_t index
        ) const noexcept;

        bool Clear() noexcept;

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
        VirtualMemoryRegion const& left,
        VirtualMemoryRegion const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        VirtualMemoryRegion const& left,
        VirtualMemoryRegion const& right
    ) noexcept;
}

namespace klib::Kongkong::Memory
{
    constexpr byte& VirtualMemoryRegion::operator[](
        ssize_t index
    ) noexcept
    {
        return static_cast<byte*>(
            Data()
        )[index];
    }

    constexpr byte const& VirtualMemoryRegion::operator[](
        ssize_t index
    ) const noexcept
    {
        return static_cast<const byte*>(
            Data()
        )[index];
    }

    inline bool VirtualMemoryRegion::Clear() noexcept
    {
        if (!m_resource.DecommitAll()) [[unlikely]] return false;

        m_length = 0;

        return true;
    }

    constexpr void* VirtualMemoryRegion::Data() noexcept
    {
        return m_resource.Data();
    }

    constexpr const void* VirtualMemoryRegion::Data() const noexcept
    {
        return m_resource.Data();
    }

    constexpr ssize_t VirtualMemoryRegion::Length() const noexcept
    {
        return m_length;
    }

    constexpr ssize_t VirtualMemoryRegion::RegionSize() const noexcept
    {
        return static_cast<ssize_t>(
            m_resource.RegionSize()
        );
    }

    inline bool VirtualMemoryRegion::Reserve(
        ssize_t maxLength
    ) noexcept
    {
        return m_resource.Reserve(
            static_cast<size_t>(maxLength)
        );
    }

    inline bool VirtualMemoryRegion::ReserveUnsafe(
        ssize_t maxLength
    ) noexcept
    {
        return m_resource.ReserveUnsafe(
            static_cast<size_t>(maxLength)
        );
    }

    inline bool VirtualMemoryRegion::Resize(
        ssize_t length
    ) noexcept
    {
        if (length < 0) [[unlikely]] return false;
        return ResizeUnsafe(length);
    }

    inline bool VirtualMemoryRegion::ResizeUnsafe(
        ssize_t length
    ) noexcept
    {
#if KLIB_HASCPP23
        [[assume(length >= 0)]];
#endif
        if (length == 0) [[unlikely]] return Clear();
        
        if (do_resizeUnsafe(length)) [[likely]] {
            m_length = length;
            return true;
        }

        return false;
    }

    constexpr MemoryResource const&
    VirtualMemoryRegion::Resource() const noexcept
    {
        return m_resource;
    }
}

#endif //!KLIB_KONGKONG_MEMORY_VIRTUALMEMORYREGION_H