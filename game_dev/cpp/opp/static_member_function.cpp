#include <iostream>
using namespace std;

class Something
{
public:
    class _init
    {
    public:
        _init()
        {
            s_value = 1234;
        }
    };
private:
    static int s_value;
    int m_value;
    static _init s_initializer;
public:
    // cannot initialize static member variable in constructor.
    Something() {}
    static int getValue()
    {
        // return this->s_value;
        // return m_value
        return s_value;
    }
    int temp()
    {
        return this->s_value;
    }
};

int Something::s_value;
Something::_init Something::s_initializer;

int main()
{
    cout << Something::getValue() << endl;
    Something s1, s2;
    cout << s1.getValue() << endl;
    // cout << s1.s_value << endl;

    int (Something:: * fptr1)() = &Something::temp;

    cout << (s2.*fptr1)() << endl;

    int (* fptr2)() = &Something::getValue;

    cout << fptr2() << endl;



    return 0;
}