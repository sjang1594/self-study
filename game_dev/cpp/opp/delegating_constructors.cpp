#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    int     m_id;
    string  m_name;

public:
    Student(const string& name_in) : Student(0, name_in) {} // init(id_in, name_in)
    Student(const int& id_in, const string& name_in) : m_id(id_in), m_name(name_in) {}

    /*Better Code*/
    Student(const int& id_in, const string& name_in) 
    {
        init(id_in, name_in);
    }

    void init(const int& id_in, const string& name_in)
    {
        m_id = id_in;
        m_name = name_in;
    }
    void print() { cout << m_id << " " << m_name << endl; }
};

int main()
{
    Student student(0, "Jack Jack");
    student.print();
    
    Student student2("Nick");
    student2.print();
    return 0;
}
