#include <iostream>
using namespace std;

// Pointer
// 바구니는 바구니인데
// [주소를 저장하는 바구니!]
// ex) pointer size 8 bytes(on 64 bit), fixed size

void SetHp(int* hp)
{
  *hp = 100;
}

int main()
{
  int hp = 1;
  SetHp(&hp);

  return 0;
}
