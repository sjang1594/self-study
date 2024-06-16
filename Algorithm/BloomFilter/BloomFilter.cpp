/* BloomFilter.cpp
*  Non-deterministic
*  
*  False Negative, False Positive => 즉 특정 원소가 존재한다는 긍정의 답변의 결과로선, 있을수도 있고 없을수도 있고.
*  하지만, 특정원소가 존재하지 않는다는 부정적인 답변의 결과로서는 이 원소는 확실이 없다.
* 
*  왜 불확실한건데요?
*  만약 boolean table 안에 있는 Element 들이 전부다 1 로 된다고하면, 내가 진짜 찾고자 하는 Lookup table 에서 무조건 True 를 반환하니까.
*  그래서 Likely 를 Check 하는거와 같다고 생각하면된다.
* 
*  Bloom Filter 자체는 Element 를 저장하지 않으며, Boolean 값만 존재한다.
* 
*  삽입:
*  HashFunction 에서 값을 계산하고, Boolean Table 안에서, 이 Hash 의 Index 를 1 로 설정
* 
*  Lookup 함수에서는, Boolean Table 안에, 해당되는 Index 가 1 인지 아닌지를 체크. 만약 1 이면 Return True
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