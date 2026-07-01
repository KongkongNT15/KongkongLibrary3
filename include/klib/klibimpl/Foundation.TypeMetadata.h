#ifndef KLIB_FOUNDATION_TYPEMETADATA_H
#define KLIB_FOUNDATION_TYPEMETADATA_H

#include "base.h"

namespace klib::Foundation
{
    struct TypeMetadata {
        private:



        public:

        template <class T>
        const TypeMetadata* Typeof() noexcept;
    };
}

#define typeof(Typename) ::klib::Foundation::TypeMetadata::Typeof<Typename>()

#endif //!KLIB_FOUNDATION_TYPEMETADATA_H