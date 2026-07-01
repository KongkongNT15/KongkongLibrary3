#ifndef KLIB_MEMORY_PRIMITIVES_GCHANDLEBASE_H
#define KLIB_MEMORY_PRIMITIVES_GCHANDLEBASE_H

#include "base.h"
#include "Foundation.HandleType.h"
#include "Memory.Primitives.GCHandleEntry.h"
#include "Memory.Primitives.HeapObjectBase.h"

#include <atomic>

namespace klib::Memory::Primitives
{
    class GCHandleBase : public Foundation::HandleType {
        friend GC;
        template <class T>
        friend class GCHandle;

        private:

        class s_pointer {
            public:
#if KLIB_ENABLE_GC
            ::std::atomic<Primitives::GCHandleEntry>* m_pointer;
#else 
            Primitives::HeapObjectBase* m_pointer;
#endif
            

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

#if KLIB_ENABLE_GC

#else 
            [[nodiscard]]
            constexpr Primitives::HeapObjectBase* ObjectBase() const noexcept;
#endif
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
#if KLIB_ENABLE_GC
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
#else
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

        m_pointer->AddRefCount();
    }

    inline GCHandleBase::s_pointer::~s_pointer()
    {
        if (m_pointer == nullptr) return;

        if (m_pointer->RemoveRefCount() == 0) {
            m_pointer->Dispose();
            delete m_pointer;
        }
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
        return m_pointer->Get();
    }

    constexpr GCHandleBase::GCHandleBase() noexcept
        : m_pointer(nullptr)
    {
    }

    constexpr Primitives::HeapObjectBase*
    GCHandleBase::s_pointer::ObjectBase() const noexcept
    {
        return m_pointer;
    }
#endif
}

#endif //!KLIB_MEMORY_PRIMITIVES_GCHANDLEBASE_H
