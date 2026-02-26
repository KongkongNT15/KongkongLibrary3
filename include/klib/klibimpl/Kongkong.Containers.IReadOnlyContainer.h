#ifndef KLIB_KONGKONG_CONTAINERS_IREADONLYCOLLECTION_H
#define KLIB_KONGKONG_CONTAINERS_IREADONLYCOLLECTION_H

#include "base.h"
#include "Kongkong.Interface.h"

namespace klib::Kongkong::Containers
{
    template <class T>
    class IReadOnlyContainer : Interface<> {
        public:
        using ElementType = ::std::remove_cv_t<T>;
        protected:

        struct s_impl {
            [[nodiscard]]
            virtual ssize_t Length() const = 0;
        };
        

        template <class TValue>
        struct s_impl1 {

        };

        public:
    };
}

#endif //!KLIB_KONGKONG_CONTAINERS_IREADONLYCOLLECTION_H