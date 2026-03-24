#ifndef KLIB_KONGKONG_MEMORY_GCARRAYHANDLE_H
#define KLIB_KONGKONG_MEMORY_GCARRAYHANDLE_H

#include "base.h"
#include "Kongkong.Memory.Primitives.GCHandleBase.h"
#include "Kongkong.Memory.GCArrayObject.h"

namespace klib::Kongkong::Memory
{
    template <class T>
    class GCArrayHandle final : public GCHandleBase {
        public:
        

        private:
        ssize_t m_length;
    };
}

#endif //!KLIB_KONGKONG_MEMORY_GCARRAYHANDLE_H