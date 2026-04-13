#ifndef KLIB_KONGKONG_MEMORY_MEMORYRESOURCE_H
#define KLIB_KONGKONG_MEMORY_MEMORYRESOURCE_H

#include "base.h"
#include "Kongkong.PointerType.h"
#include "Kongkong.Memory.MemoryPageHelper.h"

namespace klib::Kongkong::Memory
{
    class MemoryResource final : public PointerType {

        private:

        void* m_p;
        size_t m_regionSize;

        bool do_free() noexcept;

        static void* do_reserve(
            size_t minBytes
        ) noexcept;
        public:

        [[nodiscard]]
        static size_t GetPageLength(
            size_t bytes
        ) noexcept;

        [[nodiscard]]
        static size_t PageSize() noexcept;
        
        constexpr MemoryResource(
        ) noexcept;

        MemoryResource(
            MemoryResource const&
        ) = delete;

        constexpr MemoryResource(
            MemoryResource&& other
        ) noexcept;

        ~MemoryResource();

        MemoryResource& operator=(
            MemoryResource const&
        ) = delete;

        MemoryResource& operator=(
            MemoryResource&& other
        ) noexcept;
        
        bool Commit(
            void* targetAddress,
            size_t bytes
        ) noexcept;

        [[nodiscard]]
        constexpr void* Data() const noexcept;

        bool Decommit(
            void* targetAddress,
            size_t bytes
        ) noexcept;

        bool DecommitAll() noexcept;

        bool Free() noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;

        [[nodiscard]]
        constexpr bool IsReserved() const noexcept;

        [[nodiscard]]
        constexpr size_t RegionSize() const noexcept;

        bool Reserve(
            size_t minBytes
        ) noexcept;

        bool ReserveUnsafe(
            size_t minBytes
        ) noexcept;
    };

    [[nodiscard]]
    constexpr bool operator==(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept;
}

namespace klib::Kongkong::Memory
{
    inline bool MemoryResource::do_free() noexcept
    {
        return MemoryPageHelper::Free(
            m_p,
            m_regionSize
        );
    }

    inline void* MemoryResource::do_reserve(
        size_t minBytes
    ) noexcept
    {
        return MemoryPageHelper::Reserve(
            minBytes
        );
    }

    inline size_t MemoryResource::GetPageLength(
        size_t bytes
    ) noexcept
    {
        if (bytes == 0) return 0;

        return (bytes - 1) / PageSize() + 1;
    }

    inline size_t MemoryResource::PageSize() noexcept
    {
        return MemoryPageHelper::PageSize();
    }

    constexpr MemoryResource::MemoryResource(
    ) noexcept
        : m_p(nullptr)
        , m_regionSize(0)
    {
    }

    constexpr MemoryResource::MemoryResource(
        MemoryResource&& other
    ) noexcept
        : m_p(other.m_p)
        , m_regionSize(other.m_regionSize)
    {
        other.m_p = nullptr;
    }

    inline MemoryResource::~MemoryResource()
    {
        if (m_p == nullptr) return;
        do_free();
    }

    inline MemoryResource& MemoryResource::operator=(
        MemoryResource&& other
    ) noexcept
    {
        if (&other != this) [[likely]] {
            if (IsReserved()) do_free();

            m_p = other.m_p;
            m_regionSize = other.m_regionSize;

            other.m_p = nullptr;
        }

        return *this;
    }

    inline bool MemoryResource::Commit(
        void* targetAddress,
        size_t bytes
    ) noexcept
    {
        return MemoryPageHelper::Commit(
            targetAddress,
            bytes
        );
    }

    constexpr void* MemoryResource::Data() const noexcept
    {
        return m_p;
    }

    bool MemoryResource::Decommit(
        void* targetAddress,
        size_t bytes
    ) noexcept
    {
        return MemoryPageHelper::Decommit(
            targetAddress,
            bytes
        );
    }

    bool MemoryResource::DecommitAll(
    ) noexcept
    {
        return MemoryPageHelper::Decommit(
            m_p,
            m_regionSize
        );
    }

    inline bool MemoryResource::Free() noexcept
    {
        if (!do_free()) return false;

        m_p = nullptr;
        m_regionSize = 0;

        return true;
    }

    constexpr Hash::ResultType
    MemoryResource::GetHashCode() const noexcept
    {
        auto v = ::std::hash<void*>().operator()(m_p);

        return v + m_regionSize;
    }

    constexpr bool MemoryResource::IsReserved() const noexcept
    {
        return m_p != nullptr;
    }

    constexpr size_t MemoryResource::RegionSize() const noexcept
    {
        return m_regionSize;
    }

    inline bool MemoryResource::Reserve(
        size_t minBytes
    ) noexcept
    {
        if (IsReserved()) {
            bool result = do_free();

            if (!result) [[unlikely]] return false;
        }

        return ReserveUnsafe(minBytes);
    }

    inline bool MemoryResource::ReserveUnsafe(
        size_t minBytes
    ) noexcept
    {
        void* p = do_reserve(minBytes);

        if (!p) return false;

        m_p = p;

        if (minBytes % PageSize() == 0) {
            m_regionSize = minBytes;
        }
        else {
            m_regionSize = (minBytes / PageSize() + 1) * PageSize();
        }
    }

    constexpr bool operator==(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept
    {
        return !left.IsReserved() && right.IsReserved();
    }

    constexpr bool operator!=(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept
    {
        return left.IsReserved() || right.IsReserved();
    }

    constexpr bool operator<(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept
    {
        return left.Data() < right.Data();
    }

    constexpr bool operator<=(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept
    {
        if (left == right) return true;
        return left < right;
    }

    constexpr bool operator>(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>=(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept
    {
        if (left == right) return true;
        return right < left;
    }

    constexpr ::std::strong_ordering operator<=>(
        MemoryResource const& left,
        MemoryResource const& right
    ) noexcept
    {
        if (left == right) return ::std::strong_ordering::equal;

        return left < right ? ::std::strong_ordering::less : ::std::strong_ordering::greater;
    }
}

#endif //!KLIB_KONGKONG_MEMORY_MEMORYRESOURCE_H