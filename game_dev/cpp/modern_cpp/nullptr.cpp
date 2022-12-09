#include <iostream>
#include <vector>

using namespace std;
#define NULL 0

class Knight
{
public:
    void Test(){}
};

Knight* FindKnight(){ return nullptr; }

void Test(int a) { cout << "Test(int)" << endl; }
void Test(void *ptr) { cout << "Test(*)" << endl; }

// nullPtr 구현
class NullPtr
{
public:
    // 그 어떤 타입의 포인터와도 치환 가능
    template<typename T>
    operator T*() const{ return 0; }

    // 그 어떤 타입의 멤버 포인터와도 치환가능 // 잘모르겠음
    template<typename C, typename T>
    operator T C::* () const { return 0; }

private:
    void operator&() const; // 주소 값을 막는다.
} _NullPtr;

// const NullPtr _NullPtr; // 위에 _NullPtr 로 선언 가능하다.

int main()
{
    // 0 NULL 
    int *ptr = NULL; // 0 NULL

    Test(0);
    Test(NULL); 
    // 위의 Test(int a) 를 call 한다.
    Test(nullptr); // 정상적으로 작동. Test(void *ptr) 정석으로 표현해야 한다. (오동작을 방지하기 위해서)

    auto Knight = FindKnight();

    nullptr_t whoami = nullptr; // 객체 타입

    void (Knight::*memFunc)(); // operator T C::* () const { return 0; }
    memFunc = &Knight::Test;
    if (memFunc == _NullPtr){}

    // &nullptr; // private 에 선언된 부분
     
    return 0;
}