
// smart pointer 
#include <iostream>
using namespace std;

void doSomething(int& lref)
{
    cout << "L-value ref" << endl;
}

void doSomething(int&& ref)
{
    cout << "R-value ref" << endl;
}

int getResult()
{
    return 100 * 100;
}

int main()
{
    int x = 5;
    int y = getResult();
    const int cx = 6;
    const int cy = getResult();

    // L-value Reference
    int &lr1 = x;           // Modifiable l-values
    // int& lr2 = cx;       // only readable -> const
    // int& lr3 = 5;        // r value

    const int& lr4 = x;     // Modifiable l-values
    const int& lr5 = cx;    // Non-modifiable l-values
    const int& lr6 = 5;     // R-values (symbolics constant)

    // R-value references
    //int&& rr3 = x;          // Modifiable l-values
    //int&& rr2 = cx;         // Non-modifiable l-values
    int&& rr3 = 5;          // R-values (symbolics constant)
    
    // 곧 사라질 애들... --> rvalue

    doSomething(x);
    //doSomething(cx);
    doSomething(5); 
    doSomething(getResult());
    return 0;
}