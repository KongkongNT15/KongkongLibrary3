#ifndef KLIB_THRAEDING_THREADSTATE_H
#define KLIB_THRAEDING_THREADSTATE_H

#include "base.h"

namespace klib::Threading
{
    enum struct ThreadState {
        Running          = 0,
        StopRequested    = 0x1,
        SuspendRequested = 0x2,
        Background       = 0x4,
        Unstarted        = 0x8,
        Stopped          = 0x10,
        WaitSleepJoin    = 0x20,
        Suspended        = 0x40,
        AbortRequested   = 0x80,
        Aborted          = 0x100,
    };
}

#endif //!KLIB_THRAEDING_THREADSTATE_H