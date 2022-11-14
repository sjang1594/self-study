#include <iostream>
#include <vector>
using namespace std;

// stl vector

int main()
{
    // STL (Standard Template Library)
    // 프로그래밍할 때 필요한 자료구조/알고리즘등을
    // 템플릿으로 제공하는 라이브러리

    // 컨테이너 (container): 데이터를 저장하는 객체 (data structure)

    // vector (동적 배열)
    // - vector의 동작 원리 (size/capacity)
    // - 중간 삽입 / 삭제
    // - 처음 / 끝 삽입 / 삭제
    // - 임의 접근

    // 동적 배열
    // 매우 매우 중요한 개념 -> 어떤 마법을 부렸길래 배열을 '유동적으로' 사용한 것인가?

    // 1) (여유분을 두고) 메모리를 할당한다.
    // 2) 여유분까지 꽉 찾으면, 메모리를 increase 한다.

    // Q1) 여유분은 얼만큼이 적당할까?
    // Q2) 증설을 얼만큼 해야 할까?
    // Q3) 기존의 데이터를 어떻게 처리할까?
    vector<int> v;
    // for(int i=0; i<5; i++)
    //     v.push_back(i);

    // 생성자 자체에서 크기를 조정 가능
    vector<int> x(300);
    
    // 생성자 자체에서 크기및 초기값설정 가능
    vector<int> y(300, 0);

    // 생성자 복사
    vecotr<int> x2 = v;

    for (int i = 0; i < 100; i++)
    {
        v.push_back(100);
        cout << v.size() << v.capacity() << endl;
    }
    // size (실제 사용 데이터 개수)
    // 1 2 3 4 5 6
    // capacity (여유분을 포함한 용량 개수)
    // 1 2 3 4 6 9 13 19 28 42 63 .. 1000, 2000 1.5 개씩 늘린다.

    // 그렇다면 왜 reserve 가 필요할까? 
    // 1. 계속적으로 push_back 을 하다 보면, capcity 가 늘어가는걸 볼수있다. 
    // 그때 활용할수 있는 메모리가 부족 함으로써, 더 큰공간으로 이동할수 있게 복사를 도와준다. (sequential array 특징 고려)
    // 그럴때 공간을 미리 크게 확보를 하면, 복사를 할필요가 없기 때문에. 복사 생략
    v.reserve(1000) // 처음부터 여유분 1000 개라는 확신을 가지고, 만든다.
    //v.resize(1000)  // data 1000 개 짜리 할당할때 capacity 도 1000 개를 만든다.
    const int size = v.size();
    cout << size << endl;

    for(int i = 0; i < 3; i++)
    {
        v.push_back(100):
    }

    v.front() // 제일 앞에 
    v.back() // 제일 뒤에
    v.pop_back() // push_back 의 반대

    v.clear()
    vector<int>().swap(v); // capacity 에서 0 을 만들수 있는 방법
    cout << v.size() << v.capacity() << endl;
    // size 는 0 이 되지만 capacity 는 0 이 아니다.

    return 0;
}
