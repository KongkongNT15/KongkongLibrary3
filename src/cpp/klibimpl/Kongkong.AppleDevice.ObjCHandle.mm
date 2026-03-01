#define KLIB_OBJC_NSOBJECT (static_cast<::NSObject*>(m_objectPtr))

namespace klib::Kongkong::AppleDevice
{
    

    

    void ObjCHandle::do_release() noexcept
    {
        if (m_objectPtr == nullptr) return;

        [KLIB_OBJC_NSOBJECT release];
    }

    void do_retain() noexcept
    {
        if (m_objectPtr != nullptr) {
            [KLIB_OBJC_NSOBJECT retain];
        }
    }

    bool operator==(
        ObjCHandle const& left,
        ObjCHandle const& right
    ) noexcept
    {
        auto pLeft = static_cast<::NSObject*>(
            left.GetRawPointer()
        );

        auto pRight = static_cast<::NSObject*>(
            right.GetRawPointer()
        );

        if (pLeft == nullptr) return pRight == nullptr;

        return static_cast<bool>(
            [pLeft isEqual:pRight]
        );
    }
}

#undef KLIB_OBJC_NSOBJECT