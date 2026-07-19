#ifndef KLIB_TEXT_GENERICSTRINGVIEW_H
#define KLIB_TEXT_GENERICSTRINGVIEW_H

#include "base.h"

namespace klib::Text
{
    template <CChar TChar>
    struct GenericStringView {
        private:

        public:

        constexpr GenericStringView(
            GenericString<TChar> const& str
        ) noexcept;
    };
}

#endif //!KLIB_TEXT_GENERICSTRINGVIEW_H