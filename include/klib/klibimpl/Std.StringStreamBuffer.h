#ifndef KLIB_STD_STRINGSTREAMBUFFER_H
#define KLIB_STD_STRINGSTREAMBUFFER_H

#include "base.h"
#include "Containers.PageCache.h"

#include <streambuf>

namespace klib::Std
{
    template <Text::CChar TChar>
    class StringStreamBuffer final : public ::std::basic_streambuf<TChar> {
        private:

        Containers::PageCache m_cache;

        protected:



        public:
    };
}

#endif //!KLIB_STD_STRINGSTREAMBUFFER_H