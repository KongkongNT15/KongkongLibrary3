#ifndef KLIB_IO_STREAMRWRESULT_H
#define KLIB_IO_STREAMRWRESULT_H

#include "base.h"
#include "ValueType.h"

namespace klib::IO
{
    struct StreamRWResult : public ValueType {

        uint32_t BytesTransferred;
        bool Success;

        constexpr StreamRWResult(
            uint32_t bytesTransferred,
            bool success
        ) noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;
    };
}

namespace klib::IO
{
    constexpr StreamRWResult::StreamRWResult(
        uint32_t bytesTransferred,
        bool success
    ) noexcept
        : BytesTransferred(bytesTransferred)
        , Success(success)
    {
    }

    constexpr Hash::ResultType
    StreamRWResult::GetHashCode() const noexcept
    {
        auto h1 = Hash::Get(BytesTransferred);
        auto h2 = Hash::Get(Success);

        return h1 + h2;
    }
}

#endif //!KLIB_IO_STREAMRWRESULT_H
