#ifndef KLIB_TEXT_STRINGHELPER_H
#define KLIB_TEXT_STRINGHELPER_H

#include "base.h"

namespace klib::Text
{
    class StringHelper final {
        private:

        public:

        KLIB_STATIC_CLASS(StringHelper);

        /// @brief 文字列が空ならエラー
        /// @param p 文字列
        /// @throws ArgumentNullException: pがnullptrのとき
        /// @throws InvalidArgumentException: 文字列が空の時
        static void CheckEmpty(const char16_t* p);

        /// @brief 文字列が空ならエラー
        /// @param str 文字列
        /// @throws InvalidArgumentException: 文字列が空の時
        static void CheckEmpty(String const& str);

        /// @brief 文字列が空ならエラー
        /// @param str 文字列
        /// @throws InvalidArgumentException: 文字列が空の時
        static void CheckEmpty(StringView const& str);

        /// @brief 文字列が空ならエラー
        /// @param p 文字列
        /// @throws InvalidArgumentException: 文字列が空の時
        static void CheckEmptyUnsafe(const char16_t* p);

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, char) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, wchar_t) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, char8_t) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, char16_t) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, char32_t) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, const char*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, ssize_t, const char*) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, const wchar_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, ssize_t, const wchar_t*) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, const char8_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, ssize_t, const char8_t*) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, const char16_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, ssize_t, const char16_t*) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, const char32_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool Contains(ssize_t, std::nullptr_t, ssize_t, const char32_t*) = delete;

        /// @brief 指定した文字がソースに含まれるかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param target 探す文字
        /// @throws ArgumentNullException: sourceがnullptrのとき
        /// @throws InvalidArgumentException: lengthSourceが負の値の時
        [[nodiscard]] static bool Contains(ssize_t lengthSource, const char* source, char target);
        [[nodiscard]] static bool Contains(ssize_t lengthSource, const wchar_t* source, wchar_t target);
        [[nodiscard]] static bool Contains(ssize_t lengthSource, const char8_t* source, char8_t target);
        [[nodiscard]] static bool Contains(ssize_t lengthSource, const char16_t* source, char16_t target);
        [[nodiscard]] static bool Contains(ssize_t lengthSource, const char32_t* source, char32_t target);

        /// @brief 指定した文字列がソースに含まれるかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param lengthTarget 探す文字列の長さ
        /// @param target 探す文字列
        /// @throws ArgumentNullException: sourceがnullptrのとき
        /// @throws ArgumentNullException: targetがnullptrのとき
        /// @throws InvalidArgumentException: lengthSourceが負の値の時
        /// @throws InvalidArgumentException: lengthTargetが負の値の時
        [[nodiscard]] static bool Contains(ssize_t lengthSource, const char* source, ssize_t lengthTarget, const char* target);
        [[nodiscard]] static bool Contains(ssize_t lengthSource, const wchar_t* source, ssize_t lengthTarget, const wchar_t* target);
        [[nodiscard]] static bool Contains(ssize_t lengthSource, const char8_t* source, ssize_t lengthTarget, const char8_t* target);
        [[nodiscard]] static bool Contains(ssize_t lengthSource, const char16_t* source, ssize_t lengthTarget, const char16_t* target);
        [[nodiscard]] static bool Contains(ssize_t lengthSource, const char32_t* source, ssize_t lengthTarget, const char32_t* target);

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, char) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, wchar_t) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, char8_t) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, char16_t) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, char32_t) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, const char*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, ssize_t, const char*) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, const wchar_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, ssize_t, const wchar_t*) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, const char8_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, ssize_t, const char8_t*) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, const char16_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, ssize_t, const char16_t*) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, const char32_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool ContainsUnsafe(ssize_t, std::nullptr_t, ssize_t, const char32_t*) = delete;

        /// @brief 指定した文字がソースに含まれるかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param target 探す文字
        [[nodiscard]] static constexpr ssize_t ContainsUnsafe(ssize_t lengthSource, const char* source, char target) noexcept { return _containsUnsafe(lengthSource, source, target); }
        [[nodiscard]] static constexpr ssize_t ContainsUnsafe(ssize_t lengthSource, const wchar_t* source, wchar_t target) noexcept { return _containsUnsafe(lengthSource, source, target); }
        [[nodiscard]] static constexpr ssize_t ContainsUnsafe(ssize_t lengthSource, const char8_t* source, char8_t target) noexcept { return _containsUnsafe(lengthSource, source, target); }
        [[nodiscard]] static constexpr ssize_t ContainsUnsafe(ssize_t lengthSource, const char16_t* source, char16_t target) noexcept { return _containsUnsafe(lengthSource, source, target); }
        [[nodiscard]] static constexpr ssize_t ContainsUnsafe(ssize_t lengthSource, const char32_t* source, char32_t target) noexcept { return _containsUnsafe(lengthSource, source, target); }

        /// @brief 指定した文字列がソースに含まれるかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param lengthTarget 探す文字列の長さ
        /// @param target 探す文字列
        [[nodiscard]] static constexpr ssize_t ContainsUnsafe(ssize_t lengthSource, const char* source, ssize_t lengthTarget, const char* target) noexcept { return _containsUnsafe(lengthSource, source, lengthTarget, target); }
        [[nodiscard]] static constexpr ssize_t ContainsUnsafe(ssize_t lengthSource, const wchar_t* source, ssize_t lengthTarget, const wchar_t* target) noexcept { return _containsUnsafe(lengthSource, source, lengthTarget, target); }
        [[nodiscard]] static constexpr ssize_t ContainsUnsafe(ssize_t lengthSource, const char8_t* source, ssize_t lengthTarget, const char8_t* target) noexcept { return _containsUnsafe(lengthSource, source, lengthTarget, target); }
        [[nodiscard]] static constexpr ssize_t ContainsUnsafe(ssize_t lengthSource, const char16_t* source, ssize_t lengthTarget, const char16_t* target) noexcept { return _containsUnsafe(lengthSource, source, lengthTarget, target); }
        [[nodiscard]] static constexpr ssize_t ContainsUnsafe(ssize_t lengthSource, const char32_t* source, ssize_t lengthTarget, const char32_t* target) noexcept { return _containsUnsafe(lengthSource, source, lengthTarget, target); }

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, char) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, wchar_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, char8_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, char16_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, char32_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, const char*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, ssize_t, const char*) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, const wchar_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, ssize_t, const wchar_t*) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, const char8_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, ssize_t, const char8_t*) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, const char16_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, ssize_t, const char16_t*) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, const char32_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWith(ssize_t, std::nullptr_t, ssize_t, const char32_t*) = delete;

        /// @brief ソース文字列が指定したサフィックスで終了するかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param suffix サフィックス
        /// @throws ArgumentNullException: sourceがnullptrのとき
        /// @throws InvalidArgumentException: lengthSourceが負の値の時
        [[nodiscard]] static bool EndsWith(ssize_t lengthSource, const char* source, char suffix);
        [[nodiscard]] static bool EndsWith(ssize_t lengthSource, const wchar_t* source, wchar_t suffix);
        [[nodiscard]] static bool EndsWith(ssize_t lengthSource, const char8_t* source, char8_t suffix);
        [[nodiscard]] static bool EndsWith(ssize_t lengthSource, const char16_t* source, char16_t suffix);
        [[nodiscard]] static bool EndsWith(ssize_t lengthSource, const char32_t* source, char32_t suffix);

        /// @brief ソース文字列が指定したサフィックスで終了するかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param lengthSuffix サフィックスの長さ
        /// @param suffix サフィックス
        /// @throws ArgumentNullException: sourceがnullptrのとき
        /// @throws ArgumentNullException: suffixがnullptrのとき
        /// @throws InvalidArgumentException: lengthSourceが負の値の時
        /// @throws InvalidArgumentException: lengthSuffixが負の値の時
        [[nodiscard]] static bool EndsWith(ssize_t lengthSource, const char* source, ssize_t lengthSuffix, const char* suffix);
        [[nodiscard]] static bool EndsWith(ssize_t lengthSource, const wchar_t* source, ssize_t lengthSuffix, const wchar_t* suffix);
        [[nodiscard]] static bool EndsWith(ssize_t lengthSource, const char8_t* source, ssize_t lengthSuffix, const char8_t* suffix);
        [[nodiscard]] static bool EndsWith(ssize_t lengthSource, const char16_t* source, ssize_t lengthSuffix, const char16_t* suffix);
        [[nodiscard]] static bool EndsWith(ssize_t lengthSource, const char32_t* source, ssize_t lengthSuffix, const char32_t* suffix);

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, char) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, wchar_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, char8_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, char16_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, char32_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, const char*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, const char*) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, const wchar_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, const wchar_t*) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, const char8_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, const char8_t*) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, const char16_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, const char16_t*) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, const char32_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool EndsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, const char32_t*) = delete;

        /// @brief ソース文字列が指定したサフィックスで終了するかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param suffix サフィックス
        [[nodiscard]] static constexpr bool EndsWithUnsafe(ssize_t lengthSource, const char* source, char suffix) noexcept { return _endsWithUnsafe(lengthSource, source, suffix); }
        [[nodiscard]] static constexpr bool EndsWithUnsafe(ssize_t lengthSource, const wchar_t* source, wchar_t suffix) noexcept { return _endsWithUnsafe(lengthSource, source, suffix); }
        [[nodiscard]] static constexpr bool EndsWithUnsafe(ssize_t lengthSource, const char8_t* source, char8_t suffix) noexcept { return _endsWithUnsafe(lengthSource, source, suffix); }
        [[nodiscard]] static constexpr bool EndsWithUnsafe(ssize_t lengthSource, const char16_t* source, char16_t suffix) noexcept { return _endsWithUnsafe(lengthSource, source, suffix); }
        [[nodiscard]] static constexpr bool EndsWithUnsafe(ssize_t lengthSource, const char32_t* source, char32_t suffix) noexcept { return _endsWithUnsafe(lengthSource, source, suffix); }

        /// @brief ソース文字列が指定したサフィックスで終了するかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param lengthSuffix サフィックスの長さ
        /// @param suffix サフィックス
        [[nodiscard]] static constexpr bool EndsWithUnsafe(ssize_t lengthSource, const char* source, ssize_t lengthSuffix, const char* suffix) noexcept { return _endsWithUnsafe(lengthSource, source, lengthSuffix, suffix); }
        [[nodiscard]] static constexpr bool EndsWithUnsafe(ssize_t lengthSource, const wchar_t* source, ssize_t lengthSuffix, const wchar_t* suffix) noexcept { return _endsWithUnsafe(lengthSource, source, lengthSuffix, suffix); }
        [[nodiscard]] static constexpr bool EndsWithUnsafe(ssize_t lengthSource, const char8_t* source, ssize_t lengthSuffix, const char8_t* suffix) noexcept { return _endsWithUnsafe(lengthSource, source, lengthSuffix, suffix); }
        [[nodiscard]] static constexpr bool EndsWithUnsafe(ssize_t lengthSource, const char16_t* source, ssize_t lengthSuffix, const char16_t* suffix) noexcept { return _endsWithUnsafe(lengthSource, source, lengthSuffix, suffix); }
        [[nodiscard]] static constexpr bool EndsWithUnsafe(ssize_t lengthSource, const char32_t* source, ssize_t lengthSuffix, const char32_t* suffix) noexcept { return _endsWithUnsafe(lengthSource, source, lengthSuffix, suffix); }

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, char) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, wchar_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, char8_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, char16_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, char32_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, const char*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, ssize_t, const char*) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, const wchar_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, ssize_t, const wchar_t*) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, const char8_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, ssize_t, const char8_t*) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, const char16_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, ssize_t, const char16_t*) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, const char32_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t Find(ssize_t, std::nullptr_t, ssize_t, const char32_t*) = delete;

        /// @brief ソース文字列内の文字を検索
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param target 探す文字
        /// @return 指定した文字が最初に現れるインデックス
        /// @return 見つからない場合はKongkong::Collections::CollectionHelper::NotFound()
        /// @throws ArgumentNullException: sourceがnullptrのとき
        /// @throws InvalidArgumentException: lengthSourceが負の値の時
        [[nodiscard]] static ssize_t Find(ssize_t lengthSource, const char* source, char target);
        [[nodiscard]] static ssize_t Find(ssize_t lengthSource, const wchar_t* source, wchar_t target);
        [[nodiscard]] static ssize_t Find(ssize_t lengthSource, const char8_t* source, char8_t target);
        [[nodiscard]] static ssize_t Find(ssize_t lengthSource, const char16_t* source, char16_t target);
        [[nodiscard]] static ssize_t Find(ssize_t lengthSource, const char32_t* source, char32_t target);

        /// @brief ソース文字列内の文字列を検索
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param lengthTarget 探す文字列の長さ
        /// @param target 探す文字列
        /// @return 指定した文字列が最初に現れるインデックス
        /// @return 見つからない場合はKongkong::Collections::CollectionHelper::NotFound()
        /// @throws ArgumentNullException: sourceがnullptrのとき
        /// @throws ArgumentNullException: targetがnullptrのとき
        /// @throws InvalidArgumentException: lengthSourceが負の値の時
        /// @throws InvalidArgumentException: lengthTargetが負の値の時
        [[nodiscard]] static ssize_t Find(ssize_t lengthSource, const char* source, ssize_t lengthTarget, const char* target);
        [[nodiscard]] static ssize_t Find(ssize_t lengthSource, const wchar_t* source, ssize_t lengthTarget, const wchar_t* target);
        [[nodiscard]] static ssize_t Find(ssize_t lengthSource, const char8_t* source, ssize_t lengthTarget, const char8_t* target);
        [[nodiscard]] static ssize_t Find(ssize_t lengthSource, const char16_t* source, ssize_t lengthTarget, const char16_t* target);
        [[nodiscard]] static ssize_t Find(ssize_t lengthSource, const char32_t* source, ssize_t lengthTarget, const char32_t* target);

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, char) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, wchar_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, char8_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, char16_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, char32_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, const char*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, ssize_t, const char*) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, const wchar_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, ssize_t, const wchar_t*) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, const char8_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, ssize_t, const char8_t*) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, const char16_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, ssize_t, const char16_t*) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, const char32_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static ssize_t FindUnsafe(ssize_t, std::nullptr_t, ssize_t, const char32_t*) = delete;

        /// @brief ソース文字列内の文字を検索
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param target 探す文字
        /// @return 指定した文字が最初に現れるインデックス
        /// @return 見つからない場合はKongkong::Collections::CollectionHelper::NotFound()
        [[nodiscard]] static constexpr ssize_t FindUnsafe(ssize_t lengthSource, const char* source, char target) noexcept { return _findUnsafe(lengthSource, source, target); }
        [[nodiscard]] static constexpr ssize_t FindUnsafe(ssize_t lengthSource, const wchar_t* source, wchar_t target) noexcept { return _findUnsafe(lengthSource, source, target); }
        [[nodiscard]] static constexpr ssize_t FindUnsafe(ssize_t lengthSource, const char8_t* source, char8_t target) noexcept { return _findUnsafe(lengthSource, source, target); }
        [[nodiscard]] static constexpr ssize_t FindUnsafe(ssize_t lengthSource, const char16_t* source, char16_t target) noexcept { return _findUnsafe(lengthSource, source, target); }
        [[nodiscard]] static constexpr ssize_t FindUnsafe(ssize_t lengthSource, const char32_t* source, char32_t target) noexcept { return _findUnsafe(lengthSource, source, target); }

        /// @brief ソース文字列内の文字列を検索
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param lengthTarget 探す文字列の長さ
        /// @param target 探す文字列
        /// @return 指定した文字列が最初に現れるインデックス
        /// @return 見つからない場合はKongkong::Collections::CollectionHelper::NotFound()
        [[nodiscard]] static constexpr ssize_t FindUnsafe(ssize_t lengthSource, const char* source, ssize_t lengthTarget, const char* target) noexcept { return _findUnsafe(lengthSource, source, lengthTarget, target); }
        [[nodiscard]] static constexpr ssize_t FindUnsafe(ssize_t lengthSource, const wchar_t* source, ssize_t lengthTarget, const wchar_t* target) noexcept { return _findUnsafe(lengthSource, source, lengthTarget, target); }
        [[nodiscard]] static constexpr ssize_t FindUnsafe(ssize_t lengthSource, const char8_t* source, ssize_t lengthTarget, const char8_t* target) noexcept { return _findUnsafe(lengthSource, source, lengthTarget, target); }
        [[nodiscard]] static constexpr ssize_t FindUnsafe(ssize_t lengthSource, const char16_t* source, ssize_t lengthTarget, const char16_t* target) noexcept { return _findUnsafe(lengthSource, source, lengthTarget, target); }
        [[nodiscard]] static constexpr ssize_t FindUnsafe(ssize_t lengthSource, const char32_t* source, ssize_t lengthTarget, const char32_t* target) noexcept { return _findUnsafe(lengthSource, source, lengthTarget, target); }

        /// @brief ふぁ！？っく
        static ssize_t GetLength(std::nullptr_t) = delete;
    
        /// @brief 文字列の長さを取得
        /// @param str 文字列
        /// @throws ArgumentNullException: strがnullptrのとき
        [[nodiscard]] static ssize_t GetLength(const char* str);
        [[nodiscard]] static ssize_t GetLength(const wchar_t* str);
        [[nodiscard]] static ssize_t GetLength(const char8_t* str);
        [[nodiscard]] static ssize_t GetLength(const char16_t* str);
        [[nodiscard]] static ssize_t GetLength(const char32_t* str);

        /// @brief ふぁ！？っく
        static ssize_t GetLengthUnsafe(std::nullptr_t) = delete;
    
        /// @brief 文字列の長さを取得
        /// @param str 文字列
        [[nodiscard]] static constexpr ssize_t GetLengthUnsafe(const char* str) noexcept { return _getLengthUnsafe(str); }
        [[nodiscard]] static constexpr ssize_t GetLengthUnsafe(const wchar_t* str) noexcept { return _getLengthUnsafe(str); }
        [[nodiscard]] static constexpr ssize_t GetLengthUnsafe(const char8_t* str) noexcept { return _getLengthUnsafe(str); }
        [[nodiscard]] static constexpr ssize_t GetLengthUnsafe(const char16_t* str) noexcept { return _getLengthUnsafe(str); }
        [[nodiscard]] static constexpr ssize_t GetLengthUnsafe(const char32_t* str) noexcept { return _getLengthUnsafe(str); }

        /// @brief ふぁ！？っく
        static ssize_t GetMultiByteLengthUnsafe(std::nullptr_t) = delete;

        /// @brief マルチバイト文字列の長さを取得
        /// @attention このAPIは無効な文字がないことを前提にしてるよ！
        /// @param str 文字列
        [[nodiscard]] static ssize_t GetMultiByteLengthUnsafe(const char8_t* str) noexcept;
        [[nodiscard]] static ssize_t GetMultiByteLengthUnsafe(const char16_t* str) noexcept;
        [[nodiscard]] static ssize_t GetMultiByteLengthUnsafe(const char32_t* str) noexcept;

        /// @brief ふぁ！？っく
        static bool IsNullOrEmpty(std::nullptr_t) = delete;

        /// @brief C文字列がNULLもしくは空であるかを判定
        /// @param str C文字列
        /// @return NULLもしくは空であればtrue そうでなければfalse
        [[nodiscard]] static constexpr bool IsNullOrEmpty(const char* str) noexcept { return _isNullOrEmpty(str); }
        [[nodiscard]] static constexpr bool IsNullOrEmpty(const wchar_t* str) noexcept { return _isNullOrEmpty(str); }
        [[nodiscard]] static constexpr bool IsNullOrEmpty(const char8_t* str) noexcept { return _isNullOrEmpty(str); }
        [[nodiscard]] static constexpr bool IsNullOrEmpty(const char16_t* str) noexcept { return _isNullOrEmpty(str); }
        [[nodiscard]] static constexpr bool IsNullOrEmpty(const char32_t* str) noexcept { return _isNullOrEmpty(str); }

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, char) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, wchar_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, char8_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, char16_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, char32_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, const char*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, ssize_t, const char*) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, const wchar_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, ssize_t, const wchar_t*) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, const char8_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, ssize_t, const char8_t*) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, const char16_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, ssize_t, const char16_t*) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, const char32_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWith(ssize_t, std::nullptr_t, ssize_t, const char32_t*) = delete;

        /// @brief ソース文字列が指定したプレフィックスで始まるかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param prefix プレフィックス
        /// @throws ArgumentNullException: sourceがnullptrのとき
        /// @throws InvalidArgumentException: lengthSourceが負の値の時
        [[nodiscard]] static bool StartsWith(ssize_t lengthSource, const char* source, char prefix);
        [[nodiscard]] static bool StartsWith(ssize_t lengthSource, const wchar_t* source, wchar_t prefix);
        [[nodiscard]] static bool StartsWith(ssize_t lengthSource, const char8_t* source, char8_t prefix);
        [[nodiscard]] static bool StartsWith(ssize_t lengthSource, const char16_t* source, char16_t prefix);
        [[nodiscard]] static bool StartsWith(ssize_t lengthSource, const char32_t* source, char32_t prefix);

        /// @brief ソース文字列が指定したプレフィックスで始まるかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param prefixLength プレフィックスの長さ
        /// @param prefix プレフィックス
        /// @throws ArgumentNullException: sourceがnullptrのとき
        /// @throws ArgumentNullException: prefixがnullptrのとき
        /// @throws InvalidArgumentException: lengthSourceが負の値の時
        /// @throws InvalidArgumentException: prefixLengthが負の値の時
        [[nodiscard]] static bool StartsWith(ssize_t lengthSource, const char* source, ssize_t prefixLength, const char* prefix);
        [[nodiscard]] static bool StartsWith(ssize_t lengthSource, const wchar_t* source, ssize_t prefixLength, const wchar_t* prefix);
        [[nodiscard]] static bool StartsWith(ssize_t lengthSource, const char8_t* source, ssize_t prefixLength, const char8_t* prefix);
        [[nodiscard]] static bool StartsWith(ssize_t lengthSource, const char16_t* source, ssize_t prefixLength, const char16_t* prefix);
        [[nodiscard]] static bool StartsWith(ssize_t lengthSource, const char32_t* source, ssize_t prefixLength, const char32_t* prefix);

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, char) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, wchar_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, char8_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, char16_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, char32_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, const char*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, const char*) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, const wchar_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, const wchar_t*) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, const char8_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, const char8_t*) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, const char16_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, const char16_t*) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, const char32_t*, ssize_t, std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        static bool StartsWithUnsafe(ssize_t, std::nullptr_t, ssize_t, const char32_t*) = delete;

        /// @brief ソース文字列が指定したプレフィックスで始まるかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param prefix プレフィックス
        [[nodiscard]] static constexpr bool StartsWithUnsafe(ssize_t lengthSource, const char* source, char prefix) noexcept { return _startsWithUnsafe(lengthSource, source, prefix); }
        [[nodiscard]] static constexpr bool StartsWithUnsafe(ssize_t lengthSource, const wchar_t* source, wchar_t prefix) noexcept { return _startsWithUnsafe(lengthSource, source, prefix); }
        [[nodiscard]] static constexpr bool StartsWithUnsafe(ssize_t lengthSource, const char8_t* source, char8_t prefix) noexcept { return _startsWithUnsafe(lengthSource, source, prefix); }
        [[nodiscard]] static constexpr bool StartsWithUnsafe(ssize_t lengthSource, const char16_t* source, char16_t prefix) noexcept { return _startsWithUnsafe(lengthSource, source, prefix); }
        [[nodiscard]] static constexpr bool StartsWithUnsafe(ssize_t lengthSource, const char32_t* source, char32_t prefix) noexcept { return _startsWithUnsafe(lengthSource, source, prefix); }

        /// @brief ソース文字列が指定したプレフィックスで始まるかを確認
        /// @param lengthSource ソース文字列の長さ
        /// @param source ソース文字列
        /// @param prefixLength プレフィックスの長さ
        /// @param prefix プレフィックス
        [[nodiscard]] static constexpr bool StartsWithUnsafe(ssize_t lengthSource, const char* source, ssize_t prefixLength, const char* prefix) noexcept { return _startsWithUnsafe(lengthSource, source, prefixLength, prefix); }
        [[nodiscard]] static constexpr bool StartsWithUnsafe(ssize_t lengthSource, const wchar_t* source, ssize_t prefixLength, const wchar_t* prefix) noexcept { return _startsWithUnsafe(lengthSource, source, prefixLength, prefix); }
        [[nodiscard]] static constexpr bool StartsWithUnsafe(ssize_t lengthSource, const char8_t* source, ssize_t prefixLength, const char8_t* prefix) noexcept { return _startsWithUnsafe(lengthSource, source, prefixLength, prefix); }
        [[nodiscard]] static constexpr bool StartsWithUnsafe(ssize_t lengthSource, const char16_t* source, ssize_t prefixLength, const char16_t* prefix) noexcept { return _startsWithUnsafe(lengthSource, source, prefixLength, prefix); }
        [[nodiscard]] static constexpr bool StartsWithUnsafe(ssize_t lengthSource, const char32_t* source, ssize_t prefixLength, const char32_t* prefix) noexcept { return _startsWithUnsafe(lengthSource, source, prefixLength, prefix); }

        /// @brief ふぁ！？っく
        static CharString ToCharStringUnsafe(ssize_t, std::nullptr_t) = delete;

        /// @brief char文字列をCharStringに変換
        /// @param length 文字列の長さ
        /// @param str char文字列
        /// @throws MemoryAllocationException: インスタンスの作成に失敗したとき
        [[nodiscard]]
        static CharString ToCharStringUnsafe(ssize_t length, const char* str);

        /// @brief wchar_t文字列をCharStringに変換
        /// @param length 文字列の長さ
        /// @param str wchar_t文字列
        /// @throws MemoryAllocationException: インスタンスの作成に失敗したとき
        [[nodiscard]]
        static CharString ToCharStringUnsafe(ssize_t length, const wchar_t* str);

        /// @brief char8_t文字列をCharStringに変換
        /// @param length 文字列の長さ
        /// @param str char8_t文字列
        /// @throws MemoryAllocationException: インスタンスの作成に失敗したとき
        [[nodiscard]]
        static CharString ToCharStringUnsafe(ssize_t length, const char8_t* str);

        /// @brief char16_t文字列をCharStringに変換
        /// @param length 文字列の長さ
        /// @param str char16_t文字列
        /// @throws MemoryAllocationException: インスタンスの作成に失敗したとき
        [[nodiscard]]
        static CharString ToCharStringUnsafe(ssize_t length, const char16_t* str);

        /// @brief char32_t文字列をCharStringに変換
        /// @param length 文字列の長さ
        /// @param str char32_t文字列
        /// @throws MemoryAllocationException: インスタンスの作成に失敗したとき
        [[nodiscard]]
        static CharString ToCharStringUnsafe(ssize_t length, const char32_t* str);

        /// @brief ふぁ！？っく
        static String ToStringUnsafe(ssize_t, std::nullptr_t) = delete;

        /// @brief char文字列をStringに変換
        /// @param length 文字列の長さ
        /// @param str char文字列
        /// @throws MemoryAllocationException: インスタンスの作成に失敗したとき
        [[nodiscard]]
        static String ToStringUnsafe(ssize_t length, const char* str);

        /// @brief wchar_t文字列をStringに変換
        /// @param length 文字列の長さ
        /// @param str wchar_t文字列
        /// @throws MemoryAllocationException: インスタンスの作成に失敗したとき
        [[nodiscard]]
        static String ToStringUnsafe(ssize_t length, const wchar_t* str);

        /// @brief char8_t文字列をStringに変換
        /// @param length 文字列の長さ
        /// @param str char8_t文字列
        /// @throws MemoryAllocationException: インスタンスの作成に失敗したとき
        [[nodiscard]]
        static String ToStringUnsafe(ssize_t length, const char8_t* str);

        /// @brief char16_t文字列をStringに変換
        /// @param length 文字列の長さ
        /// @param str char16_t文字列
        /// @throws MemoryAllocationException: インスタンスの作成に失敗したとき
        [[nodiscard]]
        static String ToStringUnsafe(ssize_t length, const char16_t* str);

        /// @brief char32_t文字列をStringに変換
        /// @param length 文字列の長さ
        /// @param str char32_t文字列
        /// @throws MemoryAllocationException: インスタンスの作成に失敗したとき
        [[nodiscard]]
        static String ToStringUnsafe(ssize_t length, const char32_t* str);

        private:

        template <class TC>
        static constexpr bool _containsUnsafe(ssize_t lengthSource, const TC* source, TC target) noexcept
        {
            return _findUnsafe(lengthSource, source, target) != Collections::CollectionHelper::NotFound();
        }

        template <class TC>
        static constexpr bool _containsUnsafe(ssize_t lengthSource, const TC* source, ssize_t lengthTarget, const TC* target) noexcept
        {
            return _findUnsafe(lengthSource, source, lengthTarget, target) != Collections::CollectionHelper::NotFound();
        }

        template <class TC>
        static constexpr bool _endsWithUnsafe(ssize_t lengthSource, const TC* source, TC suffix) noexcept
        {
            return source[lengthSource - 1] == suffix;
        }

        template <class TC>
        static constexpr bool _endsWithUnsafe(ssize_t lengthSource, const TC* source, ssize_t lengthSuffix, const TC* suffix) noexcept
        {
            if (lengthSource < lengthSuffix) return false;

            const TC* p = source + (lengthSource - lengthSuffix);

            for (ssize_t i = 0; i < lengthSuffix; i++) {
                if (p[i] != suffix[i]) return false;
            }

            return true;
        }

        template <class TC>
        static constexpr ssize_t _findUnsafe(ssize_t lengthSource, const TC* source, TC target) noexcept
        {
            const TC* p = source;
            const TC* end = p + lengthSource;

            while (p != end) {
                if (*p == target) return p - source;
                p++;
            }

            return Collections::CollectionHelper::NotFound();
        }

        template <class TC>
        static constexpr ssize_t _findUnsafe(ssize_t lengthSource, const TC* source, ssize_t lengthTarget, const TC* target) noexcept
        {
            const TC* p = source;
            ssize_t i;
            
            while (lengthSource >= lengthTarget) {

                for (ssize_t i = 0; i < lengthTarget; i++) {
                    if (p[i] != target[i]) break;
                }

                if (i == lengthTarget) return p - source;

                lengthSource--;
                p++;
            }

            return Collections::CollectionHelper::NotFound();
        }

        template <class TChar>
        static constexpr ssize_t _getLengthUnsafe(const TChar* str) noexcept
        {
            const TChar* p = str;

            while (*p) ++p;

            return p - str;
        }

        template <class TC>
        static constexpr bool _isNullOrEmpty(const TC* str) noexcept { return str == nullptr || *str == (TC)0; }

        template <class TC>
        static constexpr bool _startsWithUnsafe(ssize_t lengthSource, const TC* source, TC prefix) noexcept
        {
            if (lengthSource == 0) return false;

            return *source == prefix;
        }

        template <class TC>
        static constexpr bool _startsWithUnsafe(ssize_t lengthSource, const TC* source, ssize_t lengthPrefix, const TC* prefix) noexcept
        {
            if (lengthSource < lengthPrefix) return false;

            for (ssize_t i = 0; i < lengthPrefix; ++i) {
                if (source[i] != prefix[i]) return false;
            }
    
            return true;
        }
    };
}

#endif //!KLIB_TEXT_STRINGHELPER_H
