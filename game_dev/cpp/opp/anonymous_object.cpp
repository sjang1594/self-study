#include <iostream>
using namespace std;

/// rvalue 처럼 작동
class A
{
public:
    A(const int& input) : m_value(input) { cout << "Constructor" << endl; }
    ~A() { cout << "Destructor" << endl; }
    void print() { cout << "Hello" << endl; }
public:
    int m_value;
};

class Cents
{
private:
    int m_cents;
public:
    Cents(int cents) { m_cents = cents; }
    int getCents() const { return m_cents; }
};

Cents add(const Cents& c1, const Cents& c2)
{
    return Cents(c1.getCents() + c2.getCents());
}

int main()
{
    A(1).print();

    cout << add(Cents(6), Cents(8)).getCents() << endl;
    return 0;
}