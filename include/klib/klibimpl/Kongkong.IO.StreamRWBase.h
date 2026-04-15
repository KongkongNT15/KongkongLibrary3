#ifndef KLIB_KONGKONG_IO_STREAMRWBASE_H
#define KLIB_KONGKONG_IO_STREAMRWBASE_H

#include "base.h"
#include "Kongkong.IO.Stream.h"
#include "Kongkong.Containers.PageCache.h"

namespace klib::Kongkong::IO
{
    class StreamRWBase : public HandleType {
        private:

        Stream* m_pStream;
        Containers::PageChache m_page;

        protected:

        constexpr StreamRWBase(
            Stream* baseStream
        ) noexcept;

        StreamRWBase(
            StreamRWBase const&
        ) = default;

        StreamRWBase(
            StreamRWBase&&
        ) = default;

        StreamRWBase& operator=(
            StreamRWBase const&
        ) = default;

        StreamRWBase& operator=(
            StreamRWBase&&
        ) = default;

        public:

        [[nodiscard]]
        constexpr Hash::ResultType GetHashCode() const noexcept;

        [[nodiscard]]
        constexpr Stream& BaseStream() const noexcept;
    };
}

namespace klib::Kongkong::IO
{
    constexpr StreamRWBase::StreamRWBase(
        Stream* baseStream
    ) noexcept
        : m_pStream(baseStream)
    {
    }

    constexpr Hash::ResultType
    StreamRWBase::GetHashCode() const noexcept
    {
        auto h1 = ::std::hash<void*>().operator()(m_pStream);
        auto h2 = m_page.GetHashCode();

        return h1 + h2;
    }

    constexpr Stream&
    StreamRWBase::BaseStream() const noexcept
    {
        return *m_pStream;
    }
}

#endif //!KLIB_KONGKONG_IO_STREAMRWBASE_H