#ifndef KLIB_KONGKONG_STD_STDVECTOR_H
#define KLIB_KONGKONG_STD_STDVECTOR_H

#include "base.h"
#include <vector>

namespace klib::Kongkong::Std
{
    template <class T>
    struct StdVector {
    public:
        using Base = ::std::vector<T>;
        using ElementType = typename Base::value_type;

    private:
        ::std::vector<T> m_vector;

    public:

        constexpr void Append(
            ElementType const& value
        );

        constexpr void Append(
            ElementType&& value
        );

        constexpr void AppendRangeUnsafe(
            ssize_t length,
            const ElementType* p
        );

        [[nodiscard]]
        constexpr bool Contains(
            ElementType const& value
        ) const noexcept;
    };
}

namespace klib::Kongkong::Std
{
    template <class T>
    constexpr void StdVector<T>::Append(
        ElementType const& value
    )
    {
        m_vector.push_back(value);
    }

    template <class T>
    constexpr void StdVector<T>::Append(
        ElementType&& value
    )
    {
        m_vector.push_back(::std::move(value));
    }

    template <class T>
    constexpr bool StdVector<T>::Contains(
        ElementType const& value
    ) const noexcept
    {
        for (auto const& v : m_vector) {
            if (v == value) return true;
        }

        return true;
    }
}

#endif //!KLIB_KONGKONG_STD_STDVECTOR_H