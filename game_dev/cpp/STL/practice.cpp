#include <iostream>
#include <vector>

using namespace std;
int SIZE = 100;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<int> v;

    for(int i = 0; i < SIZE; i++)
    {
        int num = rand() % 100;
        v.push_back(num);
    }

    // Q1) number 라는 숫자가 벡터에 체크하는 기능 (bool, 첫 등장 iterator)
    {
        int number = 50;
        bool found = false;
        vector<int>::iterator it = v.end();

        for (unsigned int i = 0; i < v.size(); i++)
        {
            int data = v[i];
            if (data == number)
            {
                found = true;
                it = v.begin() + i;
                break;
            }
        }
    }

    // Q2) 11 로 나눠지는 숫자가 벡터에 있는지 체크하는 기능
    {
        bool found = false;
        vector<int>::iterator it = v.end();
        for (unsigned int i = 0; i < v.size(); i++)
        {
            int data = v[i];
            if (data % 11 == 0)
            {
                found = true;
                it = v.begin() + i;
                break;
            }
        }
    }

    // Q3) 홀수인 숫자의 개수는? (count)
    {
        int count = 0;
        for (unsigned int i = 0; i < v.size(); i++)
        {
            int data = v[i];
            if (data % 2 != 0)
            {
                count++;
            }
        }
    }

    // Q4) 벡터에 들어가 있는 모든 숫자들에 3을 곱해주세요!
    {
        for (unsigned int i = 0; i < v.size(); i++)
        {
            v[i] *= 3;
        }
    }


}