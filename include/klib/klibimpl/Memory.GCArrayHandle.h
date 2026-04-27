#ifndef KLIB_MEMORY_GCARRAYHANDLE_H
#define KLIB_MEMORY_GCARRAYHANDLE_H

#include "base.h"
#include "Memory.Primitives.GCHandleBase.h"
#include "Memory.GCArrayObject.h"

namespace klib::Memory
{
    template <class T>
    class GCArrayHandle final : public GCHandleBase {
        public:
        

        private:
        ssize_t m_length;
    };
}

#endif //!KLIB_MEMORY_GCARRAYHANDLE_H
