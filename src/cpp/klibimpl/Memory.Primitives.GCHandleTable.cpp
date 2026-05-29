namespace klib::Memory::Primitives
{
    void GCHandleTable::MarkHandleUnsafe(
        ssize_t index
    ) noexcept
    {
        auto& entry = m_entries[index];
        GCHandleEntry expected = entry.load(::std::memory_order_relaxed);
        
        while (true) {

            // 既にマーク済みなら何もしないｳﾋｮｯ
            if (expected.Flags & GCObjectFlag::Marked) {
                return;
            }
            
            GCHandleEntry desired = expected;
            desired.Flags |= GCObjectFlag::Marked; // マークビットを立てるｳﾋｮｯ

            // 16バイトCASでフラグを更新ｳﾋｮｯ
            if (
                entry.compare_exchange_weak(
                    expected,
                    desired,
                    ::std::memory_order_release,
                    ::std::memory_order_acquire
                )
            ) {
                return; // マーク成功ｳﾋｮｯ
            }
            // 失敗（他スレッドが更新した）場合は、最新の expected でリトライｳﾋｮｯ
        }
    }

    void GCHandleTable::SweepAndCompact(
        VirtualMemoryRegion& heap
    )
    {
        GCObject<>* previusObject = nullptr;
        GCObject<>* currentObject = static_cast<GCObject<>*>(heap.Data()); // 移動先の先頭アドレスｳﾋｮｯ

        while (currentObject != nullptr) {

            GCHandleEntry entry = currentObject->GetHandle()->load(
                ::std::memory_order::acquire
            );

            // 参照カウントがゼロなら回収
            if (entry.RefCount == 0) {
                auto nextObject = currentObject->Next();

                auto pHandle = currentObject->GetHandle();
                do_addFreeList(pHandle);
                //
                currentObject->~GCObject();

                if (previusObject == nullptr) {
                    // 最初のオブジェクトが破棄されるだと？？？

                    if (nextObject != nullptr) {
                        new (currentObject) GCObject<>(::std::move(*nextObject));
                    }
                    
                    // previusもcurrentも更新しない
                }
                else {
                    previusObject->Next(nextObject);

                    // previusは更新しない
                    currentObject = nextObject;
                }

                continue;
            }

            previusObject = currentObject;
            currentObject = currentObject->Next();
        }
    }
}