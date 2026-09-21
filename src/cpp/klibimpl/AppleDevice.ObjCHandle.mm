#define KLIB_OBJC_NSOBJECT (static_cast<::NSObject*>(m_objectPtr))

namespace klib::AppleDevice
{
    void ObjCHandle::do_release() noexcept
    {
        if (m_objectPtr == nullptr) return;

        [KLIB_OBJC_NSOBJECT release];
    }

    void ObjCHandle::do_retain() noexcept
    {
        if (m_objectPtr != nullptr) {
            [KLIB_OBJC_NSOBJECT retain];
        }
    }

    void ObjCHandle::WriteTo(
        ::std::ostream& out
    ) const
    {
        out << m_objectPtr;
    }

    bool operator==(
        ObjCHandle const& left,
        ObjCHandle const& right
    ) noexcept
    {
        auto pLeft = left.As<::NSObject*>();

        auto pRight = right.As<::NSObject*>();

        if (pLeft == nullptr) return pRight == nullptr;

        return static_cast<bool>(
            [pLeft isEqual:pRight]
        );
    }
}

#undef KLIB_OBJC_NSOBJECT