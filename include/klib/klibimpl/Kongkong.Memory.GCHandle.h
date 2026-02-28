#ifndef KLIB_KONGKONG_MEMORY_GCHANDLE_H
#define KLIB_KONGKONG_MEMORY_GCHANDLE_H

#include "base.h"
#include "Kongkong.Memory.GCHandleBase.h"
#include "Kongkong.Memory.GCObject.h"
#include "Kongkong.Memory.GCPinGuard.h"
#include "Kongkong.NullPointerException.h"

namespace klib::Kongkong::Memory
{
    template <class T>
    class GCHandle final : private GCHandleBase {
        friend GC;

    public:
        using Type = ::std::remove_cvref_t<T>;

    private:

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
        constexpr Type* GetRawPointerUnsafe() const noexcept;

        template <class TPredicate>
        void WithPinned(
            TPredicate pred
        ) const;

    };
    
}

namespace klib::Kongkong::Memory
{
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

        NullPointerException::CheckNull(p);

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
    template <class TPredicate>
    void GCHandle<T>::WithPinned(
        TPredicate pred
    ) const
    {
        GCPinGuard<T> guard = this->operator->();

        auto objectPtr = guard.operator->();

        pred(*objectPtr);
    }
}

#endif //!KLIB_KONGKONG_MEMORY_GCHANDLE_H