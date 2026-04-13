#ifndef KLIB_KONGKONG_STATELESSTYPE_H
#define KLIB_KONGKONG_STATELESSTYPE_H

#include "base.h"

namespace klib::Kongkong
{
    class StatelessType : public KLibType {
        public:

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;
    };
}

namespace klib::Kongkong
{
    constexpr Hash::ResultType
    StatelessType::GetHashCode() const noexcept
    {
        return 0;
    }
}

#endif //!KLIB_KONGKONG_STATELESSTYPE_H