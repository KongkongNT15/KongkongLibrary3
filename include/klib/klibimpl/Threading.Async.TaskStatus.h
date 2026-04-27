#ifndef KLIB_THRAEDING_ASYNC_TASKSTATUS_H
#define KLIB_THRAEDING_ASYNC_TASKSTATUS_H

#include "base.h"

namespace klib::Threading::Async
{
    enum struct TaskStatus {
        Canceled,  //使われていないよ！
        Completed, //
        Faulted,   //
        Running,   //
        Waiting,   //使われていないよ！
    };
}

#endif //!KLIB_THRAEDING_ASYNC_TASKSTATUS_H
