/* HashOpenAddressing.cpp : This file contains the 'main' function.Program execution begins and ends there.
 To protect the collision -> Open Addressing
 List �� �����ϴ°� �ƴ�, ��� ���Ҹ� Hash Table ���ξȿ� ����
 �� HashTable �� ũ�Ⱑ �ݵ�� ������ �������� Ŀ����

 Load Factor # of number / HashTable Size

 1. Linear Probing
     �̹� ä����������, hash(x) �� �ش�Ǵ� hash(x+1) or hash(x+2)
     Data Clustering:   �ᱹ�� ó���� ä�����ִ� ������ ������ ���Ӱ� �־��� �������� �����ǰ�, ��� ���� �־������ �Ѵٰ� �ϸ�, �˻� �ӵ��� ����
                        �Ǵ� Data �� ������ ���� ���ο� ������ �߰�

 2. Quadratic Probing
     Linear Probing �� ������ ����. ����� ���� ���� ����������, Data �� ������ ���������� ��ġ
     hash(x) �� �ִٰ� �ϸ�, hash(x+1^2), hash(x+2^2) ���� �̵�. 

 3. Cuckoo hasing
     [] [A] [] [] 
     [] [] [] [B]

     // insert C
     [] [C] [] [] Hashtable 1 �� HashFunction B �� C
     [] [ ] [] [A]

     [] [B] [] []
     [] [ ] [] [C]


    
     O(1) �� �ð� ���⵵�� �����ϴ� Hasing ���
     �Ȱ��� HashTable �� ����� ������ �ְ�, ���� �ٸ� Hash Function �� ������ �ִ�.
     ��� ���Ҵ� �� �ؽ����̺� �߿� �ϳ� ������ �ְ�, �� ��ġ�� HashTable �� ����Ű�� �ִ� Hash Function �� ���� �ٸ���.'
     
     ����
     1. ���Ұ� �� �ؽ� Table �� ���� ���� ����
     2. ���Ұ� ���߿� �ٸ���ġ�� �̵��Ҽ� �ִ�.
     3. Rehashing �� ���� �ʴ� ��, ���� ���ε� ��ġ���� �ٸ���ġ�� �̵� �Ұ���
     4. ��ȯ������ ������������, ������ Rehasing �� �ٽ��ؾ���
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