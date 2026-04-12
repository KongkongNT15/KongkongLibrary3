#ifndef KLIB_BASE_H
#define KLIB_BASE_H

#define KLIB_VERSION_MAJOR 3
#define KLIB_VERSION_MINOR 0
#define KLIB_VERSION_PATCH 0
#define KLIB_VERSION_BUILD 0

#if __has_include(<Windows.h>)
    #define KLIB_ENV_WINDOWS 1

    #if __cplusplus == 199711L
        #define KLIB_COMPILER_MSVC 1
        #define KLIB_CPP_LANG_VERSION _MSVC_LANG

        // 安全でない関数の使用時に出てくるうっざい警告C4996の抑制
        #define _CRT_SECURE_NO_WARNINGS 1

        #include <vcruntime.h>

        #if defined(_M_ARM64)
            #define KLIB_ENV_ARM64 1
        #elif defined(_M_X64)
            #define KLIB_ENV_X64 1
        #endif
    #else
        #define KLIB_COMPILER_MSVC 0
        #define KLIB_CPP_LANG_VERSION __cplusplus
    #endif

    #if defined(__MINGW32__) || defined(__MINGW64__)
        #define KLIB_COMPILER_MINGW 1
        #if defined(__aarch64__)
            #define KLIB_ENV_ARM64 1
        #elif defined(__x86_64__)
            #define KLIB_ENV_X64 1
        #endif
    #endif

    #include <Windows.h>

    // ふぁ！？っく
    #undef max
    #undef min
#endif

#if __has_include(<unistd.h>) && !defined(KLIB_ENV_WINDOWS)
    #define KLIB_ENV_UNIX 1

    #include <unistd.h>
#endif

#ifdef __APPLE__
    #define KLIB_ENV_APPLE 1

    #ifdef TARGET_OS_MAC
        #define KLIB_COMPILER_APPLE_CLANG 1
        #define KLIB_COMPILER_CLANG 1
    #endif

    #if defined(__aarch64__) || defined(__arm64__)
        #define KLIB_ENV_ARM64 1
    #else
        #define KLIB_ENV_X64 1
    #endif

    #ifdef KLIB_OBJECTIVE_C_DISABLED
        #define KLIB_OBJECTIVE_C_ENABLED 0
    #else
        #define KLIB_OBJECTIVE_C_ENABLED 1
    #endif
#endif

#ifdef __linux__
    #define KLIB_ENV_LINUX 1

    #ifdef __aarch64__
        #define KLIB_ENV_ARM64 1
    #endif

    #ifdef __x86_64__
        #define KLIB_ENV_X64 1
    #endif
#endif

#ifndef KLIB_CPP_LANG_VERSION
    #define KLIB_CPP_LANG_VERSION __cplusplus
#endif

#define KLIB_CPP11 201103L
#define KLIB_CPP14 201402L
#define KLIB_CPP17 201703L
#define KLIB_CPP20 202002L
#define KLIB_CPP23 202302L

#if KLIB_CPP_LANG_VERSION >= KLIB_CPP11
    #define KLIB_HAS_CPP11 1
#else
    #define KLIB_HAS_CPP11 0
#endif

#if KLIB_CPP_LANG_VERSION >= KLIB_CPP14
    #define KLIB_HAS_CPP14 1
#else
    #define KLIB_HAS_CPP14 0
#endif

#if KLIB_CPP_LANG_VERSION >= KLIB_CPP17
    #define KLIB_HAS_CPP17 1
#else
    #define KLIB_HAS_CPP17 0
#endif

#if KLIB_CPP_LANG_VERSION >= KLIB_CPP20
    #define KLIB_HAS_CPP20 1
#else
    #define KLIB_HAS_CPP20 0
#endif

#if KLIB_CPP_LANG_VERSION >= KLIB_CPP23
    #define KLIB_HAS_CPP23 1
#else
    #define KLIB_HAS_CPP23 0
#endif

#ifndef KLIB_ENV_WINDOWS
    #define KLIB_ENV_WINDOWS 0
#endif

#ifndef KLIB_ENV_UNIX
    #define KLIB_ENV_UNIX 0
#endif

#ifndef KLIB_COMPILER_MSVC
    #define KLIB_COMPILER_MSVC 0
#endif

#ifndef KLIB_COMPILER_MINGW
    #define KLIB_COMPILER_MINGW 0
#endif

#ifndef KLIB_COMPILER_APPLE_CLANG
    #define KLIB_COMPILER_APPLE_CLANG 0
#endif

#ifndef KLIB_COMPILER_CLANG
    #define KLIB_COMPILER_CLANG 0
#endif

