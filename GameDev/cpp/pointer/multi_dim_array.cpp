#include <iostream>
using namespace std;

// Multi-dimensional Array

int main()
{
    // [1] [1] [5] [2] [2] << 1 층
    // [4] [2] [3] [4] [1] << 0 층

    int apartment[2][5] = {{4, 2, 3, 4, 1},
                           {1, 1, 5, 2, 2}};

    for (int floor=0; floor < 2; floor++)
    {
        for(int room=0; room < 5; room++){
            int num = apartment[floor][room];
            cout << num << endl;
        }
        cout << endl;
    }

    return 0;
}