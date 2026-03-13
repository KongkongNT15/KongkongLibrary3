namespace klib::Kongkong::Containers
{
    void ContainerHelper::do_throwLengthZero()
    {
        throw InvalidOperationException(u"コンテナの要素数がゼロでした。");
    }
}