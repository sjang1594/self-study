#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // vector
    // 중간 삽입 / 삭제

    // 반복자 (iterator) : 포인터와 유사한 개념, 컨테이너의 원소(데이터를)를 가르키고
    // 다음/이전 원소로 이동
    vector<int> v(10);
    for (vector<int>::size_type i=0; i < v.size(); i++)
        v[i] = i;

    vector<int>::iterator it;
    int *ptr; 

    // 같은 의미: 데이터를 접근하는 방식은
    // 하지만 다른점은 ?
    // 추가정보로 _Myproxy .. 소속된걸 볼수 있다.
    it = v.begin();
    ptr = &v[0];

    cout << (*it) << endl;
    cout << (*ptr) << endl;

    // ptr 과 it 의 연산자
    // 뺄셈과 덧셈 같다
    ptr++;
    ++ptr;
    it++;
    ++it;

    vector<int>::iterator itBegin = v.begin();
    // 할당된 다음에 쓰레기 메모리까지의 값 --> v.end()
    vector<int>::iterator itEnd = v.end();

    // 팁 ++it 가 성능이 더 좋다.
    // 왜 사용할까? 
    // 다른 컨테이너는 v[i] 와 같은 인덱스 접근이 안될수도 있음

    // iterator는 vector뿐만 아니라, 다른 컨테이너에도 공종적으로 있는 개념
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        cout << (*it) << endl;
    }

    int* ptrBegin = &v[0]; // v.begin()._Ptr;
    int* ptrEnd = ptrBegin + 10; // v.end()._Ptr;
    for (int* ptr = ptrBegin; ptr !=ptrEnd; ++ptr)
    {
        cout << (*ptr) << endl;
    }

    // const int*; read 만 할 경우
    vector<int>::const_iterator cit1 = v.begin();

    // 마지막 데이터에서 차례대로 (역박향)
    for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
    {
        cout << (*it) << endl;
    }


    return 0;
}