namespace klib::Kongkong::Threading
{
    AppleDevice::ObjCHandle ThreadPool::s_nsOperationQueue = nullptr;

    void ThreadPool::do_addOperationWithBlock(
        void(^block)(void)
    )
    {
        do_initialize();
        do_addOperationWithBlockUnsafe(block);
    }

    void ThreadPool::do_addOperationWithBlockUnsafe(
        void(^block)(void)
    )
    {
        auto p = static_cast<::NSOperationQueue*>(s_nsOperationQueue.GetRawPointer());
        [p addOperationWithBlock:block];
    }

    void ThreadPool::do_initialize()
    {
        if (s_nsOperationQueue != nullptr) return;

        s_nsOperationQueue.SetRawPointer(
            [[::NSOperationQueue alloc] init]
        );
    }

    
}