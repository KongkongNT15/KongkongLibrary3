#ifndef KLIB_TEXT_GENERICSTRING_H
#define KLIB_TEXT_GENERICSTRING_H

#define nameof(name) ::klib::Foundation::String(u ## #name)

#include "base.h"
#include "Containers.ArrayView.h"
#include "Text.GenericStringView.h"
#include "Text.StringHelper.h"
#include "Foundation.ExceptionThrower.h"

#include <atomic>
#include <bit>

namespace klib::Text
{
    template <CChar TChar>
    class GenericString {
        public:

        using ElementType = TChar;
        using SizeType = ssize_t;

        private:

        static constexpr ElementType s_emptyStr = 0;

        SizeType m_length;
        const ElementType* m_p;

        // nullptrなら静的文字列
        ::std::atomic<SizeType>* m_pRefCount;

        void DoAllocUnsafe(
            SizeType n
        );

        constexpr void DoRemove() noexcept;

        public:

        [[nodiscard]]
        static constexpr GenericString FromStaticCharsUnsafe(
            const ElementType* chars
        );

        [[nodiscard]]
        static constexpr GenericString FromStaticCharsUnsafe(
            ssize_t length,
            const ElementType* chars
        );

        consteval GenericString() noexcept;

        template <ssize_t N>
        consteval GenericString(
            const ElementType(&arr)[N]
        ) noexcept;

        GenericString(
            GenericStringView<TChar> sv
        );

        GenericString(
            SizeType n,
            ElementType c
        );

        constexpr GenericString(
            GenericString const& other
        ) noexcept;

        constexpr GenericString(
            GenericString&& other
        ) noexcept;

        constexpr ~GenericString();

        constexpr GenericString& operator=(
            GenericString const& other
        ) noexcept;

        constexpr GenericString& operator=(
            GenericString&& other
        ) noexcept;

        [[nodiscard]]
        constexpr ElementType operator[](
            SizeType index
        ) const noexcept;

        [[nodiscard]]
        constexpr const ElementType* begin() const noexcept;

        [[nodiscard]]
        constexpr const ElementType* c_str() const noexcept;

        [[nodiscard]]
        constexpr const ElementType* end() const noexcept;

        [[nodiscard]]
        constexpr const ElementType* Data() const noexcept;

        [[nodiscard]]
        constexpr bool IsEmpty() const noexcept;

        [[nodiscard]]
        constexpr SizeType Length() const noexcept;
    };

    template <CChar TChar>
    [[nodiscard]]
    constexpr bool operator==(
        GenericString<TChar> const& left,
        GenericString<TChar> const& right
    ) noexcept;
}

namespace klib::Text
{
    template <CChar TChar>
    constexpr GenericStringView<TChar>::GenericStringView(
        GenericString<TChar> const& str
    ) noexcept
        : Base(
            str.Length(),
            str.Data()
        )
    {
    }
}

namespace klib::Text
{
    template <CChar TChar>
    void GenericString<TChar>::DoAllocUnsafe(
        SizeType n
    )
    {
        void* p = ::malloc(sizeof(*m_pRefCount) + (n + 1) * sizeof(ElementType));

        ExceptionThrower::CheckAllockedMemory(p);

        m_pRefCount = static_cast<decltype(m_pRefCount)>(p);

        new (m_pRefCount) ::std::atomic<SizeType>(1);

        // 参照カウントの後ろに文字列を配置
        m_p = reinterpret_cast<decltype(m_p)>(m_pRefCount + 1);
    }

    template <CChar TChar>
    constexpr void GenericString<TChar>::DoRemove() noexcept
    {
        if (m_pRefCount == nullptr) return;

        if (m_pRefCount->operator--() == 0) {
            ::free(m_pRefCount);
        }
    }

    template <CChar TChar>
    constexpr GenericString<TChar>
    GenericString<TChar>::FromStaticCharsUnsafe(
        const ElementType* chars
    )
    {
        FromStaticCharsUnsafe(
            StringHelper::GetLengthUnsafe(chars),
            chars
        );
    }

