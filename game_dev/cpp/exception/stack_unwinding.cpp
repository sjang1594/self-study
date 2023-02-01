#include <iostream>
using namespace std;

void first()
{
    cout << "first" << endl;
    try
    {
        second();
    }
    catch (int)
    {
        cerr << "first caught int exception" << endl;
    }

    cout << "End first" << endl;
}

void second()
{
    cout << "second" << endl;
    try
    {
        third();
    }
    catch (double)
    {
        cerr << "second caught int exception" << endl;
    }
    cout << "End second" << endl;
}

void third()
{
    cout << "third" << endl;
    cout << "End third" << endl;
}

// void last() throw(...) exception specifier
void last() throw(...)
{
    cout << "last" << endl;
    cout << "Throws exception" << endl;
    throw - 1;
    cout << "End last" << endl;
}

int main()
{
    cout << "Start" << endl;
    try
    {
        first();
    }
    catch (int)
    {
        cerr << "main caught int exception" << endl;
    }

    catch (...)
    {

    }
}