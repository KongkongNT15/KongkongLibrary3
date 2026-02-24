
namespace Test
{
    class MyClass {};
}

namespace Test1
{
    using Test::MyClass;
}

void f()
{
    using namespace Test;
    using namespace Test1;

    MyClass s;
}