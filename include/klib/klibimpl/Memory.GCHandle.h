#ifndef KLIB_MEMORY_GCHANDLE_H
#define KLIB_MEMORY_GCHANDLE_H

#include "base.h"
#include "Memory.Primitives.GCHandleBase.h"
#include "Memory.GCPinGuard.h"
#include "Foundation.NullPointerException.h"

namespace klib::Memory
{
    template <class T>
    class GCHandle final : private GCHandleBase {
        friend GC;

    public:
        using Type = ::std::remove_cvref_t<T>;

    private:

#if KLIB_ENABLE_GC

#else
        [[nodiscard]]
        constexpr Primitives::HeapObject<Type>* DoGetObject() const noexcept;

#endif

    public:

        constexpr GCHandle(
            ::std::nullptr_t
        ) noexcept;

        template <class... Args>
        GChandle(
            Args&&... args
        );

        [[nodiscard]]
        GCPinGuard<T> operator->() const;

        template <class THandle>
            requires ::std::derived_from<THandle, GCHandleBase>
        THandle As() const noexcept;

        template <class THandle>
            requires ::std::derived_from<THandle, GCHandleBase>
        THandle Cast() const;

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;

        [[nodiscard]]
        constexpr Type* GetUnsafe() const noexcept;

        template <class TPredicate>
        void WithPinned(
            TPredicate pred
        ) const;

    };
    
}

namespace klib::Memory
{
#if KLIB_ENABLE_GC

    template <class T>
    constexpr GCHandle<T>::GCHandle(
        ::std::nullptr_t
    ) noexcept
    {
    }

    template <class T>
    GCPinGuard<T> GCHandle<T>::operator->() const
    {
        auto p = static_cast<Type*>(
            this->m_pointer.Get()
        );

        Foundation::NullPointerException::CheckNull(p);

        return { p };
    }

    template <class T>
    template <class THandle>
        requires ::std::derived_from<THandle, GCHandleBase>
    THandle GCHandle<T>::Cast() const
    {
        using type = typename THandle::Type;

        if constexpr (::std::derived_from<typename Type, type>) {

        }
    }

    template <class T>
    constexpr Hash::ResultType
    GCHandle<T>::GetHashCode() const noexcept
    {
        if (this->m_pointer.m_pointer == nullptr) return 0;
        GCPinGuard<T> guard = this->operator->();

        return Hash::Get<Type>(*GetRawPointerUnsafe());
    }

    template <class T>
    constexpr GCHandle<T>::Type*
    GCHandle<T>::GetUnsafe() const noexcept
    {

    }

    template <class T>
    template <class TPredicate>
    void GCHandle<T>::WithPinned(
        TPredicate pred
    ) const
    {
        GCPinGuard<T> guard = this->operator->();

        auto objectPtr = guard.operator->();

        pred(*objectPtr);
    }
#else
        template <class T>
    constexpr Primitives::HeapObject<typename GCHandle<T>::Type>*
    GCHandle<T>::DoGetObject() const noexcept
    {
        return static_cast<Primitives::HeapObject<Type>*>(this->m_pointer.ObjectBase());
    }

    template <class T>
    constexpr GCHandle<T>::GCHandle(
        ::std::nullptr_t
    ) noexcept
    {
    }

    template <class T>
    GCPinGuard<T> GCHandle<T>::operator->() const
    {
        auto p = static_cast<Type*>(
            this->m_pointer.Get()
        );

        Foundation::NullPointerException::CheckNull(p);

        return { p };
    }

    template <class T>
    template <class THandle>
        requires ::std::derived_from<THandle, GCHandleBase>
    THandle GCHandle<T>::Cast() const
    {
        using type = typename THandle::Type;

        if constexpr (::std::derived_from<typename Type, type>) {

        }
    }

    template <class T>
    constexpr Hash::ResultType
    GCHandle<T>::GetHashCode() const noexcept
    {
        if (this->m_pointer.m_pointer == nullptr) return 0;

        return Hash::Get<Type>(*GetUnsafe());
    }

    template <class T>
    constexpr GCHandle<T>::Type*
    GCHandle<T>::GetUnsafe() const noexcept
    {
        return &DoGetObject()->Value;
    }

    template <class T>
    template <class TPredicate>
    void GCHandle<T>::WithPinned(
        TPredicate pred
    ) const
    {
        auto p = GetUnsafe();

        if (p == nullptr) [[unlikely]] return;

        pred(*p);
    }

#endif
    
}

#endif //!KLIB_MEMORY_GCHANDLE_H
