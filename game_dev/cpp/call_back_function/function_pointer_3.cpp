#include <iostream>
#include <array>
#include <functional>

using namespace std;

bool isEven(const int& number)
{
    if (number % 2 == 0) return true;
    else return false;
}

bool isOdd(const int& number)
{
    if (number % 2 == 1) return true;
    else return false;
}

using check_fcn_t = bool(*)(const int&);

void printNumbers(const array<int, 10>& my_array, check_fcn_t check_fcn = isEven)
{
    for (auto element : my_array)
    {
        if (check_fcn(element) == true) cout << element;
    }
    cout << endl;
}

void printNumbers(const array<int, 10>& my_array, std::function<bool(const int&)> check_fcn = isEven)
{
    for (auto element : my_array)
    {
        if (check_fcn(element) == true) cout << element;
    }
    cout << endl;
}

int main()
{
    std::array<int, 10> my_array{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    
    std::function<bool(const int&)> fcnptr = isEven;

    printNumbers(my_array, isEven);
    printNumbers(my_array, isOdd);

    fcnptr = isOdd;
    printNumbers(my_array, fcnptr);
    return 0;
}
