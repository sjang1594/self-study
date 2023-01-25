#include <iostream>
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
            cout << m_data[i] << endl;
        cout << endl;
    }
};

int main()
{
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL); // disconnect cout from buffer
    std::cout << "Hello World!\n";

    cout.rdbuf(orig_buf);

    return 0;
}