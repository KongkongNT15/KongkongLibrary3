#ifndef KLIB_KONGKONG_UNSAFELAZYOBJECT_H
#define KLIB_KONGKONG_UNSAFELAZYOBJECT_H

#include "base.h"

namespace klib::Kongkong
{
    template <class T>
    struct UnsafeLazyObject final {
    public:
        using Type = ::std::remove_cvref<T>;
        
    private:
        static constexpr ssize_t s_size = sizeof(Type);
        uint8_t m_placeHolder[s_size];

        UnsafeLazyObject(
            UnsafeLazyObject&&
        ) = default;

        UnsafeLazyObject& operator=(
            UnsafeLazyObject&&
        ) = default;

    public:

        template <class... Args>
        [[nodiscard]] static UnsafeLazyObject Make(
            Args&&... args
        ) noexcept(noexcept(Type(::std::forward<Args>(args)...)));

        UnsafeLazyObject() = default;

        UnsafeLazyObject(
            UnsafeLazyObject const&
        ) = delete;

        UnsafeLazyObject& operator=(
            UnsafeLazyObject const&
        ) = delete;

        /// <summary>
        /// 値のデストラクターを呼ぶ
        /// </summary>
        void DisposeUnsafe() noexcept;

        template <class... Args>
        void EmplaceUnsafe(
            Args&&... args
        ) noexcept(noexcept(Type(::std::forward<Args>(args)...)));

        [[nodiscard]]
        Type& GetValueUnsafe() noexcept;

        [[nodiscard]]
        Type const& GetValueUnsafe() const noexcept;
    };
}

namespace klib::Kongkong
{
    template <class T>
    template <class... Args>
    UnsafeLazyObject<T> UnsafeLazyObject<T>::Make(
        Args&&... args
    ) noexcept(noexcept(Type(::std::forward<Args>(args)...)))
    {
        UnsafeLazyObject<T> v;

        EmplaceUnsafe(
            ::std::forward<Args>(args)...
        );

        return v;
    }

    template <class T>
    void UnsafeLazyObject<T>::DisposeUnsafe() noexcept
    {
        GetValueUnsafe().~Type();
    }

    template <class T>
    template <class... Args>
    void UnsafeLazyObject<T>::EmplaceUnsafe(
        Args&&... args
    ) noexcept(noexcept(Type(::std::forward<Args>(args)...)))
    {
        Type& unsafeValue = GetValueUnsafe();

        new(&unsafeValue) Type(::std::forward<Args>(args)...);
    }

    template <class T>
    typename UnsafeLazyObject<T>::Type&
    UnsafeLazyObject<T>::GetValueUnsafe() noexcept
    {
        void* tmp = m_placeHolder;

        return *reinterpret_cast<Type*>(tmp);
    }

    template <class T>
    typename UnsafeLazyObject<T>::Type const&
        UnsafeLazyObject<T>::GetValueUnsafe() const noexcept
    {
        const void* tmp = m_placeHolder;

        return *reinterpret_cast<const Type*>(tmp);
    }
}

#endif //!KLIB_KONGKONG_UNSAFELAZYOBJECT_H