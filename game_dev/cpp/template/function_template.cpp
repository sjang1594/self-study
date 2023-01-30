#include <iostream>

class Cents
{
private:
	int m_cents;

public:
	Cents(int cents)
		: m_cents(cents)
	{

	}

	friend bool operator > (const Cents& c1, const Cents& c2)
	{
		return (c1.m_cents > c2.m_cents);
	}

	friend std::ostream& operator << (std::ostream& out, const Cents& cents)
	{
		out << cents.m_cents << " cents";
		return out;
	}
};


template <typename T>
T getMax(T x, T y)
{
    return (x > y) ? x : y;
}

int main()
{
    std::cout << getMax(1, 2) << std::endl;
    std::cout << getMax(Cents(5), Cents(6));
    return 0;
}