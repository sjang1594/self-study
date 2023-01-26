#include <iostream>
using namespace std;
// static member function

int generateId()
{
    static int s_id = 0;
    return ++s_id;
}

class Something
{
public:
    static int m_value;
    static constexpr int s_value = 1;
};

int Something::m_value = 1;

int main()
{
    cout << &Something::m_value << " " << Something::m_value << endl;
    Something st1;
    Something st2;
    st1.m_value = 2;

    // st1.s_value = 3;

    cout << &st1.m_value << " " << st1.m_value << endl;
    cout << &st2.m_value << " " << st2.m_value << endl;

    return 0;
}