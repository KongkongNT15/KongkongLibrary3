#ifndef KLIB_KONGKONG_MEMORY_GCOBJECTBASE_H
#define KLIB_KONGKONG_MEMORY_GCOBJECTBASE_H

#include "base.h"

#include <atomic>

namespace klib::Kongkong::Memory
{
    struct GCObjectBase {
    private:
        
        /// <summary>
        /// 使用中
        /// </summary>
        ::std::atomic<ssize_t> m_activeCount;

        /// <summary>
        /// 参照カウント
        /// </summary>
        ::std::atomic<ssize_t> m_referenceCount;
        
    protected:

        GCObjectBase() noexcept;

    public:

        virtual ~GCObjectBase() = default;

        [[nodiscard]]
        ssize_t ActiveCount() const noexcept;

        [[nodiscard]]
        ssize_t ReferenceCount() const noexcept;

        ssize_t AddActiveCount() noexcept;

        ssize_t AddReferenceCount() noexcept;

        ssize_t ReleaseActiveCount() noexcept;

        ssize_t ReleaseReferenceCount() noexcept;
    };
}

namespace klib::Kongkong::Memory
{
    inline GCObjectBase::GCObjectBase() noexcept
        : m_activeCount(0)
        , m_referenceCount(1)
    {
    }

    inline ssize_t GCObjectBase::ActiveCount() const noexcept
    {
        return m_activeCount;
    }

    inline ssize_t GCObjectBase::ReferenceCount() const noexcept
    {
        return m_referenceCount;
    }

    inline ssize_t GCObjectBase::AddActiveCount() noexcept
    {
        return ++m_activeCount;
    }

    inline ssize_t GCObjectBase::AddReferenceCount() noexcept
    {
        return ++m_referenceCount;
    }

    inline ssize_t GCObjectBase::ReleaseActiveCount() noexcept
    {
        return --m_activeCount;
    }

    inline ssize_t GCObjectBase::ReleaseReferenceCount() noexcept
    {
        return --m_referenceCount;
    }
}

#endif //!KLIB_KONGKONG_MEMORY_GCOBJECTBASE_H