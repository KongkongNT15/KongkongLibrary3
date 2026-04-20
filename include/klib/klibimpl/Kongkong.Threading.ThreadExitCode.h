#ifndef KLIB_KONGKONG_THREADING_THREADEXITCODE_H
#define KLIB_KONGKONG_THREADING_THREADEXITCODE_H

#include "base.h"
#include "Kongkong.ValueType.h"

namespace klib::Kongkong::Threading
{
    struct ThreadExitCode : public ValueType {
        public:
        int Code;
        bool Success;

        constexpr ThreadExitCode() noexcept;

        constexpr ThreadExitCode(
            int code
        ) noexcept;

        constexpr ThreadExitCode(
            int code,
            bool success
        ) noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode(
        ) const noexcept;
    };
}

namespace klib::Kongkong::Threading
{
    constexpr ThreadExitCode::ThreadExitCode() noexcept
        : ThreadExitCode(
            0,
            false
        )
    {
    }

    constexpr ThreadExitCode::ThreadExitCode(
        int code
    ) noexcept
        : ThreadExitCode(
            code,
            false
        )
    {
    }

    constexpr ThreadExitCode::ThreadExitCode(
        int code,
        bool success
    ) noexcept
        : Code(code)
        , Success(success)
    {
    }

    constexpr Hash::ResultType ThreadExitCode::GetHashCode(
    ) const noexcept
    {
        auto v = ::std::hash<int>().operator()(Code);
        return v + static_cast<int>(Success);
    }
}

#endif //!KLIB_KONGKONG_THREADING_THREADEXITCODE_H