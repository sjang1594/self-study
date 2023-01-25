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

auto doSomething()
{
    // auto res = std::make_unique<Resource>(5);
    // return res;
    return std::unique_ptr<Resource>(new Resource(5));
    // return std::make_unique<Resource>(5);
}

void doSomething2(std::unique_ptr<Resource>& res)
{
    res->setAll(10);
}

int main()
{
    {
        std::unique_ptr<Resource> res(new Resource(10000));
    }

    {
        std::unique_ptr<int> upi(new int);

        // std::unique_ptr<Resource> res(new Resource(5)));
        auto res1 = std::make_unique<Resource>(5);

        res1->setAll(5);
        res1->print();

        std::unique_ptr<Resource> res2;

        // res2 = res1; -- > can't copy in unique_ptr
        res2 = std::move(res1);

        cout << std::boolalpha;
        cout << static_cast<bool>(res1) << endl;
        cout << static_cast<bool>(res2) << endl;

        if (res1 != nullptr) res1->print();
        if (res2 != nullptr) res2->print();
    }

    {
        auto res1 = std::make_unique<Resource>(5);
        res1->setAll(1);
        res1->print();

        doSomething2(res1);
        res1->print();
    }

    return 0;
}