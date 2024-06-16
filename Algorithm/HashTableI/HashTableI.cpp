/* HashTableI.cpp
 *  Lookup (조회) ex: Lookup Table (python: dict)
 *  Key & Value as Pair
 *  여기에서는 Data Structure 보다는, 어떻게 효과적으로 찾는지?
 *  예를 들어서, 옛날에는 전화 번호부가 있었다. 그러면 어떻게 찾을수 있는지? ex: Divide & Conquer
 *
 * HashTable
 * 선형 검색이라고 하면, N element 가 사전에 있으면, 선형으로 찾는데 걸리는 시간 O(n)
 * Binary Search Tree 로 계산을 하면, O(logN)
 * 한번 검색이라고 하면, BST 가 좋지만 여러번 검색 횟수가 들어간다고 하면? 좋지 않아
 * 
 * HashTable 의 Main 핵심
 * Hasing -> 각각의 데이터를 가급적 고유한 숫자 값으로 표현, 그리고 이 숫자값을 사용해서
 * 1. Data 의 유뮤
 * 2. 숫자에 따른, 원본 데이터 추출
 * 
 * 이런걸 함수로 만든다고 하면, Hash Function
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