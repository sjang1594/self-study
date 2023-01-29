#include <iostream>
#include <cassert>
using namespace std;

class Fraction
{
private:
    int m_numerator;
    int m_denominator;

public:
    explicit Fraction(int num = 0, int den = 1) : m_numerator(num), m_denominator(den)
    {
        assert(den != 0);
    }

    Fraction(char) = delete;

    Fraction(const Fraction & fraction) // copy constructor 
        : m_numerator(fraction.m_numerator), m_denominator(fraction.m_denominator)
    {
        cout << "Copy Constructor" << endl;
    }

    friend std::ostream& operator << (std::ostream & out, const Fraction & fraction)
    {
        out << fraction.m_numerator << "/" << fraction.m_denominator << endl;
        return out;
    }
};

Fraction doSomething(Fraction frac)
{
    cout << frac << endl;
}

int main()
{
    Fraction frac(7);
    doSomething(Fraction(7));
    // doSemething(8); --> explicit

    //Fraction frac('c');

    return 0;
}