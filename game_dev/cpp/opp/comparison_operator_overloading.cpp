#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
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

    // comparison operator
    friend bool operator == (const Cents& c1, const Cents& c2)
    {
        return c1.m_cents == c2.m_cents;
    }
    
    friend bool operator != (const Cents& c1, const Cents& c2)
    {
        return c1.m_cents != c2.m_cents;
    }

    friend bool operator < (const Cents& c1, const Cents& c2)
    {
        return c1.m_cents < c2.m_cents;
    }

    friend bool operator > (const Cents& c1, const Cents& c2)
    {
        return c1.m_cents > c2.m_cents;
    }
};

int main()
{
    vector<Cents> arr(20);
    for (unsigned i = 0; i < 20; ++i)
    {
        arr[i].getCents() = i;
    }
    std::random_shuffle(begin(arr), end(arr));
    
    for (auto& e : arr)
        cout << e << " ";
    cout << endl;

    std::sort(begin(arr), end(arr));

    return 0;
}