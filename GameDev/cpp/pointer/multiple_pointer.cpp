#include <iostream>
using namespace std;

void SetNumber(int * a)
{
    *a = 1;
}

void SetMessage(const char *a)
{
    a = "Bye";
    // 바꾸려면 const char --> char
    // 그리고 *를 붙이면된다.
}

void SetMessage(const char **a)
{
    // a = "Bye"; --> Error
}

void SetMessage1(const char *&a)
{
    a = "Wow";
}

int main()
{
    // Multiple Pointer
    int a = 0;
    SetNumber(&a);
    cout << a << endl;

    // .rdata[H][e][l][l][o][\0]
    // msg[Hello 주소] << 8 bytes
    const char*msg = "Hello";

    SetMessage(msg);

    // 주소2 [] << 1 bytes
    // 주소1[주소2] << 8 bytes
    // pp[주소] << 8 bytes

    // .rdata[H][e][l][l][o][\0]
    // msg[ Hello 주소] << 8 bytes
    // pp[&msg] << 8 bytes

    const char** pp = &msg;
    *pp = "Bye";
    return 0;
}