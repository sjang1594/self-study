#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>

using namespace std;

class Player
{
public:
    Player() : _playerId(0) {}
    Player(int playerId) : _playerId(playerId){}

public:
    int _playerId;
};

template<typename T1, typename T2>
struct Pair
{
    T1 t1;
    T2 t2;
};

int main()
{
    // 연관 container
    // 예) ID = 2 만 플레이어 가 (ID = 1 만 Player)를 공격하고 싶어요
    // Q) ID = 1 만인 Player 를 찾아주세요
    // A) vector 를 사용하면, 찾기 어렵다. 한땀 한땀 loop 을 사용해서 찾아야 한다.

    // ex) vector 로 구현했을때
    // vector<int> v;  
    // bool found = false;
    // for(int i = 0; i < v.size(); i++)
    // {
    //     if (v[i]->_playerId = 10000)
    //     {
    //         found = true;
    //         break;
    //     }
    // }

    // vector, list 의 치명적인 단점
    // -> 원하는 조건에 해당하는 데이터를 빠르게 찾을수 [없다]

    // map : 균형 이진 트리 (AVL)
    // - 노드 기반
    class Node
    {
    public:
        Node*   _left;
        Node*   _right;
        // Data
        pair<int, Player*> _data;
        //int     _key;
        //Player* _value;
    };

    srand(static_cast<unsigned int>(time(nullptr)));
    // (Key, Value)
    map<int, int> m;

    // 10 만명
    for(int i = 0; i < 100000; i++)
    {
        m.insert(pair<int, int>(i, i * 100));
    }

    // 5 만명 퇴장
    for(int i = 0; i < 50000; i++)
    {
        int randomValue = rand() % 50000;
        // Erase by key
        m.erase(randomValue);
    }

    // 삭제
    unsigned int count = 0;
    count = m.erase(10000); // count 1 
    count = m.erase(10000); // count 0

    // insert 
    pair<map<int, int>::iterator, bool> ok;
    ok = m.insert(make_pair(1, 100));
    ok = m.insert(make_pair(1, 200)); // 무시 

    ok.first;
    ok.second;

    // Q) ID = 1 만인 Player 를 찾고 싶다!
    // A) 매우 빠르게 찾을 수 있음
    map<int, int>::iterator findit = m.find(10000);
    if (findit != m.end())
    {
        cout << "found" << endl;
    }
    else
    {
        cout << "not found" << endl;
    }

    // map 순회
    for(map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
    {
        pair<const int, int>& p = (*it);
        //int key = p.first;
        //int value = p.second;
        
        int key = it->first;
        int value = it->second;
    }

    // 없으면 추가, 있으면 수정
    map<int, int>::iterator findIt = m.find(1000);
    if (findit != m.end())
    {
        findIt->second = 200;
    }
    else
    {
        m.insert(make_pair(1000, 1000));
    }

    // 없으면 추가 있으면 수정 v2
    m[5] = 500;
    m.clear();

    // [] 연산자 사용할 때 주의
    // 대입을 하지 않더라도 (key/value) 형태의 데이터가 추가된다!
    for(int i=0; i <10; i++)
    {
        cout << m[i] << endl;
    }

    // 기본적으로 값을 0 으로 설정 (타입 별로)

    return 0;
}