    template <CChar TChar>
    constexpr GenericString<TChar>
    GenericString<TChar>::FromStaticCharsUnsafe(
        ssize_t length,
        const ElementType* chars
    )
    {
        GenericString<TChar> str;

        str.m_length = length;
        str.m_p = chars;

        return str;
    }

    template <CChar TChar>
    consteval GenericString<TChar>::GenericString() noexcept
        : m_length(0)
        , m_p(&s_emptyStr)
        , m_pRefCount(nullptr)
    {
    }

    template <CChar TChar>
    template <ssize_t N>
    consteval GenericString<TChar>::GenericString(
        const ElementType(&arr)[N]
    ) noexcept
        : m_length(N - 1)
        , m_p(arr)
        , m_pRefCount(nullptr)
    {
    }

    template <CChar TChar>
    GenericString<TChar>::GenericString(
        SizeType n,
        ElementType c
    )
        : m_length(n)
        , m_p()
        , m_pRefCount()
    {
        if (n <= 0) [[unlikely]] throw ExceptionThrower::ThrowArgumentOutOfRange(u"");

        DoAllocUnsafe(n);

        auto p = m_p;
        auto e = p + n;

        while (p != e) {
            *p = c;
            ++p;
        }

        *p = 0;
    }

    template <CChar TChar>
    constexpr GenericString<TChar>::GenericString(
        GenericString<TChar> const& other
    ) noexcept
        : m_length(other.m_length)
        , m_p(other.m_p)
        , m_pRefCount(other.m_pRefCount)
    {
        if (m_pRefCount == nullptr) return;

        m_pRefCount->operator++();
    }

    template <CChar TChar>
    constexpr GenericString<TChar>::GenericString(
        GenericString<TChar>&& other
    ) noexcept
        : m_length(other.m_length)
        , m_p(other.m_p)
        , m_pRefCount(other.m_pRefCount)
    {
        other.m_pRefCount = nullptr;
    }

    template <CChar TChar>
    constexpr GenericString<TChar>::~GenericString()
    {
        DoRemove();
    }

    template <CChar TChar>
    constexpr GenericString<TChar>&
    GenericString<TChar>::operator=(
        GenericString<TChar> const& other
    ) noexcept
    {
        if (&other != this) [[likely]] {
            DoRemove();

            m_length = other.m_length;
            m_p = other.m_p;
            m_pRefCount = other.m_pRefCount;

            if (m_pRefCount != nullptr) {
                m_pRefCount->operator++();
            }
        }

        return *this;
    }

    template <CChar TChar>
    constexpr GenericString<TChar>&
    GenericString<TChar>::operator=(
        GenericString<TChar>&& other
    ) noexcept
    {
        if (&other != this) [[likely]] {
            DoRemove();

            m_length = other.m_length;
            m_p = other.m_p;
            m_pRefCount = other.m_pRefCount;

            other.m_pRefCount = nullptr;
        }

        return *this;
    }

    template <CChar TChar>
    constexpr typename GenericString<TChar>::ElementType
    GenericString<TChar>::operator[](
        SizeType index
    ) const noexcept
    {
        return m_p[index];
    }

    template <CChar TChar>
    constexpr const typename GenericString<TChar>::ElementType*
    GenericString<TChar>::begin() const noexcept
    {
        return m_p;
    }

    template <CChar TChar>
    constexpr const typename GenericString<TChar>::ElementType*
    GenericString<TChar>::c_str() const noexcept
    {
        return m_p;
    }

    template <CChar TChar>
    constexpr const typename GenericString<TChar>::ElementType*
    GenericString<TChar>::end() const noexcept
    {
        return m_p + m_length;
    }

    template <CChar TChar>
    constexpr bool
    GenericString<TChar>::IsEmpty() const noexcept
    {
        return m_length == 0;
    }

    template <CChar TChar>
    constexpr typename GenericString<TChar>::SizeType
    GenericString<TChar>::Length() const noexcept
    {
        return m_length;
    }
}

#endif //!KLIB_TEXT_GENERICSTRING_H
