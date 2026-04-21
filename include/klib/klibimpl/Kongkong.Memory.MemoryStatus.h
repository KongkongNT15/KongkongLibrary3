#ifndef KLIB_KONGKONG_MEMORY_MEMORYSTATUS_H
#define KLIB_KONGKONG_MEMORY_MEMORYSTATUS_H

#include "base.h"
#include "Kongkong.ValueType.h"

namespace klib::Kongkong::Memory
{
    class MemoryStatus final : public ValueType {
        private:
        struct s_statusType {
            size_t TotalMemory;
            size_t TotalVirtualMemory;
            s_statusType() noexcept;
        };

        static s_statusType s_status;

        size_t m_avaiable;
        size_t m_virtualAvaiable;

        public:
        
        [[nodiscard]]
        MemoryStatus Current() noexcept;

        [[nodiscard]]
        static size_t TotalMemory() noexcept;

        [[nodiscard]]
        static size_t TotalVirtualMemory() noexcept;


    };
}

namespace klib::Kongkong::Memory
{
    inline MemoryStatus::s_statusType::s_statusType() noexcept
    {
#if KLIB_ENV_WINDOWS
        ::MEMORYSTATUSEX status;
        status.dwLength = sizeof(status);

        ::GlobalMemoryStatusEx(&status);

        TotalMemory = status.ullTotalPhys;
        TotalVirtualMemory = status.ullTotalVirtual;
#else
        static_assert(false, "ふぁ！？っく");
#endif
    }

    inline size_t MemoryStatus::TotalMemory() noexcept
    {
        return s_status.TotalMemory;
    }

    inline size_t MemoryStatus::TotalVirtualMemory() noexcept
    {
        return s_status.TotalVirtualMemory;
    }
}

#endif //!KLIB_KONGKONG_MEMORY_MEMORYSTATUS_H