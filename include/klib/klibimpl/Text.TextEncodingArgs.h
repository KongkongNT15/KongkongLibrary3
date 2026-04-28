#ifndef KLIB_TEXT_TEXTENCODINGARGS_H
#define KLIB_TEXT_TEXTENCODINGARGS_H

#include "base.h"
#include "Foundation.ValueType.h"

namespace klib::Text
{
    template <CChar TBase, CChar TResult>
    struct TextEncodingArgs : ValueType {
        public:

        const TBase* Source;
        ssize_t CharLength;
        TResult Result;
        bool Success;

        constexpr TextEncodingArgs(
            const TBase* source,
            ssize_t charLength,
            TResult result,
            bool success
        ) noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;
    };
}

namespace klib::Text
{
    template <CChar TBase, CChar TResult>
    constexpr TextEncodingArgs<TBase, TResult>::TextEncodingArgs(
        const TBase* Source,
        ssize_t CharLength,
        TResult Result,
        bool Success
    ) noexcept
        : Source(source)
        , CharLength(charLength)
        , Result(result)
        , Success(success)
    {
    }

    template <CChar TBase, CChar TResult>
    constexpr Hash::ResultType
    TextEncodingArgs<TBase, TResult>::GetHashCode() const noexcept
    {
        return 
              Hash::Get(Source)
            + Hash::Get(CharLength)
            + Hash::Get(Result)
            + Hash::Get(Success)
        ;
    }
}

#endif //!KLIB_TEXT_TEXTENCODINGARGS_H