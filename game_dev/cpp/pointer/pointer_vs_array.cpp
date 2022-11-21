#include <iostream>
using namespace std;

// 배열은 함수 인자로 넘기면, 컴파일러가 알아서 포인터로 치환한다.(char[] -> char*)
void Test2(char arr[])
{
    arr[0] = 'x';
}

int main()
{
    // char array

    // data 주소[H][e][l][l][o][W][o][r][l][d][\0]

    // test1[ 주소 ] << 8 bytes
    // test1 의 포인터는 data 주소의 첫번째를 가르키고 있다.
    const char* test = "Hello World";
    // test2[0] = 'R'; (can't do it

    // data 주소 [H][e][l][l][o][W][o][r][l][d][\0]
    // [H][e][l][l][o][W][o][r][l][d][\0]
    char test2[] = "Hello World";
    test2[0] = 'R';
    cout << test2 << endl;

    // 포인터는 [주소를 담는 바구니]
    // 배열은 [닭장] 즉, 그 자체로 같은 데이터끼리 붙어있는 '바구니 모음'
    // - 다만 [배열 이름] 은 '바구니 모음의 시작 주소.

    Test2(test2);

    // Can we do this
    char test3[12];
    //test3 = test2; // 주소값을 비교하기 때문
    return 0;
}