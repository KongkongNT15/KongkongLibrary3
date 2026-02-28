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
        
            ssize_t m_memorySize;
        };

        static inline s_gc s_instance;
        static inline bool s_isInitialized;

    public:
        KLIB_STATIC_CLASS(GC);

        /// @brief 
        /// @param size 
        /// @return 失敗するとnullptr
        static void* Alloc(
            size_t size
        ) noexcept;

        static void Collect() noexcept;

        static ssize_t GetAllocationSize(
            void* ptr
        ) noexcept;

        static bool Initialize() noexcept;

        [[nodiscard]]
        static bool IsInitialized() noexcept;

        static void Release(
            void* ptr
        ) noexcept;
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