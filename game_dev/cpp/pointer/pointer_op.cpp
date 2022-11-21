#include <iostream>
using namespace std;

// Pointer Operation
// 1) 주소 연산자 (&)
// 2) 산술 연산자 (+ -)
// 3) 간접 연산자
// 4) 간접 멤버 연산자 (->)

struct Player
{
	int hp; // +0
	int damage; // +4
};

int main()
{
	int number = 1;

	// 주소 연산자 (&)
	// - 해당 변수의 주소를 알려주세요~
	// - 더 정확히 말하면 해당 변수 타입(TYPE) 에 따라서 Type* 반환
	// ex) address = 0x007AF9E0
	int* pointer = &number;

	// 2) 산술 연산자 (+ -)
	number += 1;  // 1 증가했다!

	// int *
	// - * : 포인터 타입이네 (8byte) 주소를 담는 바구니
	// int : 해당 주소를 따라가면 int(4 bytes 정수형 바구니)가 있다.
	// [!] 포인터에서 +나 -등 산술연산으로 1 을 더하거나 빼면, 
	// 정말 '그 숫자'를 더하고 빼라는 의미가 아니다
	// 한번에 TYPE의 크기만큼 이동해라!
	// 다음/이전 바구니로 이동하고 싶다 << [바구니 단위]의 이동
	// 즉, 1을 더하면 = 바구니 1개 이동시켜라
	// ex) 3을 더하면 = 바구니 3개 이동시켜라
	// pointer += 1; // 4 증가했다

	// 3) 간접 연산자 (*)
	* pointer = 3; // number = 3

	Player player;
	player.hp = 100;
	player.damage = 10;

	// playerPtr 바구니, 바구니 안에 player
	Player* playerPtr = &player;
	(*playerPtr).hp = 200;
	(*playerPtr).damage = 200;

	// What's better way?
	// 4) 간접 멤버 연산자 (->)
	// * 간접 연산자 (포탈 타고 해당 주소로 GOGO)
	// . 구조체의 특정 멤버를 다룰 때 사용 (어셈블리 언어로 까보면 .사실상 그냥 덧셈)
	// ->는 * 와 . 한방에!
	playerPtr->hp = 200;
	playerPtr->damage = 200;

	return 0;
}