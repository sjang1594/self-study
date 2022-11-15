#include <iostream>
using namespace std;

const int AIR = 0;
const int STUN = 1;
const int POLYMORPH = 2;
const int INVINCIBLE = 3;

// Global Variable
// [Data Section]
// .data (initial value exists)
int a = 2;

// .bss (initial value doesn't exist)
int b;

// .rodata (only readable data)
const char* msg = "Hello World";

int main()
{
  // [Stack Space]
  int c = 3;

  return 0;
}
