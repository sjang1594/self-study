#include <iostream>
using namespace std;

// 참조

struct StatInfo{
  int hp;
  int attack;
  int defence;
};

void PrintInfoByValue(StatInfo info)
{
  cout << "_________________" << endl;
  cout << info.hp << endl;
  cout << info.attack << endl;
  cout << info.defence << endl;
}

void PrintInfoByPtr(StatInfo* info)
{
  cout << "_________________" << endl;
  cout << info->hp << endl;
  cout << info->attack << endl;
  cout << info->defence << endl;
}

void PrintInfoByRef(StatInfo& info)
{
  cout << "_________________" << endl;
  cout << info.hp << endl;
  cout << info.attack << endl;
  cout << info.defence << endl;
}

// const 위치
StatInfo globalinfo;

// Reference 단점 예제
void PrintInfo(StatInfo *info)
{

  if (info == nullptr)
    return;
  cout << "_________________" << endl;
  cout << info->hp << endl;
  cout << info->attack << endl;
  cout << info->defence << endl;

  // 별 뒤에 붙인다면?
  // StatInfo* const info
  // info 라는 바구니의 내용을(주소)를 바꿀수 없음
  // info는 주소 값을 갖는 바구니 ->이 주소 값이 고정이다

  // 별 앞에 붙인다면?
  // const Stat *info
  // info 가 '가르키고 있는' 바구니의 내용물을 바꿀 수 없음
  // '원격' 바구니의 내용물을 바꿀수 없음

  // info[주소값]  주소값[데이터]
  info = &globalinfo;
  info->hp= 1000;
}

void PrintInfo(const StatInfo &info)
{
  cout << "_________________" << endl;
  cout << info.hp << endl;
  cout << info.attack << endl;
  cout << info.defence << endl;
}

#define OUT
void ChangeInfo(OUT StatInfo& info)
{
  info.hp = 1000;
}

// 특정 조건을 만족하는 몬스터를 찾는 함수
StatInfo* FindMonster()
{
    //Todo : Heap 영역에서 뭔가를 찾아봄
    //찾았다!
    //return monster-;

    // if not
    return nullptr;
}

int main()
{
  int number = 1;
  StatInfo info;

  int *pointer = &number;
  // Low Level(Assembly) --> Poitner 와 동일
  int& reference = number;
  reference = 3;

  // Pointer vs Reference
  // Performance : Same
  // Convinence  : Reference > Pointer

  // 1) Related Convinence
  // 편의성이 좋다는게 꼭 장점만은 아니다
  // 포인터는 주소를 넘기니 확실하게 원본을 넘긴다는 힌트를 얻을수 있는데
  // 참조는 자연스럽게 모르고 지나칠 수도 있음
  // ex) 마음대로 고친다면?
  // const 를 사용해서 이런 마음대로 고치는 부분을 개선 가능

  // 참고로 포인터도 const를 사용가능
  // * 개준으로 앞에 붙이느냐, 뒤에 붙이느냐에 따라 의미가 다르다

  // 2) 초기화 여부
  // 참조 타입은 바구니의 2번째 이름 (별칭?)
  // -> 참조하는 대상이 없으면 안됨
  // 반면 포인터는 그냥 어떤~ 주소라는 의미
  // -> 대상이 실존하지 않을 수도 있음
  // reference 는 operation(ex: arithematics) 이 안됨


  // 그래서 결론은 ?
  // 사실을 Team By Team ... 정해진 답은 없다.
  // ex) google 은 pointer 로
  // ex) Unreal 엔진에선 reference 애용

  // - 없는 경우도 고려해야 한다면, pointer (null 체크 필수)
  // - 바뀌지 않고 읽는 용도(readonly)만 사용하면 const ref
  // - 그 외 일반적으로 ref (명시적으로 호출할때 out을 선호)
  StatInfo* pointer = nullptr;

  // Bonus) 포인터로 사용하던걸 참조로 넘겨주려면?
  // pointer [  주소(&info)  ]  info[데이터]
  // StatInfo& ref = *pointer
  // PrintInfoByRef(*pointer)

  // Bonus) 참조로 사용하던걸 포인터로 넘겨주려면?
  // StatInfo*ptr = &reference
  // pointer[주소] reference, info[데이터]
  // PrintInfoByPtr(&reference)
  // pointer = &info;
  // PrintInfo(pointer);

  StatInfo& reference = info;
  //PrintInfo(reference);

  ChangeInfo(OUT info);
  return 0;
}
