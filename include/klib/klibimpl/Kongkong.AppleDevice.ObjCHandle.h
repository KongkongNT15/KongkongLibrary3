#ifndef KLIB_KONGKONG_APPLEDEVICE_OBJCHANDLE_H
#define KLIB_KONGKONG_APPLEDEVICE_OBJCHANDLE_H

#include "base.h"

#if KLIB_ENV_APPLE

namespace klib::Kongkong::AppleDevice
{
    class ObjCHandle final {
        private:

        void* m_objectPtr;

        void do_release() noexcept;
        void do_retain() noexcept;

        public:

        constexpr ObjCHandle(
            ::std::nullptr_t
        ) noexcept;

        constexpr ObjCHandle(
            void* objectPtr
        ) noexcept;

        ObjCHandle(
            ObjCHandle const& other
        ) noexcept;

        constexpr ObjCHandle(
            ObjCHandle&& other
        ) noexcept;

        ~ObjCHandle();

        ObjCHandle& operator=(
            ::std::nullptr_t
        ) noexcept;

        ObjCHandle& operator=(
            ObjCHandle const& other
        ) noexcept;

        ObjCHandle& operator=(
            ObjCHandle&& other
        ) noexcept;

        [[nodiscard]]
        constexpr operator bool() const noexcept;

        [[nodiscard]]
        constexpr bool operator!() const noexcept;

        [[nodiscard]]
        constexpr void* GetRawPointer() const noexcept;
    };

    [[nodiscard]]
    bool operator==(
        ObjCHandle const& left,
        ObjCHandle const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        ObjCHandle const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        ::std::nullptr_t,
        ObjCHandle const& right
    ) noexcept;

    [[nodiscard]]
    bool operator!=(
        ObjCHandle const& left,
        ObjCHandle const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        ObjCHandle const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        ::std::nullptr_t,
        ObjCHandle const& right
    ) noexcept;
}

namespace klib::Kongkong::AppleDevice
{
    constexpr ObjCHandle::ObjCHandle(
        ::std::nullptr_t
    ) noexcept
        : m_objectPtr(nullptr)
    {
    }

    constexpr ObjCHandle::ObjCHandle(
        void* objectPtr
    ) noexcept
        : m_objectPtr(objectPtr)
    {
    }

    inline ObjCHandle::ObjCHandle(
        ObjCHandle const& other
    ) noexcept
        : m_objectPtr(other.m_objectPtr)
    {
        do_retain();
    }

    constexpr ObjCHandle::ObjCHandle(
        ObjCHandle&& other
    ) noexcept
        : m_objectPtr(other.m_objectPtr)
    {
        other.m_objectPtr = nullptr;
    }

    inline ObjCHandle::~ObjCHandle()
    {
        do_release();
    }

    inline ObjCHandle& ObjCHandle::operator=(
        ::std::nullptr_t
    ) noexcept
    {
        do_release();

        m_objectPtr = nullptr;

        return *this;
    }

    inline ObjCHandle& ObjCHandle::operator=(
        ObjCHandle const& other
    ) noexcept
    {
        if (&other != this) [[likely]] {
            do_release();

            m_objectPtr = other.m_objectPtr;

            do_retain();
        }

        return *this;
    }

    inline ObjCHandle& ObjCHandle::operator=(
        ObjCHandle&& other
    ) noexcept
    {
        if (&other != this) [[likely]] {
            do_release();

            m_objectPtr = other.m_objectPtr;

            other.m_objectPtr = nullptr;
        }

        return *this;
    }

    constexpr ObjCHandle::operator bool() const noexcept
    {
        return m_objectPtr != nullptr;
    }

    constexpr bool ObjCHandle::operator!() const noexcept
    {
        return m_objectPtr == nullptr;
    }

    constexpr void* ObjCHandle::GetRawPointer() const noexcept
    {
        return m_objectPtr;
    }

    constexpr bool operator==(
        ObjCHandle const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return left.GetRawPointer() == nullptr;
    }

    constexpr bool operator==(
        ::std::nullptr_t,
        ObjCHandle const& right
    ) noexcept
    {
        nullptr == right.GetRawPointer();
    }

    inline bool operator!=(
        ObjCHandle const& left,
        ObjCHandle const& right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator!=(
        ObjCHandle const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return left.GetRawPointer() != nullptr;
    }

    constexpr bool operator!=(
        ::std::nullptr_t,
        ObjCHandle const& right
    ) noexcept
    {
        nullptr != right.GetRawPointer();
    }
}

#endif //KLIB_ENV_APPLE
#endif //!KLIB_KONGKONG_APPLEDEVICE_OBJCHANDLE_H