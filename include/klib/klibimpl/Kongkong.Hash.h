#ifndef KLIB_KONGKONG_HASH_H
#define KLIB_KONGKONG_HASH_H

#include "base.h"

namespace klib::Kongkong
{
    template <>
    struct Hash<void> final {
        public:
        using ResultType = int64_t;

        KLIB_STATIC_CLASS(Hash);
    };
}

#endif //!KLIB_KONGKONG_HASH_H