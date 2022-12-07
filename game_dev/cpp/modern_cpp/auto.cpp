#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Knight
{
public:
    int _hp;
};

template<typename T>
void Print(T t)
{
    cout << t << endl;
}

// Modern cpp : c++11
int main()
{
    auto a = 3;
    auto b = 3.14f;
    auto c = 1.23;
    auto d = Knight();
    auto e = "nick";

    // auto 는 일종의 조커 카드
    // type deduction
    // -> compiler 한테 알아서 잘맞춰봐~ (추론)

    // 추론 규칙은 복잡해질수 있다. 

    auto f = &d;
    const auto test1 = b; // const float

    auto* test2 = e; // const char 
    //auto* test3 = a; // doesn't work

    // 주의 
    // 기본 auto 는 const, & 무시!!
    int &reference = a;
    const int cst = a;
    auto test4 = reference; // int 
    auto test5 = cst;       // int

    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    for (vector<int>::size_type i = 0; i < v.size(); i++)
    {
        int& data = v[i]; // auto 로 바꾼다고 하면, vector 의 값들이 변경 되지 않는다. --> auto & 이런식으로 
        data = 100;
    }

    // 아무튼 이제 기존의 타입은 잊어버리고, auto 만 사용할래요~
    // 별로 안좋다 --> 가독성 측면에서
    // 타이핑이 길어지는 경우에는 OK
    
    map<int, int> m;
    auto ok = m.insert(make_pair(1, 100));
    for(auto it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << endl;
    }
    return 0;
}