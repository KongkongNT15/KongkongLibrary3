#ifndef KLIB_KONGKONG_CONTAINERS_CONTAINERHELPER_H
#define KLIB_KONGKONG_CONTAINERS_CONTAINERHELPER_H

#include "base.h";

namespace klib::Kongkong::Containers
{
    /// <summary>
    /// 配列操作
    /// </summary>
    class ContainerHelper final {
    private:

        [[noreturn]]
        static void do_throwIndexError();

        [[noreturn]]
        static void do_throwIndexMinus();

        [[noreturn]]
        static void do_throwLengthZero();
    public:

        KLIB_STATIC_CLASS(ContainerHelper);

        /// <summary>
        /// IndexOf()で要素が見つからなかった時の戻り値
        /// </summary>
        [[nodiscard]]
        static consteval ssize_t NotFound() noexcept;

        static void CheckIndex(
            ssize_t index,
            ssize_t length
        );

        static ssize_t CheckIndexFromEnd(
            ssize_t indexFromEnd,
            ssize_t length
        );

        /// @brief 長さがゼロの時に例外をスロー
        /// @param length 
        static void CheckLengthZero(
            ssize_t length
        );

        /// <summary>
        /// ふぁ！？っく
        /// </summary>
        template <class T>
        static bool ContainsUnsafe(
            ssize_t,
            ::std::nullptr_t,
            T const&
        ) = delete;

        /// <summary>
        /// 指定した要素が配列に含まれるかを判定
        /// </summary>
        /// <typeparam name="T">要素型</typeparam>
        /// <param name="length">配列の長さ</param>
        /// <param name="p">配列へのポインター</param>
        /// <param name="value">要素</param>
        /// <returns>判定結果</returns>
        template <class T>
        [[nodiscard]]
        static constexpr bool ContainsUnsafe(
            ssize_t length,
            const T* p,
            T const& value
        ) noexcept;

        template <class TIterator>
        static constexpr void DestructUnsafe(
            TIterator begin,
            TIterator end
        ) noexcept;

        /// <summary>
        /// ふぁ！？っく
        /// </summary>
        template <class T>
        static bool EndsWithUnsafe(
            ssize_t,
            ::std::nullptr_t,
            T const&
        ) = delete;

        /// <summary>
        /// 指定した要素が配列の最後の要素と一致するかを判定
        /// </summary>
        /// <typeparam name="T">要素型</typeparam>
        /// <param name="length">配列の長さ</param>
        /// <param name="p">配列へのポインター</param>
        /// <param name="value">要素</param>
        /// <returns>判定結果</returns>
        template <class T>
        [[nodiscard]]
        static constexpr bool EndsWithUnsafe(
            ssize_t length,
            const T* p,
            T const& value
        ) noexcept;

        /// <summary>
        /// ふぁ！？っく
        /// </summary>
        template <class T>
        static ssize_t IndexOfUnsafe(
            ssize_t,
            ::std::nullptr_t,
            T const&
        ) = delete;

        /// <summary>
        /// 指定した要素の要素番号を取得
        /// </summary>
        /// <typeparam name="T">要素型</typeparam>
        /// <param name="length">配列の長さ</param>
        /// <param name="p">配列へのポインター</param>
        /// <param name="value">要素</param>
        /// <returns>指定した要素がある要素番号 見つからない場合はNotFound()</returns>
        template <class T>
        [[nodiscard]]
        static constexpr ssize_t IndexOfUnsafe(
            ssize_t length,
            const T* p,
            T const& value
        ) noexcept;

        /// <summary>
        /// ふぁ！？っく
        /// </summary>
        template <class T>
        static bool StartsWithUnsafe(
            ::std::nullptr_t,
            T const&
        ) = delete;

        /// <summary>
        /// ふぁ！？っく
        /// </summary>
        template <class T>
        static bool StartsWithUnsafe(
            ssize_t,
            ::std::nullptr_t,
            T const&
        ) = delete;

        /// <summary>
        /// 指定した要素が配列の最初の要素と一致するかを判定
        /// </summary>
        /// <typeparam name="T">要素型</typeparam>
        /// <param name="p">配列へのポインター</param>
        /// <param name="value">要素</param>
        /// <returns>判定結果</returns>
        template <class T>
        [[nodiscard]]
        constexpr bool StartsWithUnsafe(
            const T* p,
            T const& value
        ) noexcept;

        /// <summary>
        /// 指定した要素が配列の最初の要素と一致するかを判定
        /// </summary>
        /// <typeparam name="T">要素型</typeparam>
        /// <param name="length">配列の長さ</param>
        /// <param name="p">配列へのポインター</param>
        /// <param name="value">要素</param>
        /// <returns>判定結果</returns>
        template <class T>
        [[nodiscard]]
        constexpr bool StartsWithUnsafe(
            ssize_t length,
            const T* p,
            T const& value
        ) noexcept;
    };
}

namespace klib::Kongkong::Containers
{
    consteval ssize_t ContainerHelper::NotFound() noexcept
    {
        return -1;
    }

    inline void ContainerHelper::CheckIndex(
        ssize_t index,
        ssize_t length
    )
    {
        if (index < 0) [[unlikely]] do_throwIndexMinus();
        if (index >= length) [[unlikely]] do_throwIndexError();
    }

    inline ssize_t ContainerHelper::CheckIndexFromEnd(
        ssize_t indexFromEnd,
        ssize_t length
    )
    {
        ssize_t index = length - indexFromEnd;
        if (indexFromEnd <= 0 || index < 0) [[unlikely]] do_throwIndexError();

        return index;
    }

    inline void ContainerHelper::CheckLengthZero(
        ssize_t length
    )
    {
        if (length == 0) [[unlikely]] do_throwLengthZero();
    }

    template <class T>
    constexpr bool ContainerHelper::ContainsUnsafe(
        ssize_t length,
        const T* p,
        T const& value
    ) noexcept
    {
        const T* end = p + length;

        while (p != end) {
            if (*p == value) return true;
            ++p;
        }

        return false;
    }

    template <class TIterator>
    constexpr void ContainerHelper::DestructUnsafe(
        TIterator begin,
        TIterator end
    ) noexcept
    {
        using elementType = decltype(*begin);
        while (begin != end) {
            begin->~elementType();
            ++begin;
        }
    }

    template <class T>
    constexpr bool ContainerHelper::EndsWithUnsafe(
        ssize_t length,
        const T* p,
        T const& value
    ) noexcept
    {
        return p[length - 1] == value;
    }

    template <class T>
    constexpr ssize_t ContainerHelper::IndexOfUnsafe(
        ssize_t length,
        const T* p,
        T const& value
    ) noexcept
    {
        const T* itr = p;
        const T* end = p + length;

        while (itr != end) {
            if (*itr == value) return itr - p;
            ++itr;
        }

        return NotFound();
    }

    template <class T>
    constexpr bool ContainerHelper::StartsWithUnsafe(
        const T* p,
        T const& value
    ) noexcept
    {
        return *p == value;
    }

    template <class T>
    constexpr bool ContainerHelper::StartsWithUnsafe(
        ssize_t length,
        const T* p,
        T const& value
    ) noexcept
    {
        return length != 0 && *p == value;
    }
}

#endif //!KLIB_KONGKONG_CONTAINERS_CONTAINERHELPER_H