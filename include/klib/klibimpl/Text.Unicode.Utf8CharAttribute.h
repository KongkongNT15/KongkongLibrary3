#ifndef KLIB_TEXT_UNICODE_UTF8CHARATTRIBUTE_H
#define KLIB_TEXT_UNICODE_UTF8CHARATTRIBUTE_H

#include "base.h"

namespace klib::Text::Unicode
{
    enum struct Utf8CharAttribute : uint8_t {
        SingleByte       = 1,   //1バイト文字
        TwoByteLead      = 2,   //2バイト文字の開始バイト
        ThreeByteLead    = 3,   //3バイト文字の開始バイト
        FourByteLead     = 4,   //4バイト文字の開始バイト
        FiveByteLead     = 5,   //5バイト文字の開始バイト
        SixByteLead      = 6,   //6バイト文字の開始バイト
        ContinuationByte = 255, //マルチバイト文字の2バイト目以降
    };
}

#endif //!KLIB_TEXT_UNICODE_UTF8CHARATTRIBUTE_H
