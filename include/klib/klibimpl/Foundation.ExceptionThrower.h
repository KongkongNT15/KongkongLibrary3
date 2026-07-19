#ifndef KLIB_FOUNDATION_EXCEPTIONTHROWER_H
#define KLIB_FOUNDATION_EXCEPTIONTHROWER_H

#include "base.h"

namespace klib::Foundation
{
    class ExceptionThrower final {
        public:

        KLIB_STATIC_CLASS(ExceptionThrower);

        static void CheckAllockedMemory(
            const void* p
        );

        [[noreturn]]
        static void ThrowArgumentOutOfRange(
            const char16_t* message
        );

        [[noreturn]]
        static void ThrowMemoryAllocation(
            const char16_t* message
        );
    };
}

namespace klib::Foundation
{
    void ExceptionThrower::CheckAllockedMemory(
        const void* p
    )
    {
        if (p == nullptr) [[unlikely]] {
            ThrowMemoryAllocation(u"メモリの確保に失敗しました");
        }
    }
}

#endif //!KLIB_FOUNDATION_EXCEPTIONTHROWER_H