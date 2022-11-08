#include <iostream>
using namespace std;

// typename T 를 붙이면 '조커카드' (어떤  타입도 다 넣을수 있음)
// 그런데 무조건 typename 을 붙여야 하는건 아니다.
// template <> 안에 들어가는건 [골라줘야 하는 일종 목록]
template <typename T, int SIZE = 10>
class RandomBox
{
public:
    T GetRandomData()
    {
        int idx = rand() % SIZE;
        return _data[idx];
    }
public:
    T _data[SIZE];
};

// template 특수화
template <int SIZE>
class RandomBox<double, SIZE>
{
public:
    double GetRandomData()
    {
        int idx = rand() % SIZE;
        return _data[idx];
    }
public:
    double _data[SIZE];
};

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    RandomBox<int, 10> rb1;
    for(int i=0; i < 10; i++)
    {
        rb1._data[i] = i;
    }

    int value1 = rb1.GetRandomData();
    cout << value1;

    RandomBox<int, 20> rb2;
    for(int i=0; i < 10; i++)
    {
        rb2._data[i] = i + 0.5f;
    }
    int value2 = rb2.GetRandomData();
    cout << value2;

    RandomBox<double, 20>rb3;
    for(int i=0; i < 20; i++)
    {
        rb3._data[i] = i + 0.5;
    }
    int value3 = rb3.GetRandomData();
    cout << value3;
    return 0;
}