#ifndef KLIB_ENV_APPLE
    #define KLIB_ENV_APPLE 0
#endif

#ifndef KLIB_OBJECTIVE_C_ENABLED
    #define KLIB_OBJECTIVE_C_ENABLED 0
#endif

#ifndef KLIB_ENV_LINUX
    #define KLIB_ENV_LINUX 0
#endif

#ifndef KLIB_ENV_ARM64
    #define KLIB_ENV_ARM64 0
#endif

#ifndef KLIB_ENV_X64
    #define KLIB_ENV_X64 0
#endif

#if KLIB_ENV_UNIX || KLIB_ENV_WINDOWS
    #define KLIB_ENV_OTHER 0
#else
    #define KLIB_ENV_OTHER 1
#endif

#if KLIB_HAS_CPP23
    #define KLIB_CPP23_CONSTEXPR constexpr
    #define KLIB_CPP23_CONSTEXPR_OR_INLINE constexpr
#else
    #define KLIB_CPP23_CONSTEXPR
    #define KLIB_CPP23_CONSTEXPR_OR_INLINE inline
#endif

// インスタンス化できないようにする
#define KLIB_STATIC_CLASS(className) \
    className() = delete; \
    className(className const&) = delete; \
    className(className&&) = delete; \
    ~className() = delete; \
    className& operator=(className const&) = delete; \
    className& operator=(className&&) = delete

#define KLIB_INTERFACE struct

#define KLIB_NEW new(::std::nothrow)

#define KLIB_KONGKONG_OBJECT_CONSTRUCTER(type, base) \
    constexpr type(::std::nullptr_t) noexcept : base(nullptr) {}

#define KLIB_KONGKONG_OBJECT_OPERATOR_UNSAFE \
    [[nodiscard]] constexpr ImplType* operator->() const noexcept \
    { \
        return static_cast<ImplType*>(Object::GetPointer()); \
    }

#define KLIB_KONGKONG_OBJECT_OPERATOR \
    [[nodiscard]] constexpr ImplType* operator->() const noexcept \
    { \
        auto p = Object::GetPointer(); \
        if (p == nullptr) [[unlikely]] throw NullPointerException(); \
        return static_cast<ImplType*>(p); \
    }

#define KLIB_KONGKONG_OBJECT_OMAJINAI(type, base) \
    KLIB_KONGKONG_OBJECT_CONSTRUCTER(type, base) \
    KLIB_KONGKONG_OBJECT_OPERATOR

#define KLIB_KONGKONG_OBJECT_GETINSTANCE \
    (Object::GetPointerChecked<ImplType>())

#define KLIB_CREATE_ENUM_CREATE_OPERATOR_OR(enumClass) \
    [[nodiscard]] constexpr enumClass operator|(enumClass left, enumClass right) noexcept { return enumClass((::std::underlying_type_t<enumClass>)left | (::std::underlying_type_t<enumClass>)right); } \
    constexpr enumClass& operator|=(enumClass& left, enumClass right) noexcept { return left = enumClass((::std::underlying_type_t<enumClass>)left | (::std::underlying_type_t<enumClass>)right); }

#define KLIB_CREATE_ENUM_CREATE_OPERATOR_AND(enumClass) \
    [[nodiscard]] constexpr bool operator&(enumClass left, enumClass right) noexcept { return (bool)((::std::underlying_type_t<enumClass>)left & (::std::underlying_type_t<enumClass>)right); }

#define KLIB_CREATE_ENUM_CREATE_OPERATOR_PP(enumClass) \
    [[nodiscard]] constexpr enumClass& operator++(enumClass& value) noexcept \
    { \
        return value = (enumClass)((::std::underlying_type_v<enumClass>)value + 1); \
    } \
    [[nodiscard]] constexpr enumClass operator++(enumClass& value, int) noexcept \
    { \
        enumClass ret = value; \
        value = (enumClass)((::std::underlying_type_t<enumClass>)value + 1); \
        return ret; \
    }

#define KLIB_CREATE_ENUM_CREATE_OPERATOR_MM(enumClass) \
    [[nodiscard]] constexpr enumClass& operator--(enumClass& value) noexcept \
    { \
        return value = (enumClass)((::std::underlying_type_t<enumClass>)value - 1); \
    } \
    [[nodiscard]] constexpr enumClass operator--(enumClass& value, int) noexcept \
    { \
        enumClass ret = value; \
        value = (enumClass)((::std::underlying_type_t<enumClass>)value - 1); \
        return ret; \
    }

#define KLIB_CREATE_ENUM_CREATE_OPERATOR_AND_OR(enumClass) \
    KLIB_CREATE_ENUM_CREATE_OPERATOR_OR(enumClass) \
    KLIB_CREATE_ENUM_CREATE_OPERATOR_AND(enumClass)

