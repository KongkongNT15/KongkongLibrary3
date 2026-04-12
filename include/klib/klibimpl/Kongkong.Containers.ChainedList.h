#ifndef KLIB_KONGKONG_CONTAINERS_CHAINEDLIST_H
#define KLIB_KONGKONG_CONTAINERS_CHAINEDLIST_H

#include "base.h"
#include "Kongkong.Containers.Primitives.ArrayBase.h"

namespace klib::Kongkong::Containers
{
    template <class T>
    class ChainedList : public Primitives::ArrayBase<T> {
        public:
        using ElementType = typename Primitives::ArrayBase<T>::ElementType;
        using IteratorType = typename Primitives::ArrayBase<T>::IteratorType;
        using ConstIteratorType = typename Primitives::ArrayBase<T>::ConstIteratorType;
        
        static constexpr bool IsCopyConstructible = ::std::is_copy_constructible_v<ElementType>;
        static constexpr bool IsMoveConstructible = ::std::is_move_constructible_v<ElementType>;
        static constexpr bool IsNothrowCopyConstructible = ::std::is_nothrow_copy_constructible_v<ElementType>;
        static constexpr bool IsNothrowMoveConstructible = ::std::is_nothrow_move_constructible_v<ElementType>;

        private:
    };
}

#endif //!KLIB_KONGKONG_CONTAINERS_CHAINEDLIST_H