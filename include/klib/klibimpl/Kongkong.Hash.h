#ifndef KLIB_KONGKONG_HASH_H
#define KLIB_KONGKONG_HASH_H

#include "base.h"

namespace klib::Kongkong
{
    struct Hash final {
        public:
        using ResultType = int64_t;

        KLIB_STATIC_CLASS(Hash);

        template <class T>
        [[deprecated("この関数は特殊化されていません。常に0を返します。")]]
        static ResultType Get(
            T const& value
        ) noexcept;
    };

    template <>
    constexpr Hash::ResultType Hash::Get<bool>(
        bool const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<char>(
        char const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<short>(
        short const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<int>(
        int const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<long>(
        long const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<long long>(
        long long const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<unsigned char>(
        unsigned char const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<signed char>(
        signed char const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<unsigned short>(
        unsigned short const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<unsigned int>(
        unsigned int const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<unsigned long>(
        unsigned long const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<unsigned long long>(
        unsigned long long const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<float>(
        float const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<double>(
        double const& value
    ) noexcept;

    template <>
    constexpr Hash::ResultType Hash::Get<long double>(
        long double const& value
    ) noexcept;
}

namespace klib::Kongkong
{
    template <class T>
    Hash::ResultType Hash::Get(
        T const&
    ) noexcept
    {
        return 0;
    }

    template <>
    constexpr Hash::ResultType Hash::Get<bool>(
        bool const& value
    ) noexcept
    {
        return ::std::hash<bool>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<char>(
        char const& value
    ) noexcept
    {
        return ::std::hash<char>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<short>(
        short const& value
    ) noexcept
    {
        return ::std::hash<short>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<int>(
        int const& value
    ) noexcept
    {
        return ::std::hash<int>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<long>(
        long const& value
    ) noexcept
    {
        return ::std::hash<long>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<long long>(
        long long const& value
    ) noexcept
    {
        return ::std::hash<long long>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<unsigned char>(
        unsigned char const& value
    ) noexcept
    {
        return ::std::hash<unsigned char>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<signed char>(
        signed char const& value
    ) noexcept
    {
        return ::std::hash<signed char>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<unsigned short>(
        unsigned short const& value
    ) noexcept
    {
        return ::std::hash<unsigned short>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<unsigned int>(
        unsigned int const& value
    ) noexcept
    {
        return ::std::hash<unsigned int>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<unsigned long>(
        unsigned long const& value
    ) noexcept
    {
        return ::std::hash<unsigned long>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<unsigned long long>(
        unsigned long long const& value
    ) noexcept
    {
        return ::std::hash<unsigned long long>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<float>(
        float const& value
    ) noexcept
    {
        return ::std::hash<float>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<double>(
        double const& value
    ) noexcept
    {
        return ::std::hash<double>().operator()(value);
    }

    template <>
    constexpr Hash::ResultType Hash::Get<long double>(
        long double const& value
    ) noexcept
    {
        return ::std::hash<long double>().operator()(value);
    }
}

#endif //!KLIB_KONGKONG_HASH_H