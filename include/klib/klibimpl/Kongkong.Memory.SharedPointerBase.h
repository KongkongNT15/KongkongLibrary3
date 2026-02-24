#ifndef KLIB_KONGKONG_MEMORY_SHAREDPOINTERBASE_H
#define KLIB_KONGKONG_MEMORY_SHAREDPOINTERBASE_H

#include "base.h"
#include <atomic>

namespace klib::Kongkong::Memory
{
    class SharedPointerBase {
        friend constexpr bool operator==(
            SharedPointerBase const&,
            SharedPointerBase const&
        ) noexcept;

        friend constexpr bool operator==(
            SharedPointerBase const&,
            ::std::nullptr_t
        ) noexcept;

        friend constexpr bool operator<(
            SharedPointerBase const&,
            SharedPointerBase const&
        ) noexcept;

        friend constexpr bool operator<=(
            SharedPointerBase const&,
            SharedPointerBase const&
        ) noexcept;

        friend constexpr ::std::strong_ordering operator<=>(
            SharedPointerBase const&,
            SharedPointerBase const&
        ) noexcept;

        friend constexpr ::std::strong_ordering operator<=>(
            SharedPointerBase const&,
            ::std::nullptr_t
        ) noexcept;

        friend constexpr ::std::strong_ordering operator<=>(
            ::std::nullptr_t,
            SharedPointerBase const&
        ) noexcept;
    protected:
        struct s_data {
            ::std::atomic<ssize_t> m_referenceCount;
            void(*m_delete)(void*);

            constexpr s_data(
                void(*fDelete)(void*)
            );
        };

        template <class T>
        void DefaultDelete(
            void* p
        ) noexcept;

        s_data* m_pData;

        SharedPointerBase(
            void(*fDelete)(void*)
        );

        constexpr SharedPointerBase(
            ::std::nullptr_t
        ) noexcept;

        [[nodiscard]]
        constexpr operator bool() const noexcept;

        [[nodiscard]]
        constexpr bool operator!() const noexcept;

        /// <summary>
        /// データを所有しているかを確認せずに参照カウントを取得
        /// </summary>
        [[nodiscard]]
        constexpr ssize_t GetReferenceCountUnsafe() const noexcept;

        /// <summary>
        /// 参照カウント
        /// </summary>
        [[nodiscard]]
        constexpr ssize_t ReferenceCount() const noexcept;
    };

    [[nodiscard]]
    constexpr bool operator==(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator==(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator!=(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator<=(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>(
        ::std::nullptr_t,
        SharedPointerBase const& right
        ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    constexpr bool operator>=(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept;

    [[nodiscard]]
    constexpr ::std::strong_ordering operator<=>(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept;
}

namespace klib::Kongkong::Memory
{
    constexpr SharedPointerBase::s_data::s_data(
        void(*fDelete)(void*)
    )
        : m_referenceCount(1)
        , m_delete(fDelete)
    {
    }

    template <class T>
    void SharedPointerBase::DefaultDelete(
        void* p
    ) noexcept
    {
        delete static_cast<T*>(p);
    }

    constexpr SharedPointerBase::SharedPointerBase(
        ::std::nullptr_t
    ) noexcept
        : m_pData(nullptr)
    {
    }

    constexpr
    SharedPointerBase::operator bool() const noexcept
    {
        return *this != nullptr;
    }

    constexpr bool
    SharedPointerBase::operator!() const noexcept
    {
        return *this == nullptr;
    }

    constexpr ssize_t
    SharedPointerBase::GetReferenceCountUnsafe() const noexcept
    {
        return m_pData->m_referenceCount.load();
    }

    constexpr ssize_t
    SharedPointerBase::ReferenceCount() const noexcept
    {
        if (m_pData == nullptr) return 0;
        return m_pData->m_referenceCount.load();
    }

    constexpr bool operator==(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept
    {
        return left.m_pData == right.m_pData;
    }

    constexpr bool operator==(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return left.m_pData == nullptr;
    }

    constexpr bool operator==(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept
    {
        return right == nullptr;
    }

    constexpr bool operator!=(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept
    {
        return !(left == right);
    }

    constexpr bool operator!=(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return !(left == nullptr);
    }

    constexpr bool operator!=(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept
    {
        return !(right == nullptr);
    }

    constexpr bool operator<(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept
    {
        return left.m_pData < right.m_pData;
    }

    constexpr bool operator<(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return false;
    }

    constexpr bool operator<(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept
    {
        return nullptr != right;
    }

    constexpr bool operator<=(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept
    {
        return left.m_pData <= right.m_pData;
    }

    constexpr bool operator<=(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return left == nullptr;
    }

    constexpr bool operator<=(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept
    {
        return true;
    }

    constexpr bool operator>(
        SharedPointerBase const& left,
        SharedPointerBase const& right
        ) noexcept
    {
        return right < left;
    }

    constexpr bool operator>(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return left != nullptr;
    }

    constexpr bool operator>(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept
    {
        return false;
    }

    constexpr bool operator>=(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept
    {
        return right >= left;
    }

    constexpr bool operator>=(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return true;
    }

    constexpr bool operator>=(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept
    {
        return nullptr == right;
    }

    constexpr ::std::strong_ordering operator<=>(
        SharedPointerBase const& left,
        SharedPointerBase const& right
    ) noexcept
    {
        return left.m_pData <=> right.m_pData;
    }

    constexpr ::std::strong_ordering operator<=>(
        SharedPointerBase const& left,
        ::std::nullptr_t
    ) noexcept
    {
        return left.m_pData <=> nullptr;
    }

    constexpr ::std::strong_ordering operator<=>(
        ::std::nullptr_t,
        SharedPointerBase const& right
    ) noexcept
    {
        return nullptr <=> right.m_pData;
    }
}

#endif //!KLIB_KONGKONG_MEMORY_SHAREDPOINTERBASE_H