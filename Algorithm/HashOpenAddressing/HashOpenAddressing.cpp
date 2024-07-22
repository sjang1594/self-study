/* HashOpenAddressing.cpp : This file contains the 'main' function.Program execution begins and ends there.
 To protect the collision -> Open Addressing
 List 로 저장하는게 아닌, 모든 원소를 Hash Table 내부안에 저장
 즉 HashTable 의 크기가 반드시 데이터 개수보다 커야함

 Load Factor # of number / HashTable Size

 1. Linear Probing
     이미 채워져있으면, hash(x) 에 해당되는 hash(x+1) or hash(x+2)
     Data Clustering:   결국엔 처음에 채워져있는 값들의 군집과 새롭게 넣어질 군집들이 생성되고, 계속 집어 넣었더라고 한다고 하면, 검색 속도는 증가
                        또는 Data 의 분포에 따른 새로운 값들의 추가

 2. Quadratic Probing
     Linear Probing 의 단점을 개선. 방식은 동일 위와 동일하지만, Data 의 분포를 여러곳으로 배치
     hash(x) 가 있다고 하면, hash(x+1^2), hash(x+2^2) 으로 이동. 

 3. Cuckoo hasing
     [] [A] [] [] 
     [] [] [] [B]

     // insert C
     [] [C] [] [] Hashtable 1 에 HashFunction B 가 C
     [] [ ] [] [A]

     [] [B] [] []
     [] [ ] [] [C]


    
     O(1) 의 시간 복잡도를 만족하는 Hasing 기법
     똑같은 HashTable 의 사이즈를 가지고 있고, 서로 다른 Hash Function 을 가지고 있다.
     모든 원소는 두 해시테이블 중에 하나 있을수 있고, 그 위치는 HashTable 을 가르키고 있는 Hash Function 에 따라 다르다.'
     
     정리
     1. 원소가 두 해시 Table 중 어디든 저장 가능
     2. 원소가 나중에 다른위치로 이동할수 있다.
     3. Rehashing 을 하지 않는 한, 최초 삽인된 위치에서 다른위치로 이동 불가능
     4. 순환과정이 나왔을때에는, 무조건 Rehasing 을 다시해야함
*/

#include <iostream>
#include <vector>

class HashMap
{
public:
    HashMap(int n) : size(n)
    {
        hashTable1 = std::vector<int>(size, -1);
        hashTable2 = std::vector<int>(size, -1);
    }

    void insert(int key)
    {
        insert_impl(key, 0, 1);
    }

    void erase(int key)
    {
        std::vector<int>::iterator pos = lookup(key);
        if (pos != hashTable2.end())
        {
            *pos = -1;
            std::cout << "Key is deleted: " << std::endl;
        }
        else
        {
            std::cout << "Key not Found" << std::endl;
        }
    }

    void print()
    {
        std::cout << "Index: ";
        for (int i = 0; i < size; i++)
            std::cout << i << "\t";
        std::cout << std::endl;

        std::cout << "HashTable 1: ";
        for (auto& i : hashTable1)
            std::cout << i << "\t";
        std::cout << std::endl;

        std::cout << "HashTable 2: ";
        for (auto& i : hashTable2)
            std::cout << i << "\t";
        std::cout << std::endl;
    }


private:
    // Hasing Function 1: return the index of key
    int hash1(int key) const { return key % size; }
    // Hashing Function 2
    int hash2(int key) const { return (key / size) % size; }

    // LookUp Function
    std::vector<int>::iterator lookup(int key)
    {
        const int hash_value1 = hash1(key);
        if (hashTable1[hash_value1] == key)
        {
            std::cout << "Found in HashTable 1: " << key << std::endl;
            return hashTable1.begin() + hash_value1;
        }

        const int hash_value2 = hash2(key);
        if (hashTable2[hash_value2] == key)
        {
            std::cout << "Found in HashTable 2: " << key << std::endl;
            return hashTable1.begin() + hash_value2;
        }

        return hashTable2.end();
    }

    // insert implemented
    void insert_impl(int key, int cnt, int table)
    {
        if(cnt >= size)
        {
            std::cout << "Rehashing needed because of circular dependency " << std::endl;
            return;
        }

        if (table == 1)
        {
            int hash = hash1(key);
            if (hashTable1[hash] == -1)
            {
                hashTable1[hash] = key;
            }
            else
            {
                // Old key swap, and recursively give it to table 2
                const int old = hashTable1[hash];
                hashTable1[hash] = key;
                insert_impl(old, cnt + 1, 2);
            }
        }   
        else
        {
            // Table 2
            int hash = hash2(key);
            if (hashTable2[hash] == -1)
            {
                hashTable2[hash] = key;
            }
            else
            {
                const int old = hashTable2[hash];
                hashTable2[hash] = key;
                insert_impl(old, cnt + 1, 1);
            }
        }
    }

    std::vector<int> hashTable1;
    std::vector<int> hashTable2;
    int size;
};

int main()
{
    HashMap map(7);
    map.print();
    std::cout << std::endl;

    map.insert(10);
    map.insert(20);
    map.insert(30);
    map.print();
    std::cout << std::endl;

    map.insert(104);
    map.insert(2);
    map.insert(70);
    map.insert(9);
    map.insert(90);
    map.insert(2);
    std::cout << std::endl;

    map.print();
    std::cout << std::endl;

    map.insert(14);
    return 0;
}