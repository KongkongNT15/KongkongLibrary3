#ifndef KLIB_KONGKONG_CONTAINERS_PRIMITIVES_PAGEDLISTHELPER_H
#define KLIB_KONGKONG_CONTAINERS_PRIMITIVES_PAGEDLISTHELPER_H

#include "base.h"

namespace klib::Kongkong::Containers::Primitives
{
    class PagedListHelper final {
        private:

        template <class T>
        friend class PagedList;

        [[noreturn]]
        static void do_throwMemoryCommitError();

        [[noreturn]]
        static void do_throwReserveError();

        public:

        KLIB_STATIC_CLASS(PagedListHelper);
    };
}

#endif //!KLIB_KONGKONG_CONTAINERS_PRIMITIVES_PAGEDLISTHELPER_H