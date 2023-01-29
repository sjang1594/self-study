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

	void print() { cout << "Base" << endl; }

	friend std::ostream& operator << (std::ostream& out, const Base& base)
	{
		out << "This is Base operator" << endl;
		return out;
	}

};

class Derived : public Base
{
private:
	double m_d;

public:
	Derived(int value)
		: Base(value), m_d(0.0f)
	{}

	void print() { Base::print(); cout << "Derived" << endl; }

	friend std::ostream& operator << (std::ostream& out, const Derived& derived)
	{
		cout << static_cast<Base>(derived);
		out << "This is Base operator" << endl;
		return out;
	}
};

int main()
{
	Base base(5);
	base.print();

	Derived derived(7);
	derived.print();
	return 0;
} 