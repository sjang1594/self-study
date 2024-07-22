/* Tabulation 
*  
*  Top-Down 형식이 아닌, Bottom-Up 형식을 계산을 푼다. 
*   이 때 어떤 Tabular Data 로 저장을 하는데, 모든 부분 문제의 상태의 해답을 저장을 하고, 기존에는 재귀적으로 표현했기때문에, 상태를 표현하기 위해서는 개념적으로 어렵다.
* 
*  ex: Lookup table
* 
*  Subset Sum Problem: Dynamic Programming
*  이문제의 Core Part: 양의 정수로 이루어진 집합의 부분집합 중 원소의 합이 X 와 같은 부분 집합이 존재 !?
*  
*  왜 동적 계획법으로 푸는지?
*  1. 부분집합이 더 작은 부분집합의 집합으로 구성될수 있으니까, Optimal Substructure 의 속성을 만족
*  2. 부분집합이 중복되어 나타 낼수 있고, 중북되는 부분 문제의 속성을 만족 할수 있다.
* 
*  문제: 동전 거스름 돈 최적화!
*  제품의 가격이 7500 이고, 고객이 10000 원을 지불했을때, 2500 의 거스름돈을 꺼낼수 있는지?
* 
*  현재 금전 등록기에는 1000 원 지폐 5장과, 500 원 동전 4 개, 100 원 15 개 
*  가능한수
*  * 1000 원 2 개, 500 원 1개
*  * 1000 원 2 개 100 원 5 개
*  * 1000 원 1 개 500 원 3개
*  * 1000 원 1 개 500 원 2개, 100 원 5개
*  * 1000 원 1 개 500 원 1개, 100 원 10개
*  * 1000 원 1 개, 100 원 15 개
*  * 500 원 4개, 100 원 5 개
*  * 500 원 3개, 100 원 10개
*  * 500 원 2개, 100 원 15 개
* 
*  만약 SubSet 이 {13, 79, 45, 29} 가 있다면
*  {}
*  {13}, {79}, {45}, {29}
*  {13, 79}, {13, 45}, {13, 29}, {79, 45}, {79, 29}, {45, 29},
*  { 13, 79, 45 }, { 13, 79, 29 }, { 13, 45, 29 }, { 79, 45, 29 }
*  {13, 79, 45, 29}
* 
*  0 으로 이루어질수 있는 집합: 1
*  1 : 0 을 포함한 자기자신 2
*  2 : 4 (ex: {}, {13}, {79} {13, 79})
*  3 : 8 (ex: {}, {13}, {79}, {45},  {13, 79}, {13, 45}, {79, 45}, { 13, 79, 45 })
*  4 : 16
* 
*  원소의 개수 n 인 집합인 전체의 부분집합의 개수는 2^n 알수 있다.
* 
*  결국 동적계획법에서 풀수있는 조건은
*  1. optimal substructure
*  2. overlapping problem
* 
*  그리고 3 가지의 방법으로 전수조사, 백트래킹, 메모이제이션, 타뷸레이션
*  전수조사는 (brute force) 로 푸는 방법
*  일단 단순하며, 정답을 비교도 쉽게 할수 있고, 부분문제를 시각화해서, 모든 문제의 조건을 만족하는 해를 바로 풀수 있다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#pragma region Fibonacci
int Fibonacci(int n)
{
	vector<int> DP(n + 1, 0);
	DP[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		DP[i] = DP[i - 1] + DP[i - 2];
	}

	return DP[n];
}
#pragma endregion Fibonacci

#define DEBUG 0
#if DEBUG
#define PRINT(X) cerr << x
#else
#define PRINT(X)
#endif

void GetAllSubsets(vector<int> set, vector<int> subset, int index, vector<vector<vector<int>>>& allsubset)
{
	// Base If
	if (index == set.size())
	{
		allsubset[subset.size()].push_back(subset);
		return;
	}

	GetAllSubsets(set, subset, index + 1, allsubset);

	subset.push_back(set[index]);
	GetAllSubsets(set, subset, index + 1, allsubset);
}

bool SubsetSum_BruteForce(vector<int> set, int target)
{
	vector<vector<vector<int>>> allSubset(set.size() + 1);
	GetAllSubsets(set, {}, 0, allSubset);

	for (size_t size = 0; size <= set.size(); size++)
	{
		for (auto subset : allSubset[size])
		{
			PRINT("\t{ ");
		
			int sum = 0;
			for (auto number : subset)
			{
				sum += number;
				PRINT(number << " ");
			}
			PRINT("}= " << sum << endl);
			if (sum == target)
				return true;
		}
	}
	return false;
}

int main()
{
	vector<int> set = { 13, 79, 45, 29 };
	int target = 58;

	bool found = SubsetSum_BruteForce(set, target);
	if (found)
		cout << target << " Found" << std::endl;
	else
		cout << target << " Not Found " << std::endl;
}