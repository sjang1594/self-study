#include <iostream>
using namespace std;

class Base
{
protected:
	int m_i;

public:
	Base(int value)
		: m_i(value)
	{}

	friend std::ostream& operator << (std::ostream& out, const Base& base)
	{
		out << "This is Base operator" << endl;
		return out;
	}

	void print() {}
};

class Derived : public Base
{
private:
	double m_d;


public:
	Derived(int value)
		: Base(value), m_d(0.0f)
	{}

	friend std::ostream& operator << (std::ostream& out, const Derived& derived)
	{
		cout << static_cast<Base>(derived);
		out << "This is Base operator" << endl;
		return out;
	}
	using Base::m_i;

private:
	using Base::print;
};

int main()
{
	Derived derived(7);
	derived.m_i = 300;
	return 0;
}