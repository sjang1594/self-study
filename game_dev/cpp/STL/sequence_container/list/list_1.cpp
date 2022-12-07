#include <iostream>
#include <vector>
#include <list>
using namespace std;

// list : linked list 
// single / double / circle
// [1] ---> [2] ---> [3] -> [4]
// [1] <--> [2] <--> [3] <-> [4] <-> [ _Myhead : end() ]
// [1] <--> [2] <--> [3] <-> [4] <->

// Node [ data(4) next(4 or 8) ] -> Node [ data(4) next(4 or 8) ]
class Node
{
public:
    Node* _next;
    int _data;
}; 

int main()
{
    // - list (linked list)
    // - list 동작 원리
    // - 중간 삽입 / 삭제 (Good)
    // - 처음/끝 삽입/삭제 (Good)
    // - 임의 접근 [i 번째 데이터는 어디에 있습니까?] 

    list<int> li;
     
    for(int i=0; i< 100; i++)
        li.push_back(i);
    
    //li.push_front(10);
    int size = li.size();
    //li.capacity(); // 없음 -> 동적배열이 아니므로

    int first = li.front();
    int last = li.back();

    //li[3] = 10; // 없음

    list<int>::iterator itBegin = li.begin();
    list<int>::iterator itEnd = li.end();

    int* ptrBegin = &(li.front());
    int* ptrEnd = &(li.back());

    // list<int>::iterator itTest = --itBegin; // 두로 가는건 불가
    list<int>::iterator itTest2 = --itEnd;
    //list<int>::iterator itTest3 = ++itEnd; // 앞으로 가는것도 불가

    for (list<int>::iterator it=li.begin(); it != li.end(); ++it)
    {
        cout << (*it) << endl;
    }

    // 삽입 / 삭제
    li.insert(itBegin, 100);
    li.erase(li.begin());
    li.pop_front(); // pop series
    li.remove(10); // key 값을 넣어줘서, 10인 애들을 삭제 한다. 

    // * 임의 접근이 안되는데, 중간 삽입/삭제 빠르다.
    // 50번 인덱스에 있는 데이터를 삭제:
    list<int>::iterator it = li.begin();
    for(int i=0; i < 50; i++)
        ++it;
    
    li.erase(it);

    list<int>::iterator itRemember;
    for (int i=0; i < 100; i++)
    {
        if (i==50)
        {
            itRemember = li.insert(li.end(), i);
        }
        else
        {
            li.push_back(i);
        }
    }

    li.erase(itRemember);
    return 0;
}