#ifndef KLIB_TEXT_GENERICSTRING_H
#define KLIB_TEXT_GENERICSTRING_H

#include "base.h"
#include "Memory.GCArrayHandle.h"

namespace klib::Text
{
    template <CChar TChar>
    class GenericString {
        public:

        using ElementType = TChar;

        private:
        Memory::GCArrayHandle<ElementType> m_array;

        public:

        
    };
}

#endif //!KLIB_TEXT_GENERICSTRING_H
