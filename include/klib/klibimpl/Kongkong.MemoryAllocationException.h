#ifndef KLIB_KONGKONG_MEMORYALLOCATIONEXCEPTION_H
#define KLIB_KONGKONG_MEMORYALLOCATIONEXCEPTION_H

#include "base.h"

namespace klib::Kongkong
{
    struct MemoryAllocationException {
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
            TFunc f
        );
    };
}

namespace klib::Kongkong
{
    template <class TFunc>
    void MemoryAllocationException::CheckNull(
        const void* p,
        TFunc f
    )
    {
        if (p == nullptr) [[unlikely]] {
            f();

            throw MemoryAllocationException();
        }
    }
}

#endif //!KLIB_KONGKONG_MEMORYALLOCATIONEXCEPTION_H