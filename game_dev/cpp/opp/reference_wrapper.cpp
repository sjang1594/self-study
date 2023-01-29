#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

class Base
{
public:
    int m_i = 0;
    virtual void print()
    {
        cout << "I'm Base" << endl;
    }
};

class Derived : public Base
{
public:
    int m_j = 1;
    virtual void print()
    {
        cout << "I'm derived" << endl;
    }
};

void doSomething(Base& b)
{
    b.print();
}

int main()
{
    Derived d;
    Base& b = d;
    b.print();

    Base c = d; // m_j 잘려나감.. 

    std::vector<Base*> my_vec;
    my_vec.push_back(&b);
    my_vec.push_back(&d);

    for (auto& ele : my_vec)
        ele->print();

    std::vector<std::reference_wrapper<Base>> my_vec2;
    my_vec2.push_back(b);
    my_vec2.push_back(b);
    for (auto& ele : my_vec)
        ele.get().print();

    return 0;
}