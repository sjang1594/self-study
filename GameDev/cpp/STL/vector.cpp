#include <iostream>
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

    // 배열
    const int MAX_SIZE = 10;
    int arr[MAX_SIZE] = {};

    // initialize
    for(int i=0; i < MAX_SIZE; i++)
        arr[i] = i;
    

    return 0;
}
