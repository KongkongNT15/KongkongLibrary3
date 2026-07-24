#ifndef KLIB_TEXT_GENERICSTRINGBUFFER_H
#define KLIB_TEXT_GENERICSTRINGBUFFER_H

#include "base.h"

#include <atomic>

namespace klib::Text
{
    template <CChar TChar>
    class GenericStringBuffer {
        public:

        using ElementType = TChar;
        using SizeType = ssize_t;

        private:

        ::std::atomic<SizeType>* m_pRefCount;
        ElementType* m_p;

        public:


    };
}

#endif //!KLIB_TEXT_GENERICSTRINGBUFFER_H