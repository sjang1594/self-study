#include <iostream>
using namespace std;

class Digit
{
private:
    int m_digit;
public:
    Digit(int digit = 0) { m_digit = digit; }
    int getDigit() const { return m_digit; }
    int& getDigit() { return m_digit; }

    friend std::ostream& operator << (std::ostream& out, const Digit& digit)
    {
        out << digit.m_digit << endl;
        return out;
    }

    // increment & decrement operator
    // prefix
    Digit& operator ++()
    {
        ++m_digit;
        return *this;
    }

    Digit& operator --()
    {
        --m_digit;
        return *this;
    }

    // post
    Digit operator ++ (int)
    {
        Digit temp(m_digit);
        ++(*this);
        return temp;
    }
};

int main()
{
    Digit digit(1);
    cout << ++digit << endl;
    cout << digit << endl;
    cout << digit++ << endl;
    cout << digit << endl;

    return 0;
}
