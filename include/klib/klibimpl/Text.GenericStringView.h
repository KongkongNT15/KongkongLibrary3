#ifndef KLIB_TEXT_GENERICSTRINGVIEW_H
#define KLIB_TEXT_GENERICSTRINGVIEW_H

#include "base.h"
#include "Containers.ArrayView.h"
#include "Text.StringHelper.h"

namespace klib::Text
{
    template <CChar TChar>
    struct GenericStringView : public Containers::ArrayView<TChar> {
        public:

        using Base = Containers::ArrayView<TChar>;
        using ElementType = typename Base::ElementType;

        private:

        static constexpr ElementType s_emptyStr = 0;

        public:

        consteval GenericStringView() noexcept;

        constexpr GenericStringView(
            const ElementType* other
        ) noexcept;

        constexpr GenericStringView(
            ssize_t length,
            const ElementType* str
        ) noexcept;

        constexpr GenericStringView(
            Base other
        ) noexcept;

        constexpr GenericStringView(
            GenericString<TChar> const& str
        ) noexcept;
    };

    template <CChar TChar>
    [[nodiscard]]
    constexpr bool operator==(
        GenericStringView<TChar> const& left,
        GenericStringView<TChar> const& right
    ) noexcept;

    template <CChar TChar>
    [[nodiscard]]
    constexpr bool operator!=(
        GenericStringView<TChar> const& left,
        GenericStringView<TChar> const& right
    ) noexcept;

    template <CChar TChar>
    [[nodiscard]]
    constexpr bool operator<(
        GenericStringView<TChar> const& left,
        GenericStringView<TChar> const& right
    ) noexcept;

    template <CChar TChar>
    [[nodiscard]]
    constexpr bool operator<=(
        GenericStringView<TChar> const& left,
        GenericStringView<TChar> const& right
    ) noexcept;

    template <CChar TChar>
    [[nodiscard]]
    constexpr bool operator>(
        GenericStringView<TChar> const& left,
        GenericStringView<TChar> const& right
    ) noexcept;

    template <CChar TChar>
    [[nodiscard]]
    constexpr bool operator>=(
        GenericStringView<TChar> const& left,
        GenericStringView<TChar> const& right
    ) noexcept;

    template <CChar TChar>
    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        GenericStringView<TChar> const& left,
        GenericStringView<TChar> const& right
    ) noexcept;
}

namespace klib::Text
{
    template <CChar TChar>
    constexpr GenericStringView<TChar>::GenericStringView(
        Base other
    ) noexcept
        : Base(
            other
        )
    {
    }

    template <CChar TChar>
    constexpr GenericStringView<TChar>::GenericStringView(
        const ElementType* other
    ) noexcept
        : Base()
    {
        if (other == nullptr) [[unlikely]] {
            this->m_length = 0;
            this->m_p = nullptr;
        }
        else {
            this->m_length = StringHelper::GetLengthUnsafe(other);
            this->m_p = other;
        }
    }

    template <CChar TChar>
    constexpr GenericStringView<TChar>::GenericStringView(
        ssize_t length,
        const ElementType* str
    ) noexcept
        : Base(
            length,
            str
        )
    {
    }

    template <CChar TChar>
    consteval GenericStringView<TChar>::GenericStringView(
    ) noexcept
        : Base(
            0,
            &s_emptyStr
        )
    {
    }
}

#endif //!KLIB_TEXT_GENERICSTRINGVIEW_H