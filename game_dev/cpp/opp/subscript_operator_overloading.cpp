#include <iostream>
#include <cassert>
using namespace std;

class IntList
{
private:
    int m_list[10];

public:
    void setItem(int index, int value)
    {
        m_list[index] = value;
    }

    int getItem (int index) const
    {
        return m_list[index];
    }
    int* getList()
    {
        return m_list;
    }

    int& operator [] (const int index)
    {
        assert(index >= 0);
        assert(index < 10);
        return m_list[index];
    }

    const int& operator [] (const int index) const
    {
        return m_list[index];
    }
};

int main()
{
    IntList my_list;
    my_list.setItem(3, 1);
    cout << my_list.getItem(3) << endl;
    my_list.getList()[3] = 10;
    cout << my_list.getList()[3] << endl;

    my_list[3] = 10;
    cout << my_list[3] << endl;

    const IntList my_list1;
    cout << my_list[4] << endl;

    // pointer
    IntList* list = new IntList;
    (*list)[3] = 10; // ok

    return 0;
}
