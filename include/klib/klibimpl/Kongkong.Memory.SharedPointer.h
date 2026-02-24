#ifndef KLIB_KONGKONG_MEMORY_SHAREDPOINTER_H
#define KLIB_KONGKONG_MEMORY_SHAREDPOINTER_H

#include "base.h"
#include "Kongkong.Memory.SharedPointerBase.h"
#include "Kongkong.MemoryAllocationException.h"

namespace klib::Kongkong::Memory
{
    template <class T>
    class SharedPointer final : SharedPointerBase {
    public:
        using Type = typename ::std::remove_cvref_t<T>;

    private:

        Type* m_pointer;

        template <class... Args>
        SharedPointer(Args&&... args);

    public:

        template <class... Args>
        [[nodiscard]] static SharedPointer New(
            Args&&... args
        );

        constexpr SharedPointer(
            ::std::nullptr_t
        ) noexcept;
        
        template <class TType>// requires ::std::derived_from<TType, Type>
        SharedPointer(
            TType* p
        );

        SharedPointer(
            void*
        ) = delete;

        SharedPointer(
            const void*
        ) = delete;

        ~SharedPointer();

        [[nodiscard]]
        constexpr Type* operator->() const noexcept requires (!::std::is_void_v<Type>);

        [[nodiscard]]
        constexpr Type* RawPointer() const noexcept;
    };
}

namespace klib::Kongkong::Memory
{
    template <class T>
    template <class... Args>
    SharedPointer<T>::SharedPointer(
        Args&&... args
    )
        : SharedPointerBase(DefaultDelete<Type>)
        , m_pointer(KLIB_NEW Type(::std::forward<Args>(args)...))
    {
        MemoryAllocationException::CheckNull(
            m_pointer,
            [this->m_pData]() { delete this->m_pData; }
        );
    }

    template <class T>
    template <class... Args>
    SharedPointer<T> SharedPointer<T>::New(
        Args&&... args
    )
    {
        return SharedPointer<T>(::std::forward<Args>(args)...);
    }

    template <class T>
    constexpr SharedPointer<T>::SharedPointer(
        ::std::nullptr_t
    ) noexcept
        : SharedPointerBase(nullptr)
        , m_pointer(nullptr)
    {
    }

    template <class T>
    template <class TType>// requires ::std::derived_from<TType, typename SharedPointer<T>::Type>
    SharedPointer<T>::SharedPointer(
        TType* p
    ) noexcept
        : SharedPointerBase(nullptr)
        , m_pointer(p)
    {
        if (p == nullptr) [[unlikely]] return;

        m_pData = KLIB_NEW s_data(DefaultDelete<TType>);

        MemoryAllocationException::CheckNull(m_pData);
    }

    template <class T>
    SharedPointer<T>::~SharedPointer()
    {
        if (m_pData == nullptr) return;

        if (m_pData->m_referenceCount.operator--() == 0) {
            delete m_pointer;
            delete m_pData;
        }
    }

    template <class T>
    constexpr typename SharedPointer<T>::Type*
    SharedPointer<T>::operator->() const noexcept requires (!::std::is_void_v<Type>)
    {
        return m_pointer;
    }

    template <class T>
    constexpr typename SharedPointer<T>::Type*
    SharedPointer<T>::RawPointer() const noexcept
    {
        return m_pointer;
    }
}

#endif //!KLIB_KONGKONG_MEMORY_SHAREDPOINTER_H