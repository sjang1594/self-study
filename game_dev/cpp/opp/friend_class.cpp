#include <iostream>
using namespace std;

class B; // forward declaration

class A
{
private:
    int m_value = 1;
    friend void doSomething(A& a, B& b);
};

class B
{
private:
    int m_value = 2;
    friend void doSomething(A& a, B& b);
};

class C
{
private:
    int m_value = 3;
    friend class D;
};

class D
{
private:
    int m_value = 4;
public:
    void doSomething(C& c)
    {
        cout << c.m_value << endl;
    }
};

void doSomething(A& a, B& b)
{
    cout << a.m_value << endl;
}


int main()
{
    A a;
    B b;
    doSomething(a, b);


    return 0;
}