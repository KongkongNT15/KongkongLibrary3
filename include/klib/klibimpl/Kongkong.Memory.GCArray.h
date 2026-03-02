#ifndef KLIB_KONGKONG_MEMORY_GCARRAY_H
#define KLIB_KONGKONG_MEMORY_GCARRAY_H

#include "base.h"
#include "Kongkong.Memory.GCHandleBase.h"

namespace klib::Kongkong::Memory
{
    class GCArray final : public GCHandleBase {
        public:
        

        private:
        ssize_t m_length;
    };
}

#endif //!KLIB_KONGKONG_MEMORY_GCARRAY_H