#define KLIB_CREATE_ENUM_CREATE_OPERATOR_PP_MM(enumClass, base) \
    KLIB_CREATE_ENUM_CREATE_OPERATOR_PP(enumClass, base) \
    KLIB_CREATE_ENUM_CREATE_OPERATOR_MM(enumClass, base)

#include <stdint.h>
#include <compare>
#include <concepts>
#include <type_traits>
#include <utility>

// msvcではssize_tは定義されないので追加
#if KLIB_COMPILER_MSVC
    #ifdef _WIN64
        /// <summary>
        /// ポインターと同じ長さの整数型
        /// </summary>
        using ssize_t = int64_t;
    #else
        /// <summary>
        /// ポインターと同じ長さの整数型
        /// </summary>
        using ssize_t = int32_t;
    #endif
#endif

/// <summary>
/// 既定の名前空間
/// </summary>
namespace klib
{
    using byte = unsigned char;
    using sbyte = signed char;
}

/// <summary>
/// 基本クラスたち
/// </summary>
namespace klib::Kongkong
{
    struct KLibType;
    struct ValueType;
    struct NonType;

    struct ArgumentException;
    struct ArgumentOutOfRangeException;

    template <class TEnum = void> requires ::std::is_enum_v<TEnum>
    struct Enum;

    struct Exception;
    enum struct ErrorCode;
    class Initializer;
    struct InvalidOperationException;
    struct MemoryAllocationException;
    struct MemoryException;
    struct NotSupportedException;

    struct NullPointerException;
    
    struct OutOfMemoryException;

    struct Hash;

    template <class TStruct, class... TOtherStructs>
    struct InterfaceValue;

    template <class... TStructs>
    class Interface;

    template <class T>
    struct LazyObject;

    template <class T>
    struct UnsafeLazyObject;
}

namespace klib::Kongkong::AppleDevice
{
    class ObjCHandle;
}

namespace klib::Kongkong::Bits
{
    template <ssize_t N> requires (N >= 1)
    struct Bitset;

    class BitsetElement;
    class BitsetHelper;
    class BitsetConstIterator;
    class BitsetIterator;
}

/// <summary>
/// コンテナ型
/// </summary>
namespace klib::Kongkong::Containers
{
    template <class T, ssize_t N> requires (N >= 1)
    struct BuiltInArray;

    class ContainerHelper;

    template <class T>
    class IReadOnlyContainer;

    template <class T>
    class IIterator;

    template <class T>
    class PagedList;
}

namespace klib::Kongkong::Containers::Primitives
{
    template <class T>
    struct ArrayBase;

    struct ContainerBase;

    class PagedListHelper;
}

namespace klib::Kongkong::Functional
{
    template <class TResult, class... TArgs>
    struct FunctionBase;

    template <class TResult, class... TArgs>
    struct FunctionPointer;

    template <class TPointerType, class TResult, class... TArgs>
    struct MemberFunction;

    template <class TResult, class... TArgs>
    struct RawFunction;

    template <class TFunc, class TResult, class... TArgs>
    requires ::std::is_invocable_v<TFunc, TArgs&&...>
    struct FunctionObject;

    template <class TResult, class... TArgs>
    class Function;
}

namespace klib::Kongkong::IO
{
    enum struct FileCreateMode;
    enum struct FileShareMode;
    class HandleStream;
    struct IOException;
    class MemoryStream;
    class Stream;
}

namespace klib::Kongkong::Memory
{
    class GC;

    template <class T>
    class GCArrayHandle;

    template <class T>
    class GCHandle;

    class GCHandleBase;

    template <class T>
    struct GCArrayObject;
    
    template <class T>
    struct GCPinGuard;

    class MemoryAddress;

    class MemoryResource;
    class VirtualMemoryRegion;
    

    template <class T>
    class SharedPointer;

    class SharedPointerBase;
}

namespace klib::Kongkong::Memory::Primitives
{
    struct GCHandleEntry;
    struct GCHandleTable;
    enum struct GCObjectFlag : int16_t;

    template <class T = void>
    struct GCObjectHeader;

    template <class T = void>
    struct GCObject;

    class GCObjectList;
}

namespace klib::Kongkong::Numerics
{
    template <class T>
    concept CNumber = (
        (::std::integral<T> || ::std::floating_point<T>)
        && (::std::same_as<T, bool> == false)
    );

    template <class TNum = void>
    struct Number;

    template <class TNum> requires CNumber<TNum>
    struct NumberParseResult;

    template <CNumber TNum = float>
    struct Vector2;

