/* SubsetSumMemoization
*  - BackTracking �� �ּ��� ����� ���� Target ���� �ſ� ũ�ٸ�, ��� Recursive �ϰ� ���Ű�, ��� Subset �� üũ�Ѵ�.
* 
*  - Memoization
*  1. �޸�������̼��� ���� ĳ�� ����ϱ�
*     - ���� �ε����� ����ϴ� �Ϲ� �迭
*     - ���α׷��� ���� �����ϴ� �ؽ� ����� ����Ͽ� ���¸� ǥ���� �ؽ� ���̺� �Ǵ� �ؽø�
*     - ��ü������ ������ �ؽ� �Լ��� �̿��Ͽ� ���¸� ǥ���� �ؽ� ���̺� �Ǵ� �ؽ� ��
*   
*  2. ���� ������ ����Ҷ��� ������
*     - ���� �ε����� ����ϴ� �迭�� ���ʹ� �Ϲ������� �ʺ��� ������. ���� �̹� ĳ�ð� �����ϴ����� Ȯ�� �ϱ� ���� �־���Ű�� ��� ��ġ���ִ����� ã�ƾ��Ѵ�.
*     - ���¸� ������ ǥ���Ҽ� �ִٰ� �ϴ���, �װ��� status ������ ���ų�, �ʹ� ũ�� ��Ÿ�� ���, ���� �ʿ��� �޸𸮺��� �ξ� ū ũ���� �迭�� ����� ����ؾ��ϹǷ� ���ո���
*     - std::unordered_map �� ���� hash table �� �Ϲ����� map / dictionary �������� ������ Ű�� ã�� �˻��Ҽ��ִ�. (�迭���ٴ� ������)
*     - std::map �� Ű�� ����Ҽ� �ִ� �ڷ��� ���鿡�� std::unordered_map ���� �ν� �������� ����.
* 
*  3. ĳ�ø� ����Ҷ��� ������
*     - ���°� �Ȱ����ſ����ؼ� �����ؾ��Ѵ�.
*     - ĳ�ÿ� ����� ���� �߸� ���� �ϴ� ��찡 ������ �ȵȴ�. 
* 
*  set => {1, 5, 6, 2, 3, 9}
*  ����
*  Subset => { 1, 5 } => 6 + 2
*  Subset => { 6 } => 6 + 2
*  Subset => { 1, 2, 3 } => 6
*   
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int UNKNOWN = -1;

bool SubsetSum_Memoization(vector<int>& set, int sum, int i, vector<vector<int>>& cache)
{
    if (sum == 0)
        return true;

    if (i == set.size() || set[i] > sum)
        return false;

    // Check if the state is in the cache
    if (cache[i][sum] == UNKNOWN)
    {
        bool append = SubsetSum_Memoization(set, sum - set[i], i + 1, cache);
        bool ignore = SubsetSum_Memoization(set, sum, i + 1, cache);

        cache[i][sum] = append || ignore;
    }

    return cache[i][sum];
}

int main()
{
    vector<int> set = { 16, 1058, 22, 13, 46, 55, 3, 92, 47, 7, 98, 367, 807, 106, 333, 85, 577, 9, 3059 };
    int target = 6799;
    sort(set.begin(), set.end());

    vector<vector<int>> memo(set.size(), vector<int>(7000, UNKNOWN));
    bool found = SubsetSum_Memoization(set, target, 0, memo);
    return 0;
}
