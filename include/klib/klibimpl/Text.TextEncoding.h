#ifndef KLIB_TEXT_TEXTENCODING_H
#define KLIB_TEXT_TEXTENCODING_H

#include "base.h"

namespace klib::Text
{
    class TextEncoding {
        public:

        [[nodiscard]]
        virtual int CodePage() const noexcept = 0;

        [[nodiscard]]
        virtual bool IsSingleByte() const noexcept = 0;
    };
}

#endif //!KLIB_TEXT_TEXTENCODING_H