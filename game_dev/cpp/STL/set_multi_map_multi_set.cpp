#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
using namespace std;

int main()
{
    // (key value) --> map
    // (key) --> set (단독적으로 사용)
    set<int> s;
    
    // 넣고
    // 빼고
    // 찾고 
    // 순회하고

    // 넣고
    s.insert(10);
    s.insert(40);
    s.insert(50);

    // 빼고
    s.erase(40);

    // 찾고
    set<int>::iterator findIt = s.find(50);
    if(findIt == s.end())
    {
        cout << "not found" << endl;
    }
    else
    {
        cout << "Found" << endl;    
    }
    
    // 순회
    for(set<int>::iterator it = s.begin(); it != s.end(); ++it)
    {
        cout << (*it) << endl;
    }

    cout << "-----" <<endl;

    // 중복키를 허용하는건 --> multimap / multiset
    multimap<int, int> mm;

    // 넣고
    mm.insert(make_pair(1, 100));
    mm.insert(make_pair(1, 200));
    mm.insert(make_pair(1, 300));
    mm.insert(make_pair(2, 400));
    mm.insert(make_pair(2, 500));

    // mm[1] = 500; 막혀 있음

    // 빼고
    unsigned int count = mm.erase(1); // 1 로 되어있는 key 가 사라짐 (count = 3)

    // 찾고
    multimap<int, int>::iterator itFind = mm.find(1);
    if (itFind != mm.end())
        mm.erase(itFind);

    // 순회
    multimap<int, int>::iterator itBegin = mm.lower_bound(1);
    multimap<int, int>::iterator itEnd = mm.upper_bound(1);

    pair<multimap<int, int>::iterator, multimap<int, int>::iterator> itPair;
    itPair = mm.equal_range(1);

    for (multimap<int, int>::iterator it=itPair.first; it != itPair.second; ++it)
    {
        cout << it->first << " " << it->second << endl;
    }
    
    for (multimap<int, int>::iterator it=itBegin; it != itEnd; ++it)
    {
        cout << it->first << " " << it->second << endl;
    }

    // 모든 순회
    for (multimap<int, int>::iterator it=mm.begin(); it != mm.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }

    // multiset
    multiset<int> ms;
    ms.insert(100);
    ms.insert(100);
    ms.insert(100);
    ms.insert(200);
    ms.insert(200);

    // 찾고
    multiset<int>::iterator findIt2 = ms.find(100);
    pair<multiset<int>::iterator, multiset<int>::iterator> itPair2;
    itPair2 = ms.equal_range(100);

    for(multiset<int>::iterator it = itPair2.first; it!=itPair2.second; ++it)
    {
        cout << (*it) << endl;
    }

    multiset<int>::iterator itBegin2 = ms.lower_bound(1);
    multiset<int>::iterator itEnd2 = ms.upper_bound(1);
    for (multiset<int>::iterator it=itBegin2; it != itEnd2; ++it)
    {
        cout << *it << endl;
    }
    return 0;
}