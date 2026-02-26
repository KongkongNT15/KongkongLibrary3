#ifndef KLIB_KONGKONG_STD_ALLOCATOR_H
#define KLIB_KONGKONG_STD_ALLOCATOR_H

#include "base.h"
#include "Kongkong.Memory.GC.h"

namespace klib::Kongkong::Std
{
    template <class T>
    struct Allocator {
        public:
        using difference_type = ptrdiff_t;
        using is_always_equal = ::std::true_type;
        using propagate_on_container_move_assignment = ::std::true_type;
        using size_type = size_t;
        using value_type = typename T;

        [[nodiscard]]
        value_type* allocate(
            size_type n
        ) noexcept;

        void deallocate(
            value_type* ptr,
            size_type
        ) noexcept;
    };

    template <class T>
    [[nodiscard]] constexpr bool operator==(
        Allocator<T> const&,
        Allocator<T> const&
    ) noexcept;

    template <class T>
    [[nodiscard]] constexpr bool operator!=(
        Allocator<T> const&,
        Allocator<T> const&
    ) noexcept;
}

namespace klib::Kongkong::Std
{
    template <class T>
    typename Allocator<T>::value_type* Allocator<T>::allocate(
        size_type n
    ) noexcept
    {
        return static_cast<value_type*>(
            Memory::GC::Alloc(
                n * sizeof(value_type)
            )
        );
    }

    template <class T>
    void Allocator<T>::deallocate(
        value_type* ptr,
        size_type
    ) noexcept
    {
        Memory::GC::Release(ptr);
    }

    template <class T>
    constexpr bool operator==(
        Allocator<T> const&,
        Allocator<T> const&
    ) noexcept
    {
        return true;
    }

    template <class T>
    constexpr bool operator!=(
        Allocator<T> const&,
        Allocator<T> const&
    ) noexcept
    {
        return false;
    }
}

#endif //!KLIB_KONGKONG_STD_ALLOCATOR_H