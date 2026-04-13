#ifndef KLIB_KONGKONG_NUMERICS_NUMBERPARSERESULT_H
#define KLIB_KONGKONG_NUMERICS_NUMBERPARSERESULT_H

#include "base.h"
#include "Kongkong.ValueType.h"

namespace klib::Kongkong::Numerics
{
    template <class TNum> requires CNumber<TNum>
    struct NumberParseResult : public ValueType {
    private:
        TNum m_result;
        bool m_success;
    public:

        constexpr NumberParseResult() noexcept;

        constexpr NumberParseResult(
            TNum result
        ) noexcept;

        constexpr NumberParseResult(
            TNum result,
            bool success
        ) noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode(
        ) const noexcept;

        [[nodiscard]]
        constexpr TNum Result() const noexcept;

        constexpr void Result(
            TNum value
        ) noexcept;

        [[nodiscard]]
        constexpr bool Success() const noexcept;

        constexpr void Success(
            bool value
        ) noexcept;
    };
}

namespace klib::Kongkong::Numerics
{
    template <class TNum> requires CNumber<TNum>
    constexpr NumberParseResult<TNum>::NumberParseResult() noexcept
        : m_result(0)
        , m_success(false)
    {
    }

    template <class TNum> requires CNumber<TNum>
    constexpr NumberParseResult<TNum>::NumberParseResult(
        TNum result
    ) noexcept
        : m_result(result)
        , m_success(true)
    {
    }

    template <class TNum> requires CNumber<TNum>
    constexpr NumberParseResult<TNum>::NumberParseResult(
        TNum result,
        bool success
    ) noexcept
        : m_result(result)
        , m_success(success)
    {
    }

    template <class TNum> requires CNumber<TNum>
    constexpr Hash::ResultType
    NumberParseResult<TNum>::GetHashCode(
    ) const noexcept
    {
        return ::std::hash<TNum>().operator()(m_result) + m_success;
    }

    template <class TNum> requires CNumber<TNum>
    constexpr typename TNum
    NumberParseResult<TNum>::Result() const noexcept
    {
        return m_result;
    }

    template <class TNum> requires CNumber<TNum>
    constexpr void NumberParseResult<TNum>::Result(
        TNum value
    ) noexcept
    {
        m_result = value;
    }

    template <class TNum> requires CNumber<TNum>
    constexpr bool
    NumberParseResult<TNum>::Success() const noexcept
    {
        return m_success;
    }

    template <class TNum> requires CNumber<TNum>
    constexpr void NumberParseResult<TNum>::Success(
        bool value
    ) noexcept
    {
        m_success = value;
    }
}

#endif //!KLIB_KONGKONG_NUMERICS_NUMBERPARSERESULT_H