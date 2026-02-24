#ifndef KLIB_KONGKONG_CONTAINERS_CONTAINERHELPER_H
#define KLIB_KONGKONG_CONTAINERS_CONTAINERHELPER_H

#include "base.h";

namespace klib::Kongkong::Containers
{
    /// <summary>
    /// 配列操作
    /// </summary>
    class ContainerHelper final {
    public:

        KLIB_STATIC_CLASS(ContainerHelper);

        /// <summary>
        /// IndexOf()で要素が見つからなかった時の戻り値
        /// </summary>
        [[nodiscard]] static consteval ssize_t NotFound() noexcept;

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
        [[nodiscard]] static constexpr bool ContainsUnsafe(
            ssize_t length,
            const T* p,
            T const& value
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
        [[nodiscard]] static constexpr bool EndsWithUnsafe(
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
        [[nodiscard]] static constexpr ssize_t IndexOfUnsafe(
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
        [[nodiscard]] constexpr bool StartsWithUnsafe(
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
        [[nodiscard]] constexpr bool StartsWithUnsafe(
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