#ifndef KLIB_CONTAINERS_CHAINEDLIST_H
#define KLIB_CONTAINERS_CHAINEDLIST_H

#include "base.h"
#include "ValueType.h"
#include "Containers.Primitives.ArrayBase.h"
#include "Containers.Primitives.ChainLink.h"

namespace klib::Containers
{
    template <class T>
    class ChainedList : public Primitves::ContainerBase {
        public:
        using ElementType = typename Primitives::ArrayBase<T>::ElementType;
        using IteratorType = typename Primitives::ArrayBase<T>::IteratorType;
        using ConstIteratorType = typename Primitives::ArrayBase<T>::ConstIteratorType;
        
        static constexpr bool IsCopyConstructible = ::std::is_copy_constructible_v<ElementType>;
        static constexpr bool IsMoveConstructible = ::std::is_move_constructible_v<ElementType>;
        static constexpr bool IsNothrowCopyConstructible = ::std::is_nothrow_copy_constructible_v<ElementType>;
        static constexpr bool IsNothrowMoveConstructible = ::std::is_nothrow_move_constructible_v<ElementType>;

        private:
        static inline ssize_t s_maxChainElementCount = -1;

        static void do_initializeMaxChainElementCount() noexcept;
        Primitives::ChainLink<ElementType>* m_begin;

        public:

        
    };

    template <class T>
    void ChainedList<T>::do_initializeMaxChainElementCount() noexcept
    {

    }
}

#endif //!KLIB_CONTAINERS_CHAINEDLIST_H