    template <CNumber TNum = float>
    struct Vector3;
}

namespace klib::Kongkong::Ranges
{
    struct Index;
    struct IndexFromEnd;
    class IteratorHelper;
    struct Range;

    
}

namespace klib::Kongkong::Std
{
    template <class T>
    struct Allocator;

    template <class T, class TAllocator = Allocator<T>>
    struct StlVector;
}

/// <summary>
/// 文字列関連
/// </summary>
namespace klib::Kongkong::Text
{
    template <class T>
    concept CChar =
        ::std::same_as<T, char> ||
        ::std::same_as<T, wchar_t> ||
        ::std::same_as<T, char8_t> ||
        ::std::same_as<T, char16_t> ||
        ::std::same_as<T, char32_t>;


    template <CChar TChar>
    struct GenericFastString;

    template <CChar TChar>
    class GenericFastStringBase;

    template <CChar TChar, ssize_t N>
    struct GenericStaticFastString;

    template <CChar TChar, ssize_t N>
    struct GenericStaticMutableString;

    template <CChar TChar>
    class GenericStaticString;

    template <CChar TChar>
    class GenericString;

    template <CChar TChar>
    class GenericHeapString;

    template <CChar TChar>
    struct GenericStringMemory;

    template <CChar TChar>
    struct GenericStringView;
}

namespace klib::Kongkong::Text::Unicode
{
    struct SurrogatePair;
    class UnicodeTraits;
}

namespace klib::Kongkong::Threading
{
    class Mutex;
    enum struct MutexType;
    class ScopedLock;
    class Thread;
    class ThreadPool;
    struct ThreadExitCode;
    struct ThreadStateException;
    
}

namespace klib::Kongkong::Threading::Async
{
    struct AwaiterBase;
    struct AwaiterBasePromise;
    enum struct TaskStatus;

    template <class T>
    struct AsyncOperation;

    template <class T>
    struct AsyncOperationPromise;

    template <class TPromise>
    struct AsyncOperationBase;
}

namespace klib::Kongkong::Win32
{
    class Win32Handle;
}

namespace klib::Kongkong::Win32::UI
{
    class Button;
    class Window;
    class WindowHandle;
}

namespace klib::Kongkong::Numerics
{
    using NativeChar = Number<char>;
    using Short = Number<short>;
    using Int = Number<int>;
    using Long = Number<long>;
    using LLong = Number<long long>;
    using SNativeChar = Number<signed char>;
    using UNativeChar = Number<unsigned char>;
    using UShort = Number<unsigned short>;
    using UInt = Number<unsigned>;
    using ULong = Number<unsigned long>;
    using ULLong = Number<unsigned long long>;
    using WChar = Number<wchar_t>;
    using Char8 = Number<char8_t>;
    using Char = Number<char16_t>;
    using Char32 = Number<char32_t>;
    using Int8 = Number<int8_t>;
    using Int16 = Number<int16_t>;
    using Int32 = Number<int32_t>;
    using Int64 = Number<int64_t>;
    using UInt8 = Number<uint8_t>;
    using UInt16 = Number<uint16_t>;
    using UInt32 = Number<uint32_t>;
    using UInt64 = Number<uint64_t>;
    using Single = Number<float>;
    using Double = Number<double>;
    using LDouble = Number<long double>;
    using Int32ParseResult = NumberParseResult<int32_t>;
}

namespace klib::Kongkong::Text
{
    using Numerics::Char;
}

namespace klib::Kongkong::Threading::Async
{
    using AsyncAction = AsyncOperation<void>;
    using AsyncActionPromise = AsyncOperationPromise<void>;
}


// ユーザー定義リテラル
namespace klib
{
    inline namespace Literals
    {
        [[nodiscard]]
        consteval Kongkong::Ranges::IndexFromEnd
        operator""_end(
            unsigned long long n
        );
    }
}

// 
namespace klib::Kongkong
{
    struct KLibType {

    };

    class Hash final {
        public:

        KLIB_STATIC_CLASS(Hash);

        using ResultType = ssize_t;

        template <class T>
        static constexpr ResultType Get(
            T const& value
        ) noexcept;
    };

    template <class T>
    concept CHashable = requires (T v) {
        { v.GetHashCode() } -> ::std::convertible_to<Hash::ResultType>;
    };
}

namespace klib::Kongkong
{
    template <class T>
    constexpr Hash::ResultType Hash::Get(
        T const& value
    ) noexcept
    {
        if constexpr (CHashable<T>) {
            return value.GetHashCode();
        }
        else {
            return static_cast<ResultType>(
                ::std::hash<T>().operator()(value)
            );
        }
    }
}

#endif //!KLIB_BASE_H