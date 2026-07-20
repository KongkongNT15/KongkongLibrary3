namespace klib::Foundation
{
    Initializer MemoryAllocationException::s_initializer =
        []()
    {
        ::std::set_new_handler(
            []() { throw MemoryAllocationException(); }
        );
        
    };
}