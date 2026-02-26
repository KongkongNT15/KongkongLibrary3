
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
    using namespace klib::Kongkong::Numerics;

    Vector2<> v1;
    Vector2<double> v2;

    auto ddd = v1 + v2;

    v1 = v2;
}