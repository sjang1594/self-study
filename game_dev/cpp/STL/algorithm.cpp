#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int SIZE = 100;
int main()
{
    // 자료구조 (데이터를 저장하는 구조)
    // 알고리즘 (데이터를 어떻게 사용할것 인가?)

    // find
    // find_if
    // count
    // count_if
    // all_of
    // any_of
    // none_of
    // for_each
    // remove_if
    
    // from practice.cpp
    vector<int> v;
    
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < SIZE; i++)
    {
        int num = rand() % 100;
        v.push_back(num);        
    }

    // Q1)
    {
        int num = 50;
        vector<int>::iterator findIt = std::find(v.begin(), v.end(), num);
        if (findIt == v.end())
        {
            cout << "Not Found" << endl;
        }
        else
        {
            cout << "Found" << endl;
        }
    }

    // Q2)
    {
        struct CanDivideBy11
        {
            bool operator()(int n)
            {
                return (n % 11) == 0;
            }
        };

        vector<int>::iterator findIt = std::find_if(v.begin(), v.end(), CanDivideBy11());
        if (findIt == v.end())
        {
            cout << "Not Found" << endl;
        }
        else
        {
            cout << "Found" << endl;
        }
    }

    // Q2) v2
    {
        // 일회성 함수 사용
        vector<int>::iterator itFind = std::find_if(v.begin(), v.end(), [](int n) {return (n % 11) == 0; });
        if (itFind == v.end())
        {
            cout << "Not Found" << endl;
        }
        else
        {
            cout << "Found" << endl;
        }
    }

    // Q3)
    {
        struct IsOdd
        {
            bool operator()(int n)
            {
                return (n % 2) != 0;
            }
        };
        int n = std::count_if(v.begin(), v.end(), IsOdd());

        // 모든 데이터가 만족 하는 조건
        bool b1 = std::all_of(v.begin(), v.end(), IsOdd()); // 모든 데이터가 홀수야?
        bool b2 = std::any_of(v.begin(), v.end(), IsOdd()); // 홀수 데이터가 하나라도 있어?
        bool b3 = std::none_of(v.begin(), v.end(), IsOdd()); // 모든 데이터가 홀수가 아니야?
    }

    // Q4)
    {
        struct MultiplyByThree
        {
            bool operator()(int &n)
            {
                return n = n * 3;
            }
        };

        std::for_each(v.begin(), v.end(), MultiplyByThree());
    }

    // remove & remove_if --> 살짝 다르게 동작
    // 홀수인 데이터를 일괄 삭제
    {
        // for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        // {
        //     if((*it % 2) != 0)
        //         v.erase(it);
        // } 큰일남

        v.clear();
        
        v.push_back(1);
        v.push_back(4);
        v.push_back(3);
        v.push_back(5);
        v.push_back(8);
        v.push_back(2);

        std::remove(v.begin(), v.end(), 4);
        vector<int>::iterator it = std::remove_if(v.begin(), v.end(), [](int n) {return (n % 11) == 0;});
        // 데이터를 삭제를 했는데, 변경한게 다르다?

        // 1 4 3 5 8 2
        // 4 8 2 5 8 2
        // 4 8 2      5 8 2 //
        // 필요한 데이터만 남겨두는거에 더 가깝다
        v.erase(it, v.end());

        // v.erase(std::remove_if(v.begin(), v.end(), [](int n) {return (n % 11) == 0;}), v.end());
    }

    return 0; 
}