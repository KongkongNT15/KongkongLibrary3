#ifndef KLIB_FOUNDATION_SHAREDCOUNTER_H
#define KLIB_FOUNDATION_SHAREDCOUNTER_H

#include "base.h"
#include "Foundation.PointerType.h"

#include <atomic>

namespace klib::Foundation
{
    class SharedCounter : public PointerType {
        private:

        using CounterType = ::std::atomic<ssize_t>;

        CounterType* m_p;

        public:

        SharedCounter();

        SharedCounter(
            ssize_t count
        );

        SharedCounter(
            SharedCounter const& other
        ) noexcept;

        constexpr SharedCounter(
            SharedCounter&& other
        ) noexcept;

        [[nodiscard]]
        ssize_t DisposeUnsafe() noexcept;

        [[nodiscard]]
        ssize_t RemoveCountUnsafe() noexcept;
    };
}

namespace klib::Foundation
{
    inline SharedCounter::SharedCounter(
    )
        : SharedCounter(1)
    {
    }

    inline SharedCounter::SharedCounter(
        ssize_t count
    )
        : m_p(new CounterType(count))
    {
    }

    inline ssize_t
    SharedCounter::DisposeUnsafe() noexcept
    {
        return m_p->operator--();
    }

    inline ssize_t
    SharedCounter::RemoveCountUnsafe() noexcept
    {
        return m_p->operator--();
    }
}

#endif //!KLIB_FOUNDATION_SHAREDCOUNTER_H