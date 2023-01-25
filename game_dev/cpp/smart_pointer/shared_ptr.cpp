// ConsoleApplication8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <iostream>
#include <memory>

using namespace std;
class Resource
{
public:
    int* m_data = nullptr;
    unsigned m_length = 0;
public:
    Resource()
    {
        cout << "Resource()" << endl;
    }

    Resource(unsigned length)
    {
        cout << "Resource(unsgined length)" << endl;
        this->m_data = new int[length];
        this->m_length = length;
    }

    Resource(const Resource& res)
    {
        cout << "Resource Copy Constructor()" << endl;
        Resource(res.m_length);

        for (unsigned int i = 0; i < m_length; i++)
        {
            m_data[i] = res.m_data[i];
        }
    }

    ~Resource()
    {
        cout << "Resource Destructor" << endl;
        if (m_data != nullptr) delete[] m_data;
    }

    Resource& operator = (Resource& res)
    {
        std::cout << "Resource Copy Assignment Operator" << endl;

        if (&res == this) return *this;
        if (this->m_data != nullptr) delete[] m_data;

        m_length = res.m_length;
        m_data = new int[m_length];

        for (unsigned int i = 0; i < m_length; i++)
        {
            m_data[i] = res.m_data[i];
        }

        return *this;
    }

    void print()
    {
        for (unsigned int i = 0; i < m_length; ++i)
            cout << m_data[i];
        cout << endl;
    }

    void setAll(const int& v)
    {
        for (unsigned int i = 0; i < m_length; ++i)
            m_data[i] = v;
    }
};

void doSomething(std::shared_ptr<Resource> res)
{

}

int main()
{
    // doSomething(std::unique_ptr<Resource>(new Resource(10000));
    doSomething(std::make_shared<Resource>(10000)); // -> pref
    /*
    Resource* res = new Resource(3);
    res->setAll(1);*/
    {
        /*std::shared_ptr<Resource> ptr1(res);
        ptr1->print();*/

        
        auto ptr1 = std::make_shared<Resource>(3);
        ptr1->setAll(1);
        ptr1->print();

        {
            //std::shared_ptr<Resource> ptr2(ptr1);
            auto ptr2 = ptr1; // possible
            ptr2->setAll(3);
            ptr2->print();
        }
    }

    return 0;
}
