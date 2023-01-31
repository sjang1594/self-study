#include <iostream>
#include <array>
#include <string>

using namespace std;

template<typename T>
class A
{
public:
    A(const T& input) {}

    void doSomething()
    {
        cout << typeid(T).name() << endl;
    }

    void test() {}
};

template<>
class A<char>
{
public:
    A(const char& temp) {}
    void doSomething()
    {
        cout << "Char Type Specialization" << endl;
    }
};

int main()
{
    A<int>          a_int(1);
    A<double>       a_double(3,14);
    A<char>         a_char('C');

    a_double.doSomething();
    a_char.doSomething();

    return 0;
}