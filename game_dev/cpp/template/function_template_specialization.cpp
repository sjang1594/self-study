#include <iostream>
using namespace std;

template <class T>
class Storage
{
private:
	T m_value;

public:
	Storage(T value)
	{
		m_value = value;
	}

	~Storage()
	{}

	void print()
	{
		cout << m_value << endl;
	}
};

template <>
void Storage<double>::print()
{
	std::cout << "Double" << std::endl;
}

template<typename T>
T getMax(T x, T y)
{
    return (x > y) ? x : y;
}

template<>
char getMax(char x, char y)
{
    cout << "Warning : comparing chars" << endl;
    return (x > y) ? x : y;
}

int main()
{
    cout << getMax(1, 2) << endl;
    cout << getMax('c', 'k') << endl;

    Storage<int> nValue(5);
    Storage<double> dvalue(6.8);

    nValue.print();
    dvalue.print();
    return 0;
}