#include <iostream>
using namespace std;

// Multi-dimensional Array

int main() {
    // [1] [1] [5] [2] [2] << 1 층
    // [4] [2] [3] [4] [1] << 0 층

    int apartment[2][5] = {{4, 2, 3, 4, 1},
                           {1, 1, 5, 2, 2}};

    for (int floor = 0; floor < 2; floor++) {
        for (int room = 0; room < 5; room++) {
            int num = apartment[floor][room];
            cout << num << endl;
        }
        cout << endl;
    }

    int arr2[2][2] = {{1, 2},
                      {3, 4}};

    // 주소2 []
    // 주소1[주소2]
    // pp [주소1]
    // 2차원 array vs multiple pointer
    //int* pp = arr2;

    // Type name[개수]
    // [1][2]
    // [주소]
    int(*p2)[2] = arr2;
    cout << (*p2)[0] << endl;
    cout << (*p2)[1] << endl;
    cout << (*(p2+1))[0] << endl;
    cout << (*(p2+1))[1] << endl;
    cout << p2[0][0] << endl;
    cout << p2[0][1] << endl;
    cout << p2[1][0] << endl;
    cout << p2[1][1] << endl;

    return 0;
}