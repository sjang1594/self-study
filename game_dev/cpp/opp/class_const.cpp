#include <iostream>
using namespace std;
// class const

class Something
{
public:
    int m_value = 0;

    Something() { cout << "Constructor" << endl; }
    // copy constructor
    Something(const Something& st_in)
    {
        m_value = st_in.m_value;
        cout << "Copy Constructor" << endl;
    }

    void setValue(int value) { m_value = value; }
    // void setVlaue(int value) const { m_value = value; } // not allowed 
    int getValue() const { return m_value; }
};

void print(const Something &st) // same address --> with the main
{
    cout << &st << endl;
    cout << st.m_value << endl;
}

class Other
{
public:
    string m_value = "default";

    const string& getValue() const { return m_value; cout << "const version" << endl; }
    string& getValue() { return m_value; cout << "none const version" << endl; }
};


int main()
{
    const int i = 0;
    // i = 3;                               --> not allowed

    const Something something;
    // something.setValue(3);                --> not allowed
    // cout << something.getValue() << endl; --> not allowed

    Something something1;
    cout << &something1 << endl;
    print(something);

    cout << "_________________" << endl;

    Other other;
    other.getValue() = 10;

    const Other other2;
    other2.getValue();
    return 0;
}
