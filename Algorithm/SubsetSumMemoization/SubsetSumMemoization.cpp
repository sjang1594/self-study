/* SubsetSumMemoization
*  - BackTracking 이 최선의 방법은 만약 Target 값이 매우 크다면, 계속 Recursive 하게 돌거고, 모든 Subset 을 체크한다.
* 
*  - Memoization
*  1. 메모아이제이션을 위한 캐시 사용하기
*     - 정수 인덱스를 사용하는 일반 배열
*     - 프로그래밍 언어에서 제공하는 해시 기능을 사용하여 상태를 표현한 해시 테이블 또는 해시맵
*     - 자체적으로 생성한 해시 함수를 이용하여 상태를 표현한 해시 테이블 또는 해시 맵
*   
*  2. 위의 내용을 사용할때의 주의점
*     - 정수 인덱스를 사용하는 배열과 벡터는 일반적으로 맵보다 빠르다. 맵은 이미 캐시가 존재하는지를 확인 하기 위해 주어진키에 어디에 위치해있는지를 찾아야한다.
*     - 상태를 정수로 표현할수 있다고 하더라도, 그값의 status 종류가 많거나, 너무 크게 나타날 경우, 실제 필요한 메모리보다 훨씬 큰 크기의 배열을 만들어 사용해야하므로 비합리적
*     - std::unordered_map 과 같은 hash table 은 일반적인 map / dictionary 구조보다 빠르게 키를 찾고 검색할수있다. (배열보다는 느리다)
*     - std::map 은 키로 사용할수 있는 자료형 측면에서 std::unordered_map 보다 훨신 자유도가 높다.
* 
*  3. 캐시를 사용할때의 주으점
*     - 상태가 똑같은거에대해서 조심해야한다.
*     - 캐시에 저장된 값을 잘못 참조 하는 경우가 있으면 안된다. 
* 
*  set => {1, 5, 6, 2, 3, 9}
*  상태
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
