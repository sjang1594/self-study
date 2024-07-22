/* Tabulation 
*  
*  Top-Down ������ �ƴ�, Bottom-Up ������ ����� Ǭ��. 
*   �� �� � Tabular Data �� ������ �ϴµ�, ��� �κ� ������ ������ �ش��� ������ �ϰ�, �������� ��������� ǥ���߱⶧����, ���¸� ǥ���ϱ� ���ؼ��� ���������� ��ƴ�.
* 
*  ex: Lookup table
* 
*  Subset Sum Problem: Dynamic Programming
*  �̹����� Core Part: ���� ������ �̷���� ������ �κ����� �� ������ ���� X �� ���� �κ� ������ ���� !?
*  
*  �� ���� ��ȹ������ Ǫ����?
*  1. �κ������� �� ���� �κ������� �������� �����ɼ� �����ϱ�, Optimal Substructure �� �Ӽ��� ����
*  2. �κ������� �ߺ��Ǿ� ��Ÿ ���� �ְ�, �ߺϵǴ� �κ� ������ �Ӽ��� ���� �Ҽ� �ִ�.
* 
*  ����: ���� �Ž��� �� ����ȭ!
*  ��ǰ�� ������ 7500 �̰�, ���� 10000 ���� ����������, 2500 �� �Ž������� ������ �ִ���?
* 
*  ���� ���� ��ϱ⿡�� 1000 �� ���� 5���, 500 �� ���� 4 ��, 100 �� 15 �� 
*  �����Ѽ�
*  * 1000 �� 2 ��, 500 �� 1��
*  * 1000 �� 2 �� 100 �� 5 ��
*  * 1000 �� 1 �� 500 �� 3��
*  * 1000 �� 1 �� 500 �� 2��, 100 �� 5��
*  * 1000 �� 1 �� 500 �� 1��, 100 �� 10��
*  * 1000 �� 1 ��, 100 �� 15 ��
*  * 500 �� 4��, 100 �� 5 ��
*  * 500 �� 3��, 100 �� 10��
*  * 500 �� 2��, 100 �� 15 ��
* 
*  ���� SubSet �� {13, 79, 45, 29} �� �ִٸ�
*  {}
*  {13}, {79}, {45}, {29}
*  {13, 79}, {13, 45}, {13, 29}, {79, 45}, {79, 29}, {45, 29},
*  { 13, 79, 45 }, { 13, 79, 29 }, { 13, 45, 29 }, { 79, 45, 29 }
*  {13, 79, 45, 29}
* 
*  0 ���� �̷������ �ִ� ����: 1
*  1 : 0 �� ������ �ڱ��ڽ� 2
*  2 : 4 (ex: {}, {13}, {79} {13, 79})
*  3 : 8 (ex: {}, {13}, {79}, {45},  {13, 79}, {13, 45}, {79, 45}, { 13, 79, 45 })
*  4 : 16
* 
*  ������ ���� n �� ������ ��ü�� �κ������� ������ 2^n �˼� �ִ�.
* 
*  �ᱹ ������ȹ������ Ǯ���ִ� ������
*  1. optimal substructure
*  2. overlapping problem
* 
*  �׸��� 3 ������ ������� ��������, ��Ʈ��ŷ, �޸������̼�, Ÿ�淹�̼�
*  ��������� (brute force) �� Ǫ�� ���
*  �ϴ� �ܼ��ϸ�, ������ �񱳵� ���� �Ҽ� �ְ�, �κй����� �ð�ȭ�ؼ�, ��� ������ ������ �����ϴ� �ظ� �ٷ� Ǯ�� �ִ�.
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