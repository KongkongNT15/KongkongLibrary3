#ifndef KLIB_CONTAINERS_IREADONLYCOLLECTION_H
#define KLIB_CONTAINERS_IREADONLYCOLLECTION_H

#include "base.h"
#include "Foundation.Interface.h"

namespace klib::Containers
{
    template <class T>
    class IReadOnlyContainer : Foundation::Interface<> {
        public:
        using ElementType = ::std::remove_cvref_t<T>;
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

#endif //!KLIB_CONTAINERS_IREADONLYCOLLECTION_H
