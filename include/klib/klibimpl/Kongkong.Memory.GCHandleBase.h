#ifndef KLIB_KONGKONG_MEMORY_GCHANDLEBASE_H
#define KLIB_KONGKONG_MEMORY_GCHANDLEBASE_H

#include "base.h"
#include "Kongkong.Memory.GCObjectBase.h"

namespace klib::Kongkong::Memory
{
    class GCHandleBase {
        friend GC;
        template <class T>
        friend class GCHandle;

        private:

        class s_pointer {
        private:
            GCObjectBase* m_pointer;
        public:
            

            constexpr s_pointer(
                ::std::nullptr_t
            ) noexcept;

            s_pointer(
                s_pointer const& other
            ) noexcept;
            
            constexpr s_pointer(
                s_pointer&& other
            ) noexcept;

            ~s_pointer();

            [[nodiscard]]
            GCObjectBase* Get() const noexcept;

            void Set(
                GCObjectBase* objectPtr
            );
        };

        s_pointer m_pointer;

        constexpr GCHandleBase() noexcept;

        GCHandleBase(
            GCHandleBase const&
        ) = default;

        GCHandleBase(
            GCHandleBase&&
        ) = default;

        GCHandleBase& operator=(
            GCHandleBase const&
        ) = default;

        GCHandleBase& operator=(
            GCHandleBase&&
        ) = default;
    public:
    };
}

namespace klib::Kongkong::Memory
{
    constexpr GCHandleBase::s_pointer::s_pointer(
        ::std::nullptr_t
    ) noexcept
        : m_pointer(nullptr)
    {
    }

    inline GCHandleBase::s_pointer::s_pointer(
        s_pointer const& other
    ) noexcept
        : m_pointer(other.m_pointer)
    {
        if (m_pointer == nullptr) return;

        m_pointer->AddReferenceCount();
    }

    constexpr GCHandleBase::s_pointer::s_pointer(
        s_pointer&& other
    ) noexcept
        : m_pointer(other.m_pointer)
    {
        other.m_pointer = nullptr;
    }

    GCObjectBase*
    GCHandleBase::s_pointer::Get() const noexcept
    {
        return m_pointer;
    }

    constexpr GCHandleBase::GCHandleBase() noexcept
        : m_pointer(nullptr)
    {
    }
}

#endif //!KLIB_KONGKONG_MEMORY_GCHANDLEBASE_H