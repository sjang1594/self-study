// SubsetSumTabulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<bool>> SubsetSum_Tabulation(vector<int>& set)
{
    int maxSum = 0;
    for (int i = 0; i < set.size(); i++)
    {
        maxSum += set[i];
    }

    vector<vector<bool>> DP(set.size() + 1, vector<bool>(maxSum + 1, false));

    for (int i = 0; i < set.size(); i++)
    {
        DP[i][0] = true;
    }

    for (int i = 1; i <= set.size(); i++)
    {
        for (int sum = 1; sum <= maxSum; sum++)
        {
            if (sum < set[i - 1])
            {
                DP[i][sum] = DP[i - 1][sum];
            }

            else
            {
                DP[i][sum] = DP[i - 1][sum] || DP[i - 1][sum - set[i - 1]];
            }
        }
    }

    return DP;
}


int main()
{
    vector<int> set = { 16, 1058, 22, 13, 46, 55, 3, 92, 47, 7, 98, 367, 807, 106, 333, 85, 577, 9, 3059 };
    int target = 6799;
    sort(set.begin(), set.end());

    vector<vector<bool>> DP = SubsetSum_Tabulation(set);
    bool found = DP[set.size()][target];
}
