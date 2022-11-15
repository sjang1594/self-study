#include <iostream>
using namespace std;

// template basic
template<typename T> // template<class T> 동일
void Print(T a)
{
    cout << a << endl;
}

template<typename T>
T Add(T a, T b){return a + b; }

template<typename T1, typename T2>
void Print(T1 a, T2 b)
{
    cout << a << b << endl;
}

class Knight
{
public:
public:
    int _hp = 100;
};

// 연산자 오버로딩 [전역함수]
ostream& operator<<(ostream& os, const Knight& k)
{
    os << k._hp;
    return os;
}

// Template 특수화
template<>
void Print(Knight k)
{
    cout << k._hp << endl;
}

int main()
{
    // Template : 함수나 클래스를 찍어내는 틀
    // 1) 함수 템플릿
    // 2) 클래스 템플릿
    Print<int>(50); // 명시적인 표현, int type 이라는걸
    Print(50.0f);
    Print("Yes");

    Print("yes", 30);
    int result = Add(3, 2);
    float result_2 = Add<float>(3.4, 5.2); // 명시적인 표현

    Knight k1;
    Print(k1);
  return 0;
}
