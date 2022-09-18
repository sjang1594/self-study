#include <iostream>
using namespace std;

unsigned char flag; // remove the signed so that the following number won't be 1.

int main()
{
  #pragma region bit operation
  // When it's used: creating the account & "bitFlag".
  // ~ bitwise not
  // & bitwise and
  // | bitwise or
  // ^ bitwise xor

  // << move the bits to the left
  // remove the N number of left bits, create 0 when it's removed.

  // >> move the bits to the right
  // remove the N number of right bits
  // the one that is going to be created depends on the number is signed or unsigned.
  // if the bit have the sign, then the number will follow that signed number
  // if the bit does not have the sign, it will be 0 (unsigned number)

  // example
  // 0b0000 [invincible][polymorph][stun][levitation]

  // invinsible
  flag = (1 << 3); // move 1 to the right three times.

  // addd polymorph
  flag |= (1 << 2);

  // check if it's invincible (don't care whether the other state.)
  // bitmask
  bool invincible = (flag & (1 << 3)) != 0;

  // if it's invincible and stun state.
  bool mask = (1 << 3 | (1 << 1));
  bool stunOrInvincible = ((flag & 0b1010) != 0);
  #pragma endregion

  return 0;
}
