#include <iostream>
#include <vector>

using namespace std;

class Knight
{
public:
    Knight(int a, int b)
    {
        cout << "Knight(int a, int b)" << endl;
    }
    Knight(initializer_list<int> li)
    {
        cout << "Knight(initialize_list)" << endl;
    }
};

int main()
{
    // initialization
    int a = 10;
    int b(0);
    int c{0};

    //Knight k1;
    //Knight k2 = k1; // 복사 생성자 (대입 연산자 x)
    // Knight k3;
    // k3 = k1; // 대입 연산자  
    //Knight k3{k1};

    // vector & array initialization.
    // 1) vector 등 container 과 잘 어울린다.
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    vector<int> v2(10, 1);
    int arr[] = {1, 2, 3, 4};

    vector<int> v3{1, 2, 3, 4};

    // 2) 축소 반환 방지
    // int x = 0;
    // double y {x}; // 허용 하지 않음

    // 3) Bonus
    Knight k4(); // 기본생성자 호출 X
    Knight k5{}; // 기본생성자

    Knight k6{1, 2, 3, 4}; // 어떤생성자?
    // --> 할려면 initialize_list keyword 가 필요하다.
    // 어떨때 사용해야될까?
    Knight k3{1, 2}; // Initialize_list 가 무조건 먼저 호출 (최상의 포식자)

    // 괄호 초기화 ()를 기본으로 간다
    // - 전통적인 c++ (거부감이 없음)
    // - vector 등 특이한 케이스일때만 {} 사용

    // 중괄호 초기화 {} 를 기본으로 간다
    // - 초기화 문법의 일치화
    // - 축소 변환 방지
    
    return 0;
}