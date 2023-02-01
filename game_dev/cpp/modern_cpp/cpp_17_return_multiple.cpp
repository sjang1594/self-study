#include <iostream>
#include <tuple>
using namespace std;

tuple<int, int> my_func()
{
    return tuple<int, int>(123, 456);
}

auto my_func2()
{
    return tuple(123, 456, 789, 19);
}

int main()
{
    tuple<int, int> result = my_func();
    cout << get<0>(result) << " " << get<1>(result) << endl;

    auto [a, b, c, d] = my_func2();
    cout << a << " " << b << " " << c << " " << d << endl;
    return 0;
}