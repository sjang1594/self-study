/* Memoization.cpp 
*  (NOT Memorization)
* 
*  Fibonacci Problem (기존에는 Cache 또는 메모리에 저장 하지 않음)
*  - 각 단계에서 부분문제의 해담을 찾으면 이를 배열 구조의 캐시에 저장!
* 
*  Memoization : 어떠한 문제를 풀때, 이전 계산한 값을 메모리에 저장함으로써 동일한 계산의 반복 수행을 제거해서, 실행 속도를 빠르게 하는 기술!
*  - 여기에서는 Cache 에다가 저장을 함으로써, 불필요한 연산을 제거 
* 
*  1. 고유한 특성은 유지하면서, 서로 다른 상태의 유사성을 활용하는 캐시 사용 방식을 고안 할수 있다.
*   -> 같은 의미의 부분 문제 해법을 정확하게 일치시키면서 저장! (만약 다르다면, 중복 문제를 없앨수 없음). 그리고 모든 State 에 대해서 고려를 하면서 저장을 할필요하가 있다.
*  2. 사용 가능한 스택 공간을 초과하기 전에 필요한 모든 부분 문제의 해답을 누적 할수 있다. 
*   -> Stack Overflow 가 발생 -> Recursive Method 의 유일한 문제 중 하나
*/

#include <iostream>
#include <vector>
using namespace std;

const int UNKNOWN = -1;
const int MAX_SIZE = 100;

vector<int> memo(MAX_SIZE, UNKNOWN);

int Fibonacci(int n)
{
    if (n < 2)
        return n;

    if (memo[n] != UNKNOWN)
        return memo[n];

    int result = Fibonacci(n - 1) + Fibonacci(n - 2);
    memo[n] = result;
    return result;
}

vector<int> dp(100, -1);

int AnotherFibonacci(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;

    if (dp[n] != -1) return dp[n];
    dp[n] = AnotherFibonacci(n - 1) + AnotherFibonacci(n - 2);
    return dp[n];
}

int main()
{
    std::cout << "Hello World!\n";
}
