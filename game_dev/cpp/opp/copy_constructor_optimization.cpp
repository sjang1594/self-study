#include <iostream>
#include <cassert>
using namespace std;

class Fraction
{
private:
    int m_numerator;
    int m_denominator;

public:
    Fraction(int num = 0, int den = 1) : m_numerator(num), m_denominator(den)
    {
        assert(den != 0);
    }

    Fraction(const Fraction& fraction) // copy constructor 
        : m_numerator(fraction.m_numerator), m_denominator(fraction.m_denominator)
    {
        cout << "Copy Constructor" << endl;
    }

    friend std::ostream& operator << (std::ostream& out, const Fraction& fraction)
    {
        out << fraction.m_numerator << "/" << fraction.m_denominator << endl;
        return out;
    }
};

Fraction doSomething()
{
    Fraction temp(1, 2);
    return temp;
}

int main()
{
    Fraction frac(3, 5);
    Fraction fr_copy(frac);

    Fraction fr_copy1 = frac;
    Fraction fr_copy2(3, 4);


    Fraction result = doSomething(); // rbo
    cout << result << endl; // copy constructor

    cout << frac << " " << fr_copy << endl;
    return 0;
}