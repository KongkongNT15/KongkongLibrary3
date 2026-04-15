#ifndef KLIB_KONGKONG_CONTAINERS_PAGECACHE_H
#define KLIB_KONGKONG_CONTAINERS_PAGECACHE_H

#include "base.h"
#include "Kongkong.ValueType.h"
#include "Kongkong.Containers.PageCacheAppendFailureArgs.h"
#include "Kongkong.Containers.Primitives.ArrayBase.h"
#include "Kongkong.Memory.MemoryPage.h"

namespace klib::Kongkong::Containers
{
    class PageChache : public Primitives::ArrayBase<byte>, ValueType {
        private:

        Memory::MemoryPage m_page;

        public:

        [[nodiscard]]
        static ssize_t PageSize() noexcept;

        PageChache();

        bool Append(
            byte value
        ) noexcept;

        ssize_t AppendUnsafe(
            ssize_t,
            ::nullptr_t
        ) = delete;

        ssize_t AppendUnsafe(
            ssize_t length,
            const void* data
        ) noexcept;

        template <class TPredicate>
        void AppendWithFallBack(
            byte value,
            TPredicate&& fallBack
        );

        template <class TPredicate>
        void AppendWithFallBackUnsafe(
            ssize_t length,
            const void* data,
            TPredicate&& fallBack
        );

        [[nodiscard]]
        ssize_t Capacity() const noexcept;

        constexpr void Clear() noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;

        
    };
}

namespace klib::Kongkong::Containers
{
    inline ssize_t PageChache::PageSize() noexcept
    {
        return static_cast<ssize_t>(
            Memory::MemoryPageHelper::PageSize()
        );
    }

    inline PageChache::PageChache()
        : Primitives::ArrayBase<byte>()
        , m_page()
    {
        m_p = static_cast<byte*>(m_page.Data());
    }

    inline bool PageChache::Append(
        byte value
    ) noexcept
    {
        if (m_length == PageSize()) [[unlikely]] return false;

        m_p[m_length] = value;
        ++m_length;

        return true;
    }

    template <class TPredicate>
    void PageChache::AppendWithFallBack(
        byte value,
        TPredicate&& fallBack
    )
    {
        if (!Append(value)) [[unlikely]] {
            fallBack(
                *this,
                PageChacheAppendFailureArgs{
                    &value,
                    1
                }
            );
        }
    }

    template <class TPredicate>
    void PageChache::AppendWithFallBackUnsafe(
        ssize_t length,
        const void* data,
        TPredicate&& fallBack
    )
    {
        ssize_t writeLength = AppendUnsafe(length, data);

        if (writeLength != length) {
            fallBack(
                *this,
                PageChacheAppendFailureArgs{
                    static_cast<const byte*>(data) + writeLength,
                    length - writeLength
                }
            );
        }
    }

    inline ssize_t PageChache::AppendUnsafe(
        ssize_t length,
        const void* data
    ) noexcept
    {
        ssize_t writeLength;

        if (m_length + length > PageSize()) {
            writeLength = PageSize() - m_length;
        }
        else {
            writeLength = length;
        }

        byte* itr = m_p + m_length;
        byte* end = itr + writeLength;
        const byte* pWriteData = static_cast<const byte*>(data);

        while (itr != end) {
            *itr = *pWriteData;
            ++itr;
            ++pWriteData;
        }

        m_length += writeLength;

        return writeLength;
    }

    inline ssize_t PageChache::Capacity() const noexcept
    {
        return static_cast<ssize_t>(
            Memory::MemoryPageHelper::PageSize()
        );
    }

    constexpr void PageChache::Clear() noexcept
    {
        m_length = 0;
    }

    constexpr Hash::ResultType
    PageChache::GetHashCode() const noexcept
    {
        return m_page.GetHashCode();
    }
}

#endif //!KLIB_KONGKONG_CONTAINERS_PAGECACHE_H