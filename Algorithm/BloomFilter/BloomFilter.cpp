/* BloomFilter.cpp
*  Non-deterministic
*  
*  False Negative, False Positive => �� Ư�� ���Ұ� �����Ѵٴ� ������ �亯�� ����μ�, �������� �ְ� �������� �ְ�.
*  ������, Ư�����Ұ� �������� �ʴ´ٴ� �������� �亯�� ����μ��� �� ���Ҵ� Ȯ���� ����.
* 
*  �� ��Ȯ���Ѱǵ���?
*  ���� boolean table �ȿ� �ִ� Element ���� ���δ� 1 �� �ȴٰ��ϸ�, ���� ��¥ ã���� �ϴ� Lookup table ���� ������ True �� ��ȯ�ϴϱ�.
*  �׷��� Likely �� Check �ϴ°ſ� ���ٰ� �����ϸ�ȴ�.
* 
*  Bloom Filter ��ü�� Element �� �������� ������, Boolean ���� �����Ѵ�.
* 
*  ����:
*  HashFunction ���� ���� ����ϰ�, Boolean Table �ȿ���, �� Hash �� Index �� 1 �� ����
* 
*  Lookup �Լ�������, Boolean Table �ȿ�, �ش�Ǵ� Index �� 1 ���� �ƴ����� üũ. ���� 1 �̸� Return True
* 
*  Situation 1.
*  [0][0][0][0][0][0][0]
*  
*  Hash Function
*  1. hash1(x) = x % 7
*  2. hash2(x) = (x/7) % 7
*  3. hash3(x) = (x/11) % 7
* 
*  Insert 100 = {2, 0, 2} // index
*  [1][0][1][0][0][0][0]
* 
*  Insert 54 = {5, 0, 4} // index
*  [1][0][1][0][1][1][0]
* 
*  Insert 82 = {5, 4, 0} // index 
*  [1][0][1][0][1][1][0]
* 
*  Lookup(5)
*  Hash(5) = {5, 0, 0}
*  [1][0][1][0][1][1][0] // Index 5 is filled, it's true
* 
*  Lookup(50) = {1, 0, 4}
*  [1][0][1][0][1][1][0] -> Index 1 is 0, false
*  
*  Lookup(20) = {6, 2, 1}
*  [1][0][1][0][1][1][0] -> Index 6 is 0, false
* 
*  Lookup(54) = {5, 0, 4}
*  [1][0][1][0][1][1][0] -> It's true
*/

#include <iostream>
#include <vector>

// 1 BYTE = 8 BITS
// 
// 1023 Bit -> 1023 / 8 => 128
// key % 1023

class BloomFilter
{
    std::vector<bool> data;
    int nBits;

    int hash(int num, int key)
    {
        switch (num)
        {
        case 0: return key % nBits;
        case 1: return (key / 7) % nBits;
        case 2: return (key / 11) % nBits;
        }
    }

public:
    BloomFilter(int n) : nBits(n)
    {
        data = std::vector<bool>(nBits, false);
    }

    bool lookup(int key)
    {
        return data[hash(0, key)] & data[hash(1, key)] & data[hash(2, key)];
    }

    void insert(int key)
    {
        data[hash(0, key)] = true;
        data[hash(1, key)] = true;
        data[hash(2, key)] = true;
    }
};
int main()
{
    BloomFilter table(7);
    table.insert(100);
    table.insert(54);
    table.insert(82);

    if (table.lookup(5))
        std::cout << "Element Found " << std::endl;
    else
        std::cout << "Element Not Found " << std::endl;

    if (table.lookup(50))
        std::cout << "Element Found " << std::endl;
    else
        std::cout << "Element Not Found " << std::endl;

    if (table.lookup(20))
        std::cout << "Element Found " << std::endl;
    else
        std::cout << "Element Not Found " << std::endl;

    if (table.lookup(54))
        std::cout << "Element Found " << std::endl;
    else
        std::cout << "Element Not Found " << std::endl;
}