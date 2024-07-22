/* DynamicProgrammingI 
*  
* =================================================================
*  동적 계획법 문제 예시
*  1. 조합 (특정 기준을 만족하는 시퀀스의 조합 또는 순열의 개수 구하기)
*  2. 문자열과 Sequence (Huffman Coding & DNA Sequence)
*       - edit distance
*       - longest common subsequence
*       - longest increasing subsequence
*  3. Graph (최단 경로 문제)
*       - ?
*  4. Machine Learning 
*  =================================================================
* 
*  Fibonacci Sequence
*  { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 ...}
*  
*  F(0) = 0;
*  F(1) = 1
*  ...
*  F(n) = F(n-1) + F(n-2)
* 
*  그래서 이문제는 Recursion 으로 표현되며 풀 수 있다. (즉 여기서, Base 의 문제는 F(0) = 0, F(1) = 1 로 구성된다)
*  
*  Tree 구조확인 ** => Top Down Solution
*  
*  즉 Tree 로 Top Down 의 형식을 풀다 보면, Substructure 또는 Subproblem 으로 나누어질수 있다. 
*  
*  Substructure 을 나누거나 SubProblem 으로 풀때, 중복되는 연산을 할수 있다.
*  예: F(2) 는 F(4) 와 F(3) 를 구하는 과정에서 F(4) = F(3) + F(2) 이고 F(3) 는 F(2) + F(1) 풀린다.
*  -> 이러한 문제를 Overlapping subproblem 이라고 한다.
* 
*  분활 정복 VS 동적 계획법
*  -> 분활 정복 같은문제는 전체 문제가 독립적인 문제로 부분별로 풀지만, 동적계획법은 같은 부분문제가 반복적으로 나타낸다.
*  
*  그리고 동일한 연산 문제를 하기 때문에, 상관없이 똑같은 방식의 연산을 통해서 해를 구한다.
*  예: F(2) 의 해를 구해야할 경우, F(4) 또는 F(3) 중에서 상관없이 연산 수행 하면 된다.
*  -> 이러한 문제의 특징을 Optimal Substructure 이라고 한다.
* 
*  즉, 전체 문제에 대한 최적해가 부분문제의 최적해의 조합으로 표현이 가능!
*/

#include <iostream>

int Fibonacci(int n)
{
    if (n < 2)
        return n;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}


int main()
{
    int n;
    std::cout << "Enter Any Number you want to compute a finbonnaci number " << std::endl;
    std::cin >> n;
    std::cout << Fibonacci(n) << std::endl;
    return 0;
}
