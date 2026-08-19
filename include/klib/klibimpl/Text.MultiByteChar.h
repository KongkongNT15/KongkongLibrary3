#ifndef KLIB_TEXT_MULTIBYTECHAR_H
#define KLIB_TEXT_MULTIBYTECHAR_H

#include "base.h"
#include "Foundation.ValueType.h"

#include <stdlib.h>
#include <string.h>

namespace klib::Text
{
    struct MultiByteChar : public ValueType {
        private:

        char m_mbc[MB_LEN_MAX];

        public:

        consteval MultiByteChar() noexcept;

        void WriteTo(
            ::std::ostream& out
        ) const noexcept;
    };
}

namespace klib::Text
{
    consteval MultiByteChar::MultiByteChar(
    ) noexcept
        : m_mbc{}
    {
    }
}

#endif //!KLIB_TEXT_MULTIBYTECHAR_H