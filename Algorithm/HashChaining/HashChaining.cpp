/* HashChaining.cpp
* 
* HashChaining 은 결국, Hash (key) 값이 동일한게 존재 한다고 했을시에, 즉 중복을 허용한다고 했을때에, 그 Hash (key) 와 다른값을 저장
* LoadFactor = # of key / size of hashtable
*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using uint = unsigned int;

class HashMap
{
public:
    HashMap(size_t n)
    {
        data.resize(n);
    }

    void insert(uint value)
    {
        int n = data.size();
        data[value % n].push_back(value);
        std::cout << value << " Inserted " << std::endl;
    }

    // Lookup Function
    bool find(uint value)
    {
        int n = data.size();
        std::list<int>& entries = data[value % n];
        return std::find(entries.begin(), entries.end(), value) != entries.end();
    }

    void remove(uint value)
    {
        int n = data.size();
        std::list<int>& entries = data[value % n];
        auto iter = std::find(entries.begin(), entries.end(), value);
        if (iter != entries.end())
        {
            entries.erase(iter);
            std::cout << value << " Deleted " << std::endl;
        }
    }

private:
    std::vector<std::list<int>> data;
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
