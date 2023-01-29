#include <iostream>
using namespace std;

class Mother
{
protected:
    int m_i;
public:

    Mother(const int& i_in)
        : m_i(i_in)
    {
        cout << "Mother Constructor" << endl;
    }

    void setValue(const int& i_in)
    {
        m_i = i_in;
    }

    int getValue() const
    {
        return m_i;
    }
};

class Child : public Mother
{
private:
    double m_d;
public:
    Child(const int& i_in, const double& d_in)
        : Mother(i_in), m_d(d_in)
    {}

    void setValue(const int& i_in, const double& d_in)
    {
        Mother::setValue(i_in);
        m_d = d_in;
    }

    void setValue(const double& d_in)
    {
        m_d = d_in;
    }

    double getValue() const 
    {
        return m_d;
    }
};

int main()
{
    Mother mother(1024);
    mother.setValue(1024);
    cout << mother.getValue() << endl;

    Child child(1024, 321);
    child.setValue(234);
    child.Mother::setValue(1278);
    cout << child.getValue() << endl;
    return 0;
}