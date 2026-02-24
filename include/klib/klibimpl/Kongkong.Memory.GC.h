#ifndef KLIB_KONGKONG_MEMORY_GC_H
#define KLIB_KONGKONG_MEMORY_GC_H

#include "base.h"
#include "Kongkong.Memory.GCHandle.h"
#include "Kongkong.Threading.Thread.h"

#include <list>
#include <map>


namespace klib::Kongkong::Memory
{
    class GC final {
    private:

        class s_gc {
        public:

            /// <summary>
            /// 破棄する予定のオブジェクト
            /// </summary>
            ::std::list<GCObjectBase*> m_garbages;
        
        };

        static inline s_gc s_instance;
        static inline bool s_isInitialized;

    public:
        KLIB_STATIC_CLASS(GC);

        static void Collect() noexcept;

        static bool Initialize() noexcept;

        [[nodiscard]]
        static bool IsInitialized() noexcept;
    };
}

namespace klib::Kongkong::Memory
{
    inline bool GC::IsInitialized() noexcept
    {
        return s_isInitialized;
    }
}

#endif //!KLIB_KONGKONG_MEMORY_GC_H