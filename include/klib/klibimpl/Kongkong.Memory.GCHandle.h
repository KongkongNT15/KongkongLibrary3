#ifndef KLIB_KONGKONG_MEMORY_GCHANDLE_H
#define KLIB_KONGKONG_MEMORY_GCHANDLE_H

#include "base.h"
#include "Kongkong.Memory.GCHandleBase.h"

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
        constexpr Type* operator->() const;

        template <class THandle>
            requires ::std::derived_from<THandle, GCHandleBase>
        THandle As() const noexcept;

        template <class THandle>
            requires ::std::derived_from<THandle, GCHandleBase>
        THandle Cast() const;

        [[nodiscard]]
        constexpr Type* GetRawPointerUnsafe() const noexcept;
    };

}

namespace klib::Kongkong::Memory
{
    template <class T>
    template <class THandle>
        requires ::std::derived_from<THandle, GCHandleBase>
    THandle GCHandle<T>::Cast() const
    {
        using type = typename THandle::Type;

        if constexpr (::std::derived_from<typename Type, type>) {

        }
    }
}

#endif //!KLIB_KONGKONG_MEMORY_GCHANDLE_H