#ifndef KLIB_MEMORY_PRIMITIVES_GCHANDLEBASE_H
#define KLIB_MEMORY_PRIMITIVES_GCHANDLEBASE_H

#include "base.h"
#include "Foundation.HandleType.h"
#include "Memory.Primitives.GCHandleEntry.h"

#include <atomic>

namespace klib::Memory::Primitives
{
    class GCHandleBase : public Foundation::HandleType {
        friend GC;
        template <class T>
        friend class GCHandle;

        private:

        class s_pointer {
        private:
            ::std::atomic<Primitives::GCHandleEntry>* m_pointer;
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
            void* Get() const noexcept;

            void Set(
                void* objectPtr
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

namespace klib::Memory::Primitives
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

        auto entry = m_pointer->load(
            ::std::memory_order::relaxed
        );

        entry.RefCount++;

        m_pointer->exchange(entry);
    }

    inline GCHandleBase::s_pointer::~s_pointer()
    {
        if (m_pointer == nullptr) return;

        auto entry = m_pointer->load(
            ::std::memory_order::relaxed
        );

        entry.RefCount--;

        m_pointer->exchange(entry);
    }

    constexpr GCHandleBase::s_pointer::s_pointer(
        s_pointer&& other
    ) noexcept
        : m_pointer(other.m_pointer)
    {
        other.m_pointer = nullptr;
    }

    constexpr void*
    GCHandleBase::s_pointer::Get() const noexcept
    {
        return m_pointer->load().ObjectPtr;
    }

    constexpr GCHandleBase::GCHandleBase() noexcept
        : m_pointer(nullptr)
    {
    }
}

#endif //!KLIB_MEMORY_PRIMITIVES_GCHANDLEBASE_H
