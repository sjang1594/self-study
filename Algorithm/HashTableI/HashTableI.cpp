/* HashTableI.cpp
 *  Lookup (��ȸ) ex: Lookup Table (python: dict)
 *  Key & Value as Pair
 *  ���⿡���� Data Structure ���ٴ�, ��� ȿ�������� ã����?
 *  ���� ��, �������� ��ȭ ��ȣ�ΰ� �־���. �׷��� ��� ã���� �ִ���? ex: Divide & Conquer
 *
 * HashTable
 * ���� �˻��̶�� �ϸ�, N element �� ������ ������, �������� ã�µ� �ɸ��� �ð� O(n)
 * Binary Search Tree �� ����� �ϸ�, O(logN)
 * �ѹ� �˻��̶�� �ϸ�, BST �� ������ ������ �˻� Ƚ���� ���ٰ� �ϸ�? ���� �ʾ�
 * 
 * HashTable �� Main �ٽ�
 * Hasing -> ������ �����͸� ������ ������ ���� ������ ǥ��, �׸��� �� ���ڰ��� ����ؼ�
 * 1. Data �� ����
 * 2. ���ڿ� ����, ���� ������ ����
 * 
 * �̷��� �Լ��� ����ٰ� �ϸ�, Hash Function
 * std::map(), std::pair<>
 * 
*/

#include <iostream>
#include <vector>

using uint = unsigned int;

class HashMap
{
public:
    HashMap(size_t n)
    {
        // data initialization, set all element to be -1 with size n
        data = std::vector<int>(n, -1);
    }

    void insert(uint value)
    {
        int n = data.size();
        // Any Problems you can think of ?
       
        data[value % n] = value;
        std::cout << value << " Inserted " << std::endl;
    }

    // Lookup Function
    bool find(uint value)
    {
        int n = data.size();
        return (data[value % n] == value);
    }

    void remove(uint value)
    {
        int n = data.size();
        if (find(value))
        {
            data[value % n] = -1;
            std::cout << value << " Deleted " << std::endl;
        }
    }

private:
    std::vector<int> data;
};

int main()
{
    HashMap map(7);

    auto print = [&](int value) {
        if (map.find(value))
            std::cout << "From HashMap the value: " << value << "was found" << std::endl;
        else
            std::cout << "From HashMap the value: " << value << "was not found" << std::endl;
        std::cout << std::endl;
    };

    map.insert(2);
    map.insert(25);
    map.insert(10);

    print(25);
    map.insert(100);
    print(100);
    print(2);
    map.remove(25);

    return 0;
}