/* P vs NP
* 
*  P 라는 문제는, Polynomial Time 내에 해답을 구할수 있다. 예를 들어서 BST 또는 다른 Hashing Algorithm 같은 경우
*  O(n), O(n^2) , O(logN) 등으로 표현이 가능하다. => Polynomial Time (Reasonably Fast)
*  공식 S(tep) = f(N) N: size
*  Ex: Bipartite Matching, Finding Primes, Multiplication, Sorting, Sudoku (이미 채워져있는걸 검사)
* 
*  NP (Nondeterminisitic Polynomial Time) 이라는 비결정적 다항시간 문제는 그 반대로 위의 식처럼 표현하기가 어렵다.
*  그말은 즉슨 Problems "Vertifiable" in polynomial time. (Reasonable Okay)
*  Ex: Sudoku (예를 들어서, 비워져있는걸 테스트 한다면)
* 
*  즉 ("Does being able to quickly recognize correct answers mean there's also a quick way to find them (P))(NP)
* 
*  판단하는 방법은 "주어진 문제의 솔루션 검증이 클래스 P 에 속한다는것이 해당 문제의 다항 시간의 솔류션을 보장하는가?" 를 물어봐야하며, 
*  P= NP 라는 조건을 만족시키는가에 대해서 질문이 필요하다. (반대로 아니라고 한다면 P != NP 라고 한다.)
*  
*  NPC(NP Complete): Hardest Problem in NP.
*  Ex: Chess. Protein Folding, Super Mario
* 
*  EXP, NP - Hard
* 
*  --------------------------------------------------
*  0-1 Knapsak Problem
*  * 용량 제한이 있는 배낭과 서로 다른 가격과 무게를 갖는 여러 물건이 주어질 경우, 
*    배낭의 제한 용량을 넘지 않으면서 가방에 넣은 물건들의 가격 합이 최대가 되는 물건 조합이 무엇이냐?
*  
*  부분 집합의 합 문제, 집합 i 번째 원소 Set[i] 
*  1. 이전에 구한 부분집합의 합에 set[i] 를 더한다.
*  2. 이전에 구한 부분집합의 합을 그대로 유지
*  
*  DP(i, x) 이전행과, DP(i, x+set[i]) 같은 부분 집합의 합에 set[i] 를 더한 위치값.
* 
*  i 번째가 물건의 무게가 w, v 가 가격이라면
*  1. 기존에 선택된 물건들의 무게에 w 를 더한 결과가 최대 용량보다 같거나 작을경우, 기존에 선택된 물건들의 가격 합에 w 를 더한다.
*  2. 기존에 선택된 물건들의 가격 합을 그대로 유지
*  
*  가격이 v 이고 무게가 w 인 (i + 1) 번째 물건을 고려할 때, 선택된 물건들의 무게 합이 W 인 경우 최대 가격의 합은 (다음 state)
*  1. i 번째 물건에 대해 선택된 물건들의 무게 합이 W 인경우의 최대 가격합
*  2. i 번째 물건에 대해 선택된 물건들의 무게 합이 W - w 인 경우의 최대 가격 합에 v 를 더한값
*  
*  즉 i 번째 물건과 무게 w 를 고려할때의 최대 가격합은 같은 무게에 대해 i -1 번째 고려하거나, 이전 State 의 초디대 가격 합에 현재 물건의 가격을 더한것 과 같다 .
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
				// w - wt[i-1] 이전 최대 합과, 이전 State 의 무게 상태
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
