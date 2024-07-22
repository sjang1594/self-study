/* Memoization.cpp 
*  (NOT Memorization)
* 
*  Fibonacci Problem (�������� Cache �Ǵ� �޸𸮿� ���� ���� ����)
*  - �� �ܰ迡�� �κй����� �ش��� ã���� �̸� �迭 ������ ĳ�ÿ� ����!
* 
*  Memoization : ��� ������ Ǯ��, ���� ����� ���� �޸𸮿� ���������ν� ������ ����� �ݺ� ������ �����ؼ�, ���� �ӵ��� ������ �ϴ� ���!
*  - ���⿡���� Cache ���ٰ� ������ �����ν�, ���ʿ��� ������ ���� 
* 
*  1. ������ Ư���� �����ϸ鼭, ���� �ٸ� ������ ���缺�� Ȱ���ϴ� ĳ�� ��� ����� ��� �Ҽ� �ִ�.
*   -> ���� �ǹ��� �κ� ���� �ع��� ��Ȯ�ϰ� ��ġ��Ű�鼭 ����! (���� �ٸ��ٸ�, �ߺ� ������ ���ټ� ����). �׸��� ��� State �� ���ؼ� ����� �ϸ鼭 ������ ���ʿ��ϰ� �ִ�.
*  2. ��� ������ ���� ������ �ʰ��ϱ� ���� �ʿ��� ��� �κ� ������ �ش��� ���� �Ҽ� �ִ�. 
*   -> Stack Overflow �� �߻� -> Recursive Method �� ������ ���� �� �ϳ�
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
