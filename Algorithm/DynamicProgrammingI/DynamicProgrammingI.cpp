/* DynamicProgrammingI 
*  
* =================================================================
*  ���� ��ȹ�� ���� ����
*  1. ���� (Ư�� ������ �����ϴ� �������� ���� �Ǵ� ������ ���� ���ϱ�)
*  2. ���ڿ��� Sequence (Huffman Coding & DNA Sequence)
*       - edit distance
*       - longest common subsequence
*       - longest increasing subsequence
*  3. Graph (�ִ� ��� ����)
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
*  �׷��� �̹����� Recursion ���� ǥ���Ǹ� Ǯ �� �ִ�. (�� ���⼭, Base �� ������ F(0) = 0, F(1) = 1 �� �����ȴ�)
*  
*  Tree ����Ȯ�� ** => Top Down Solution
*  
*  �� Tree �� Top Down �� ������ Ǯ�� ����, Substructure �Ǵ� Subproblem ���� ���������� �ִ�. 
*  
*  Substructure �� �����ų� SubProblem ���� Ǯ��, �ߺ��Ǵ� ������ �Ҽ� �ִ�.
*  ��: F(2) �� F(4) �� F(3) �� ���ϴ� �������� F(4) = F(3) + F(2) �̰� F(3) �� F(2) + F(1) Ǯ����.
*  -> �̷��� ������ Overlapping subproblem �̶�� �Ѵ�.
* 
*  ��Ȱ ���� VS ���� ��ȹ��
*  -> ��Ȱ ���� ���������� ��ü ������ �������� ������ �κк��� Ǯ����, ������ȹ���� ���� �κй����� �ݺ������� ��Ÿ����.
*  
*  �׸��� ������ ���� ������ �ϱ� ������, ������� �Ȱ��� ����� ������ ���ؼ� �ظ� ���Ѵ�.
*  ��: F(2) �� �ظ� ���ؾ��� ���, F(4) �Ǵ� F(3) �߿��� ������� ���� ���� �ϸ� �ȴ�.
*  -> �̷��� ������ Ư¡�� Optimal Substructure �̶�� �Ѵ�.
* 
*  ��, ��ü ������ ���� �����ذ� �κй����� �������� �������� ǥ���� ����!
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
