#ifndef KLIB_KONGKONG_THRAEDING_ASYNC_TASKSTATUS_H
#define KLIB_KONGKONG_THRAEDING_ASYNC_TASKSTATUS_H

#include "base.h"

namespace klib::Kongkong::Threading::Async
{
    enum struct TaskStatus {
        Canceled,  //使われていないよ！
        Completed, //
        Faulted,   //
        Running,   //
        Waiting,   //使われていないよ！
    };
}

#endif //!KLIB_KONGKONG_THRAEDING_ASYNC_TASKSTATUS_H