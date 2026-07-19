#ifndef KLIB_WINRT_HSTRING_H
#define KLIB_WINRT_HSTRING_H

#include "base.h"
#include <winstring.h>

namespace klib::WinRT
{
    class HString {
        public:
        using ElementType = char16_t;
        using SizeType = ::UINT32;
        private:

        ::HSTRING m_ref;

        explicit constexpr HString(
            ::HSTRING ref
        ) noexcept;

        public:

        [[nodiscard]]
        static HString Concat(
            HString const& left,
            HString const& right
        );

        [[nodiscard]]
        static int Compare(
            HString const& left,
            HString const& right
        ) noexcept;

        HString(
            StringView str
        );

        HString(
            SizeType length,
            const ElementType* str
        );

        HString(
            HString const& other
        ) noexcept;

        constexpr HString(
            HString&& other
        ) noexcept;

        constexpr ~HString();

        [[nodiscard]]
        ElementType operator[](
            SizeType index
        ) const noexcept;

        [[nodiscard]]
        const ElementType* begin() const noexcept;

        [[nodiscard]]
        const ElementType* end() const noexcept;

        [[nodiscard]]
        const ElementType* c_str() const noexcept;

        [[nodiscard]]
        StringView GetView() const noexcept;

        [[nodiscard]]
        bool IsEmpty() const noexcept;

        [[nodiscard]]
        SizeType Length() const noexcept;

        [[nodiscard]]
        HString SubString(
            SizeType startIndex
        ) const;
    };

    [[nodiscard]]
    bool operator==(
        HString const& left,
        HString const& right
    ) noexcept;

    [[nodiscard]]
    bool operator!=(
        HString const& left,
        HString const& right
    ) noexcept;

    [[nodiscard]]
    bool operator<(
        HString const& left,
        HString const& right
    ) noexcept;

    [[nodiscard]]
    bool operator<=(
        HString const& left,
        HString const& right
    ) noexcept;

    [[nodiscard]]
    bool operator>(
        HString const& left,
        HString const& right
    ) noexcept;

    [[nodiscard]]
    bool operator>=(
        HString const& left,
        HString const& right
    ) noexcept;

    [[nodiscard]]
    ::std::strong_ordering operator<=>(
        HString const& left,
        HString const& right
    ) noexcept;

    [[nodiscard]]
    HString operator+(
        HString const& left,
        HString const& right
    );
}

namespace klib::WinRT
{
    inline int HString::Compare(
        HString const& left,
        HString const& right
    ) noexcept
    {
        ::INT32 result;

        ::WindowsCompareStringOrdinal(
            left.m_ref,
            right.m_ref,
            &result
        );

        return result;
    }

    constexpr HString::HString(
        ::HSTRING ref
    ) noexcept
        : m_ref(ref)
    {
    }

    inline HString::HString(
        HString const& other
    ) noexcept
    {
        ::WindowsDuplicateString(
            other.m_ref,
            &m_ref
        );
    }

    constexpr HString::HString(
        HString&& other
    ) noexcept
        : m_ref(other.m_ref)
    {
        other.m_ref = nullptr;
    }

    constexpr HString::~HString()
    {
        if (m_ref == nullptr) return;

        ::WindowsDeleteString(m_ref);
    }

    inline HString::ElementType
    HString::operator[](
        SizeType index
    ) const noexcept
    {
        return c_str()[index];
    }

    inline const HString::ElementType*
    HString::begin() const noexcept
    {
        return c_str();
    }

    inline const HString::ElementType*
    HString::end() const noexcept
    {
        const wchar_t* p;
        SizeType length;

        p = ::WindowsGetStringRawBuffer(
            m_ref,
            &length
        );

        return reinterpret_cast<const ElementType*>(p + length);
    }

    inline const HString::ElementType*
    HString::c_str() const noexcept
    {
        return reinterpret_cast<const ElementType*>(
            ::WindowsGetStringRawBuffer(
                m_ref,
                nullptr
            )
        );
    }

    inline HString::SizeType
    HString::Length() const noexcept
    {
        return ::WindowsGetStringLen(m_ref);
    }

    inline bool HString::IsEmpty() const noexcept
    {
        return Length() == 0;
    }

    inline bool operator==(
        HString const& left,
        HString const& right
    ) noexcept
    {
        return HString::Compare(
            left,
            right
        ) == 0;
    }

    inline bool operator!=(
        HString const& left,
        HString const& right
    ) noexcept
    {
        return HString::Compare(
            left,
            right
        ) != 0;
    }

    inline bool operator<(
        HString const& left,
        HString const& right
    ) noexcept
    {
        return HString::Compare(
            left,
            right
        ) < 0;
    }

    inline bool operator<=(
        HString const& left,
        HString const& right
    ) noexcept
    {
        return HString::Compare(
            left,
            right
        ) <= 0;
    }

    inline bool operator>(
        HString const& left,
        HString const& right
    ) noexcept
    {
        return HString::Compare(
            left,
            right
        ) > 0;
    }

    inline bool operator>=(
        HString const& left,
        HString const& right
    ) noexcept
    {
        return HString::Compare(
            left,
            right
        ) >= 0;
    }

    inline ::std::strong_ordering operator<=>(
        HString const& left,
        HString const& right
    ) noexcept
    {
        int result = HString::Compare(
            left,
            right
        );

        if (result < 0) return ::std::strong_ordering::less;
        if (result > 0) return ::std::strong_ordering::greater;

        return ::std::strong_ordering::equivalent;
    }

    inline HString operator+(
        HString const& left,
        HString const& right
    )
    {
        return HString::Concat(
            left,
            right
        );
    }
}

#endif //!KLIB_WINRT_HSTRING_H