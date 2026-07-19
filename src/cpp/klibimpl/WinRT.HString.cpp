namespace klib::WinRT
{
    HString HString::Concat(
        HString const& left,
        HString const& right
    )
    {
        ::HSTRING result;
        auto code = ::WindowsConcatString(
            left.m_ref,
            right.m_ref,
            &result
        );

        switch (code) {
            case S_OK: [[likely]] break;

            case E_INVALIDARG:
            case E_OUTOFMEMORY: [[unlikely]] throw MemoryAllocationException();
        }

        return HString(result);
    }

    HString::HString(
        StringView str
    )
        : HString(
            static_cast<SizeType>(str.Length()),
            str.Data()
        )
    {
    }

    HString::HString(
        SizeType length,
        const ElementType* str
    )
    {
        auto code = ::WindowsCreateString(
            reinterpret_cast<const wchar_t*>(str),
            length,
            &m_ref
        );

        switch (code) {
            case S_OK: [[likely]] break;
            
            //case E_INVALIDARG: [[unlikely]]
            case E_POINTER: [[unlikely]]
                ::WindowsCreateString(
                    nullptr,
                    0,
                    &m_ref
                );
                break;

            case E_OUTOFMEMORY: [[unlikely]]
                throw MemoryAllocationException();
        }
    }

    StringView HString::GetView() const noexcept
    {
        const wchar_t* p;
        SizeType length;

        p = ::WindowsGetStringRawBuffer(
            m_ref,
            &length
        );

        return StringView(
            length,
            reinterpret_cast<const ElementType*>(p)
        );
    }

    
}