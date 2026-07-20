#ifndef KLIB_STDFUNCTIONS_H
#define KLIB_STDFUNCTIONS_H

#include "base.h"

namespace std
{
    ostream& operator<<(
        ostream& out,
        klib::Text::CharStringView view
    );

    ostream& operator<<(
        ostream& out,
        klib::Text::CharString const& view
    );
}

#endif //!KLIB_STDFUNCTIONS_H