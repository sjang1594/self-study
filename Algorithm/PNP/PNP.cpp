/* P vs NP
* 
*  P ��� ������, Polynomial Time ���� �ش��� ���Ҽ� �ִ�. ���� �� BST �Ǵ� �ٸ� Hashing Algorithm ���� ���
*  O(n), O(n^2) , O(logN) ������ ǥ���� �����ϴ�. => Polynomial Time (Reasonably Fast)
*  ���� S(tep) = f(N) N: size
*  Ex: Bipartite Matching, Finding Primes, Multiplication, Sorting, Sudoku (�̹� ä�����ִ°� �˻�)
* 
*  NP (Nondeterminisitic Polynomial Time) �̶�� ������� ���׽ð� ������ �� �ݴ�� ���� ��ó�� ǥ���ϱⰡ ��ƴ�.
*  �׸��� �ｼ Problems "Vertifiable" in polynomial time. (Reasonable Okay)
*  Ex: Sudoku (���� ��, ������ִ°� �׽�Ʈ �Ѵٸ�)
* 
*  �� ("Does being able to quickly recognize correct answers mean there's also a quick way to find them (P))(NP)
* 
*  �Ǵ��ϴ� ����� "�־��� ������ �ַ�� ������ Ŭ���� P �� ���Ѵٴ°��� �ش� ������ ���� �ð��� �ַ����� �����ϴ°�?" �� ��������ϸ�, 
*  P= NP ��� ������ ������Ű�°��� ���ؼ� ������ �ʿ��ϴ�. (�ݴ�� �ƴ϶�� �Ѵٸ� P != NP ��� �Ѵ�.)
*  
*  NPC(NP Complete): Hardest Problem in NP.
*  Ex: Chess. Protein Folding, Super Mario
* 
*  EXP, NP - Hard
* 
*  --------------------------------------------------
*  0-1 Knapsak Problem
*  * �뷮 ������ �ִ� �賶�� ���� �ٸ� ���ݰ� ���Ը� ���� ���� ������ �־��� ���, 
*    �賶�� ���� �뷮�� ���� �����鼭 ���濡 ���� ���ǵ��� ���� ���� �ִ밡 �Ǵ� ���� ������ �����̳�?
*  
*  �κ� ������ �� ����, ���� i ��° ���� Set[i] 
*  1. ������ ���� �κ������� �տ� set[i] �� ���Ѵ�.
*  2. ������ ���� �κ������� ���� �״�� ����
*  
*  DP(i, x) �������, DP(i, x+set[i]) ���� �κ� ������ �տ� set[i] �� ���� ��ġ��.
* 
*  i ��°�� ������ ���԰� w, v �� �����̶��
*  1. ������ ���õ� ���ǵ��� ���Կ� w �� ���� ����� �ִ� �뷮���� ���ų� �������, ������ ���õ� ���ǵ��� ���� �տ� w �� ���Ѵ�.
*  2. ������ ���õ� ���ǵ��� ���� ���� �״�� ����
*  
*  ������ v �̰� ���԰� w �� (i + 1) ��° ������ ����� ��, ���õ� ���ǵ��� ���� ���� W �� ��� �ִ� ������ ���� (���� state)
*  1. i ��° ���ǿ� ���� ���õ� ���ǵ��� ���� ���� W �ΰ���� �ִ� ������
*  2. i ��° ���ǿ� ���� ���õ� ���ǵ��� ���� ���� W - w �� ����� �ִ� ���� �տ� v �� ���Ѱ�
*  
*  �� i ��° ���ǰ� ���� w �� ����Ҷ��� �ִ� �������� ���� ���Կ� ���� i -1 ��° ����ϰų�, ���� State �� �ʵ�� ���� �տ� ���� ������ ������ ���Ѱ� �� ���� .
* 
// How to solve this naively for optimal substructure
// Items \ Knapsack capcity
//            |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |
// empty      |   0   |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
// v1=2,w1=3  |   0   |   0   |   0   |   2   |   2   |   2   |   2   |   2   |
// v2=2,w2=1  |   0   |   2   |   2   |   2   |   4   |   4   |   4   |   4   |
// v3=4,w3=3  |   0   |   2   |   2   |   4   |   6   |   6   |   6   |   6   |
// v4=5,w4=4  |   0   |   2   |   2   |   4   |   6   |   7   |   7   |   9   |
// v5=3,w5=2  |   0   |   2   |   3   |   5   |   6   |   7   |   9   |   10  |
* https://github.com/MonaAhmed810/0-1-Knapsack-Problem-with-Genetic-Algorithms/blob/master/main.cpp
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int KnapSack01(int W, int wt[], int val[], int n)
{
	vector<vector<int>> K(n + 1, vector<int>(W + 1));

	// Build Table
	for (int i = 0; i <= n; i++)
	{
		for (int w = 0; w <= W; w++)
		{
			if (i == 0 || w == 0)
				K[i][w] = 0;
			// Check if the weight of the current item is less than or equal to current capacity
			else if (wt[i - 1] <= w)
				// w - wt[i-1] ���� �ִ� �հ�, ���� State �� ���� ����
				K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][W]);
			else
				K[i][w] = K[i - 1][w];
		}
	}

	return K[n][W];
}

int main()
{
	int profit[] = { 60, 100, 120 };
	int weight[] = { 10, 20, 30 };
	int W = 50; 
	int n = sizeof(profit) / sizeof(profit[0]);
	cout << KnapSack01(W, weight, profit, n);
	return 0;
}
