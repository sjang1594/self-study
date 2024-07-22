// MemoizationII

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool SubsetSum_BackTracking(vector<int>& set, int sum, int i)
{
    // Base 
    if (sum == 0)
        return true;

    // if the subseet size is bigger than its size 
    // or if the target subset sum is larger than target, skip
    if (i == set.size() || set[i] > sum)
        return false;
    
    //     6076 -7 
    // 1    
    return SubsetSum_BackTracking(set, sum - set[i], i + 1) || SubsetSum_BackTracking(set, sum, i + 1);
}

int main()
{
    vector<int> set = { 16, 1058, 22, 13, 46, 55, 3, 92 ,47, 7, 98, 367, 807, 106, 333, 85, 577, 9, 3059 };
    int target = 6076;

    std::sort(set.begin(), set.end());
    bool found;
    found = SubsetSum_BackTracking(set, target, 0);
    return 0;
}