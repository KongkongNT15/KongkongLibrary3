#ifndef KLIB_KONGKONG_CONTAINERS_PAGECACHEAPPENDFAILUREARGS_H
#define KLIB_KONGKONG_CONTAINERS_PAGECACHEAPPENDFAILUREARGS_H

#include "base.h"
#include "Kongkong.ValueType.h"

namespace klib::Kongkong::Containers
{
    struct PageChacheAppendFailureArgs : public ValueType {
        const byte* RemainingData;
        ssize_t RemainingLength;

        constexpr PageChacheAppendFailureArgs(
            const byte* remainingData,
            ssize_t remainingLength
        ) noexcept;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;
    };
}

namespace klib::Kongkong::Containers
{
    constexpr PageChacheAppendFailureArgs::PageChacheAppendFailureArgs(
        const byte* remainingData,
        ssize_t remainingLength
    ) noexcept
        : RemainingData(remainingData)
        , RemainingLength(remainingLength)
    {
    }

    constexpr Hash::ResultType
    PageChacheAppendFailureArgs::GetHashCode() const noexcept
    {
        ssize_t h1 = ::std::hash<const void*>().operator()(RemainingData);
        
        return h1 + RemainingLength;
    }
}

#endif //!KLIB_KONGKONG_CONTAINERS_PAGECACHEAPPENDFAILUREARGS_H