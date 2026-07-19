#ifndef KLIB_TEXT_GENERICSTRING_H
#define KLIB_TEXT_GENERICSTRING_H

#include "base.h"
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

        SizeType m_length;
        const ElementType* m_p;

        // nullptrなら静的文字列
        ::std::atomic<SizeType>* m_pRefCount;

        void DoAllocUnsafe(
            SizeType n
        );

        public:

        template <class TArray> requires ::std::is_array_v<TArray> //&& ::std::is_convertible_v<TArray, const ElementType*>
        consteval GenericString(
            TArray&& array
        ) noexcept;

        GenericString(
            SizeType n,
            ElementType c
        );

        constexpr ~GenericString();

        [[nodiscard]]
        constexpr ElementType operator[](
            SizeType index
        ) const noexcept;

        [[nodiscard]]
        constexpr const ElementType* begin() const noexcept;

        [[nodiscard]]
        constexpr const ElementType* end() const noexcept;

        [[nodiscard]]
        constexpr SizeType Length() const noexcept;
    };
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
    template <class TArray> requires ::std::is_array_v<TArray> //&& ::std::is_convertible_v<TArray, const typename GenericString<TChar>::ElementType*>
    consteval GenericString<TChar>::GenericString(
        TArray&& array
    ) noexcept
        : m_length(::std::extent_v<TArray> - 1)
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
    constexpr GenericString<TChar>::~GenericString()
    {
        if (m_pRefCount == nullptr) return;

        if (m_pRefCount->operator--() == 0) {
            ::free(m_pRefCount);
        }
    }

    template <CChar TChar>
    constexpr typename GenericString<TChar>::ElementType
    GenericString<TChar>::operator[](
        SizeType index
    ) const noexcept
    {
        return m_p[index];
    }
}

#endif //!KLIB_TEXT_GENERICSTRING_H
