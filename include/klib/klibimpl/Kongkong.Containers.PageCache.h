#ifndef KLIB_KONGKONG_CONTAINERS_PAGECACHE_H
#define KLIB_KONGKONG_CONTAINERS_PAGECACHE_H

#include "base.h"
#include "Kongkong.ValueType.h"
#include "Kongkong.Containers.PageCacheAppendFailureArgs.h"
#include "Kongkong.Containers.Primitives.ArrayBase.h"
#include "Kongkong.Memory.MemoryPage.h"

namespace klib::Kongkong::Containers
{
    class PageCache : public Primitives::ArrayBase<byte>, ValueType {
        private:

        Memory::MemoryPage m_page;

        public:

        [[nodiscard]]
        static ssize_t PageSize() noexcept;

        PageCache();

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
    inline ssize_t PageCache::PageSize() noexcept
    {
        return static_cast<ssize_t>(
            Memory::MemoryPageHelper::PageSize()
        );
    }

    inline PageCache::PageCache()
        : Primitives::ArrayBase<byte>()
        , m_page()
    {
        m_p = static_cast<byte*>(m_page.Data());
    }

    inline bool PageCache::Append(
        byte value
    ) noexcept
    {
        if (m_length == PageSize()) [[unlikely]] return false;

        m_p[m_length] = value;
        ++m_length;

        return true;
    }

    template <class TPredicate>
    void PageCache::AppendWithFallBack(
        byte value,
        TPredicate&& fallBack
    )
    {
        if (!Append(value)) [[unlikely]] {
            fallBack(
                *this,
                PageCacheAppendFailureArgs{
                    &value,
                    1
                }
            );
        }
    }

    template <class TPredicate>
    void PageCache::AppendWithFallBackUnsafe(
        ssize_t length,
        const void* data,
        TPredicate&& fallBack
    )
    {
        ssize_t writeLength = AppendUnsafe(length, data);

        if (writeLength != length) {
            fallBack(
                *this,
                PageCacheAppendFailureArgs{
                    static_cast<const byte*>(data) + writeLength,
                    length - writeLength
                }
            );
        }
    }

    inline ssize_t PageCache::AppendUnsafe(
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

    inline ssize_t PageCache::Capacity() const noexcept
    {
        return static_cast<ssize_t>(
            Memory::MemoryPageHelper::PageSize()
        );
    }

    constexpr void PageCache::Clear() noexcept
    {
        m_length = 0;
    }

    constexpr Hash::ResultType
    PageCache::GetHashCode() const noexcept
    {
        return m_page.GetHashCode();
    }
}

#endif //!KLIB_KONGKONG_CONTAINERS_PAGECACHE_H