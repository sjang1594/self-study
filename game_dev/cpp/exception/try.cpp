#include <iostream>
using namespace std;

class A
{
private:
    int m_x;
public:
    A(int x) : m_x(x)
    {
        if ( x <= 0 )
            throw 1;
    }
};

class B : public A
{
   B(int x) : A(x)
   {}
};

void doSomething()
{
    try
    {
        throw -1;
    }
    catch(...)
    {
        std::cerr << "catch" << '\n';
    }
    
}

int main()
{
    try
    {
        doSomething();
    }
    catch(...)
    {
        std::cerr << "catch" << '\n';
    }
    
}