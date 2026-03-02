#ifndef KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCACTION_H
#define KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCACTION_H

#include "base.h"

namespace klib::Kongkong::Threading::Async
{
    template <>
    struct AsyncOperation<void> : public AwaiterBase {

        public:

        using ResultType = void;

        [[nodiscard]]
        static AsyncOperation DelayAsync(
            uint32_t milliSeconds
        ) noexcept;
    };
}

#endif //!KLIB_KONGKONG_THRAEDING_ASYNC_TASYNCACTION_H