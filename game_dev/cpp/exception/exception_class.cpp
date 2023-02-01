#include <iostream>

using namespace std;

class MyArray
{
private:
    int m_data[5];

public:
    int& operator[] (const int& index)
    {
        if (index < 0 || index >= 5) throw Exception();
        return m_data[index];
    }
};

void doSomething()
{
    MyArray my_array;
    try
    {
        my_array[100];
    }
    catch (const int& x)
    {
        cerr << "Exception " << x << endl;
    }
    catch (ArrayException& e)
    {
        e.report();
        throw e;
    }
    catch (Exception& e)
    {
        e.report();
    }
}

class Exception
{
public:
    void report()
    {
        cerr << "Exception report" << endl;
    }
};

class ArrayException : public Exception
{
public:
    void report()
    {
        cerr << "Array Exception" << endl;
    }
};

int main()
{
    try
    {
        doSomething();
    }
    catch (ArrayException& e)
    {
        e.report();
    }
    return 0;
}
