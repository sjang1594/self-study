#include <iostream>
using namespace std;

void Swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void Sort(int *numbers, int count)
{
    for (int i = 0; i < count; i++)
    {
        int best = i;
        for (int j = i + 1; j <count; j++)
        {
            if (numbers[j] < numbers[best])
                best = i;
        }
        if (i != best)
            Swap(numbers[i], numbers[best]);
    }
    Sort(numbers, 0);
}

void ChooseLotto(int numbers[])
{
    srand((unsigned)time(0));
    int count = 0;
    while(count != 6)
    {
        int randVal = (rand() % 45)  + 1;
        bool found = false;
        for (int i =0; i< count; i++)
        {
            if (numbers[i] == randVal)
            {
                found = true;
                break;
            }
        }
        if (found == false)
        {
            numbers[count] = randVal;
            count++;
        }
    }
}

int main()
{
    int a = 1;
    int b = 2;
    // 1) Swap Function
    Swap(a, b);

    // 2) Assending Order
    int numbers[6] = {1, 42, 3, 15, 5, 6};
    Sort(numbers, sizeof(numbers)/sizeof(int)); // sizeof(numbers) / sizeof(int)
    ChooseLotto(numbers);
    return 0;
}