namespace klib::Kongkong::Containers
{
    void ContainerHelper::do_throwIndexError()
    {
        throw ArgumentOutOfRangeException(u"要素番号に範囲外の値が指定されました。");
    }

    void ContainerHelper::do_throwIndexMinus()
    {
        throw ArgumentOutOfRangeException(u"指定された要素番号が負の値でした。");
    }

    void ContainerHelper::do_throwLengthZero()
    {
        throw InvalidOperationException(u"コンテナの要素数がゼロでした。");
    }
}