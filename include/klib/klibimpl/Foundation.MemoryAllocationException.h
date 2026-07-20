#ifndef KLIB_FOUNDATION_MEMORYALLOCATIONEXCEPTION_H
#define KLIB_FOUNDATION_MEMORYALLOCATIONEXCEPTION_H

#include "base.h"
#include "Foundation.MemoryException.h"

namespace klib::Foundation
{
    struct MemoryAllocationException : public MemoryException {
        private:

        static constexpr char16_t s_defaultMessage[] = u"メモリの確保に失敗しました。";

        public:

        static void CheckNull(
            const void* p
        );

        /// <summary>
        /// ポインターpがnullptrのとき関数f()を実行し、その後例外をスローする
        /// </summary>
        /// <typeparam name="TFunc">引数なしの関数型</typeparam>
        /// <param name="p">ポインター</param>
        /// <param name="f">pがnullptrの時に実行する関数</param>
        template <class TFunc>
        static void CheckNull(
            const void* p,
            TFunc&& f
        );

        constexpr MemoryAllocationException() noexcept;
    };
}

namespace klib::Foundation
{
    void MemoryAllocationException::CheckNull(
        const void* p
    )
    {
        if (p == nullptr) [[unlikely]] throw MemoryAllocationException();
    }

    template <class TFunc>
    void MemoryAllocationException::CheckNull(
        const void* p,
        TFunc&& f
    )
    {
        if (p == nullptr) [[unlikely]] {
            f();

            throw MemoryAllocationException();
        }
    }
}

#endif //!KLIB_FOUNDATION_MEMORYALLOCATIONEXCEPTION_H
