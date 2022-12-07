#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

// vector : 동적 배열
// [ ]

// list : 이중 연결 리스트
// [] <-> [] <-> [] 

// deque : double-ended queue (vector 의 특성을 가지고 있지만, list 의 특성도 가지고 있음)
// [  ] 
// [  ]
// - capacity 라는 개념이 없음 (필요할때만 통을 늘리기 때문에)

int main()
{
    // Sequence Container
    // 데이터가 삽입 순서대로 나열되는 형태
    // vector list deque

    // vector 와 마찬가지로 배열 기반으로 동작
    // 다만 메모리 할당 정책이 다르다.
    
    // vector
    // capacity 가 계속 변한다 추가할 때
    // [   ] ] 

    // deque
    // [  ]
    // [  ]

    vector<int> v(3, 1);
    // dq
    // [1, 1, 1, 2] --> 꽉차면 다른 메모리 주소값을 가지고, 거기서 부터 시작
    // [1, 1, 1, 2]
    // [2]    --> after pushing back
    // [3, 3] --> after pushing front.
    deque<int> dq(3, 1);
    
    v.push_back(2);
    v.push_back(2);

    dq.push_back(2);
    dq.push_back(2);

    dq.push_front(3);
    dq.push_front(3);

    // - deque 의 동작 원리
    // - 중간 삽입/삭제 (bad / bad) --> vector 와 마찬가지 (데이터가 비어있으면, 채워줘야된다)
    // - 처음/끝 삽입/삭제 (good / good)
    // - 임의 접근 (good) ex) dq[3] 

    deque<int>::iterator it;
     
    return 0;
}