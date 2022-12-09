#include <iostream>
#include <vector>
#include <list>
using namespace std;

// c++ typdef --> using

// typedef
typedef vector<int>::iterator VecIt;
typedef int id;
typedef __int64 _diff_id;

// using
using id2 = int;

// 1) 직관성이 좋다
typedef void (*MyFunc)();
using MyFunc2 = void(*)();

// 2) template
template<typename T>
// typedef void 할수 없음
// 반면 using 은 사용할수 있게 되어있음
using List = std::list<T>;
template<typename T>
using Vec = std::vector<T>;

// 전에는 어떻게 만들었을까?
template<typename T>
struct List2
{
    typedef std::list<T> mytype;
};

int main()
{
    id playerid = 0;

    List<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);

    List2<int>::mytype li2; // 전의 방식

    return 0;
}