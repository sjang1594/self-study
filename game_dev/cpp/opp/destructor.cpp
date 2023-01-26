#include <iostream>
using namespace std;

class Simple
{
private:
    int     m_id;
   
public:
    Simple(const int& id_in) : m_id(id_in) { cout << "Constructor" << endl; }
    ~Simple() { cout << "Destructor" << endl; }
};

class IntArray
{
private:
    int* m_arr = nullptr;
    int m_length = 0;

public:
    IntArray(const int length_in)
    {
        m_length = length_in;
        m_arr = new int[m_length];
    }

    ~IntArray() { if (m_arr != nullptr) delete[] m_arr; }

    int getLength() { return m_length; }
};

int main()
{
    Simple sim1(32);
    Simple s2(1);

    Simple* s1 = new Simple(0);
    delete s1;

    while (true)
    {
        IntArray my_int_arr(1000);
    }

    return 0;
}
