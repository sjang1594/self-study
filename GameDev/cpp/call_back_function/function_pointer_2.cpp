# include <iostream>
using namespace std;

// typedef 의 진실
// typedef 왼쪽 오른쪽 -> 오른쪽 (커스텀 타입 정의)
// ex) typedef int NUMBER;

// 정확히는 왼쪽/오른쪽 기준이 아니라
// [선언 문법] 에서 typedef를 앞에다 붙이는 쪽

// 정적함수
class Knight
{
public:
//    static void HelloKnight()
//    {
//        //_hp = 20; 수정 불가능
//    }
    // 멤버함수
    int GetHp(int a, int b)
    {
        cout << "GetHp()" << endl;
        return _hp;
    }
public:
    int _hp = 100;
};

typedef int INTEGER;
typedef int *POINTER;
typedef int FUNC(int, int); // 이말은 함수가 나타나는것이 아니라, 이제 함수타입이라는게 존재 할거다.
typedef int Array[20];

// 함수 포인터
typedef int (*PFUNC)(int a, int b);

// 그렇다면 knight 에 포함된 멤버함수를 function pointer 로 표현 한다면
typedef int(Knight::*KNIGHT_FUNC)(int, int);

int Test(int a, int b)
{
    cout << "Test" << endl;
    return 0;
}

// 전역함수 예
int T(int a, int b)
{
    cout << a << b << endl;
    return 0;
}

int main()
{
    //int (*fn)(int, int);
    //typedef int(FUMC_TYPE)(int, int);
    //FUMC_TYPE* fn;
    //  fn = Test;
    PFUNC fn;
    // What about if we don't put pointer in front
    // This func T doesn't go or save in stack memory, it's just declaration that the function will be run.
    //    FUNC T;
    //    T(1, 2);
    //    FUNC* funcs;
    //    PFUNC func;
    //    func(1, 2);

     fn = &Test; // & 생략 가능 (c 언어 호환성 때문)
     fn(1, 2);
     (*fn)(1, 2);

    // 위 문법으로 [전역함수] / [정적함수]만 담을수 있다. (호출 규약이 동일한 애들)
    // fn = &Knight::GetHp();
    Knight k1;
    k1.GetHp(1, 1);

    KNIGHT_FUNC m_fn;
    m_fn = &Knight::GetHp;

    (k1.*m_fn)(1, 1);

    Knight *k2 = new Knight();
    //((*k2).*m_fn)(1, 1);
    (k2->*m_fn)(1, 1);
    delete k2;
    return 0;
}