#include <iostream>
using namespace std;

// 오늘의 주제: delete (삭제된 함수)

class Knight
{
public:

// 고전적
private:
    // 정의 되지 않은 비공개(private) 함수
    // 내부에서는 복사가 가능 하다
    void operator=(const Knight& k);
    // 예외적으로 함수를 사용할수 있게 하는건
    // 모든 것을 뚫는 창 vs 절대 방패
    friend class Admin;

// delete 사용
public:
    void operator=(const Knight& k) = delete;

private:
    int _hp = 100;
};

class Admin
{
public:
    void CopyKnight(const Knight& k)
    {
        Knight k1;
        // 복사 연산
        //k1 = k;
    }
};

int main()
{
    Knight k1;
    Knight k2;

    Admin admin;
    admin.CopyKnight(k1); // link error

    return 0;
}