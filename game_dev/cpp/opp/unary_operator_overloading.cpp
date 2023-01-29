#include <iostream>
using namespace std;

class Cents
{
private:
    int m_cents;
public:
    Cents(int cents = 0) { m_cents = cents; }
    int getCents() const { return m_cents; }
    int& getCents() { return m_cents; }
    
    friend std::ostream& operator << (std::ostream& out, const Cents& cent)
    {
        out << cent.m_cents << endl;
        return out;
    }

    // unary
    Cents operator - () const
    {
        return Cents(-m_cents);
    }

    bool operator !() const
    {
        // ! Cents(...)
        return (m_cents == 0) ? true : false;
    }
};

int main()
{
    Cents cents1(6);
    Cents cents2(0);

    cout << cents1 << endl;
    cout << -cents1 << endl;
    cout << -Cents(10) << endl;

    cout << !cents1 << endl;

    return 0;
}