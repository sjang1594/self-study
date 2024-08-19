/* LongestCommonSubsequence(LCS) 
*  
*  Sequence 라는건 결국 어떠한 Pattern 문제를 해결하기 위한 알고리즘을 Dynamic Programming 으로 해결
*  문자열 검색, 비교, 문자열 재구성
* 
*  예를 들어서, git 같은 경우 (approximate string matching) 또는 Fuzzy String Matching 이 필요
* 
* ---------------------------------------------------------------------------------------------
*  Longest Common Subsequence 
* ---------------------------------------------------------------------------------------------
* 
*  Ex:
*       A  = "ALBOCNDGZEYSXTW"
*       B  = "12L45O78N90GE9876S5432T"
*  
*  여기에서의 Common Subsequence 는
*       A  = "A "L" B "O" C "N" D "G" Z "E" Y "S" X "T" W"
*       B  = "12 "L" 45 "O" 78 "N" 90 "G" "E" 9876 "S" 5432 "T" "
*  => LONGEST 가 LCS 의 값이다. LCS = 7
* 
*  알고리즘 순서부터 확인!
*  
*  1) A 또는 B 가 Empty 일 경우 케이스
*     - 둘다 Empty 일 경우
*       - A = "", B = "", LCS = 0
*     - 둘중 하나가 Empty 일 경우
*       - A = "A", B = "", LCS = 0
*       - A = "",  B = "BLAHBLAH", LCS = 0
* 
*  2) A 와 B 가 모두 하나의 문자로 구성된 경우
*     A = "A", B = "A", LCS = 1
*     A = "A", B = "B", LCS = 0
* 
*  3) A 는 한 문자이고, B 는 두문자로 구성된 경우
*     A = "A", B = "AB", LCS = 1
*     A = "A", B = "BB", LCS = 0
* 
*  4) A 와 B 가 모두 두문자로 구성되는 경우
*     A = "AA", B = "AA", LCS = 2
*     A = "BA", B = "AB", LCS = 1 
*     A = "AA", B = "BB", LSC = 0
*  
*  5) A 와 B 가 모두 세 문자로 구성된 경우
*     A = "ABA", B = "AAB", LCS = 2
*     A = "ABC", B = "BZC", LCS = 2
* 
*  6) A 와 B 가 모두 네 문자로 구성된 경우
*     A = AAAB, B = AAAA, LCS = 3 {"AAA_", "AAA_", "AAA_", "AA_A", "A_AA", "AAA_", "_AAA"} // 중복 문제
*     A = AZYB, B = YZBA, LCS = 2 {"_Z_B", "_ZB_", "__YB", "Y_B_"}
* 
*  문자열 길이 n 이라고 하면, 2^n 부분 집합처럼 나올수 있다.
* 
*  부분집합으로 한번 보자!
* 
*  A = "ABCX"               B = "ACY"
*  {A____}                   {A__}
*  {_B___}                   {_C_}
*  {___C_}                   {__Y}
*  {____C}
*  
*  {AB__}                    {AC_}
*  {A_C_}                    {A_Y}
*  {A__X}                    {_CY}
*  {_BC_}
*  {_B_C}
*  {__CX}
*                   
*  {ABC_}                    {ACY}
*  {AB_X}
*  {A_CX}
*  {_BCX}
* 
*  {ABCX}
* 
*  ----- 
*  알고리즘: 
*  1) 만약 i 가 A 의 길이보다 커지거나 또는 j 가 B 의 길이보다 커지면, 재귀 종료, 부분 시퀀스 길이 반환
*  2) 만약 A[i] = B[j], 즉 길이가 같다면, 부분 Sequence 길이를 1 만큼 증가하고, i, j +=1 
*  3) 길이가 같지 않다면 옵션
*     옵션1) i + 1 번째와 j 번째 문자 검사
*     옵션2) i 번째와 j+1 번째문자 검사
*     
*     이 때의 LCS 는 옵션 1 및 옵션 2의 최댓값이 같다.
* 
*  Brute Force
*  
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#define DEBUG 1
#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(X)
#endif

using namespace std;

vector<vector<pair<int, int>>> found;

int LCS_BruteForce(string A, string B, int i, int j, vector<pair<int, int>> subsequence)
{
    // Base
    if (i >= A.size() || j >= B.size())
    {
        found.push_back(subsequence);
        return subsequence.size();
    }

    // If two
    if (A[i] == B[j])
    {
        subsequence.push_back({ i, j });
        return LCS_BruteForce(A, B, i + 1, j + 1, subsequence);
    }

    return max(LCS_BruteForce(A, B, i + 1, j, subsequence), LCS_BruteForce(A, B, i, j + 1, subsequence));
}

void PrintSubsequence(string A, string B)
{
    sort(found.begin(), found.end(), [](auto a, auto b)
        {
            if (a.size() != b.size())
            {
                return a.size() < b.size();
            }

            return a < b;
        });

    found.erase(unique(found.begin(), found.end()), found.end());

    int previousSize = 0;
    for(auto subsequence : found)
    {
        if (subsequence.size() != previousSize)
        {
            previousSize = subsequence.size();
            PRINT("SIZE = " << previousSize << endl);
        }

        string a_seq(A.size(), '_');
        string b_seq(B.size(), '_');

        for (auto pair : subsequence)
        {
            a_seq[pair.first] = A[pair.first];
            b_seq[pair.second] = B[pair.second];
        }

        PRINT("\t" << a_seq << " " << b_seq << endl);
    }
}

const int UNKNOWN = -1;

int LCS_Memoization(string A, string B, int i, int j,
    vector<vector<int>>& memo)
{
    // 기저 조건 - 빈 문자열에 대해서는 0을 반환
    if (i == 0 || j == 0)
    {
        return 0;
    }

    // 두 문자열의 부분 문자열에 대해 결과가 저장되어 있으면 반환
    // Have we found a result for the prefixes of the two strings?
    if (memo[i - 1][j - 1] != UNKNOWN)
    {
        return memo[i - 1][j - 1];
    }

    // A와 B의 두 부분 문자열에서 맨 마지막 문자가 같은지 확인
    if (A[i - 1] == B[j - 1])
    {
        // 이 경우 A와 B의 부분 문자열에서 구한 LCS 길이는 각 부분 문자열에서 
        // 마지막 한 문자를 제외한 문자열로부터 구한 LCS 길이에 1을 더한 것과 같음

        memo[i - 1][j - 1] = 1 + LCS_Memoization(A, B, i - 1, j - 1, memo);

        // 테이블에 저장된 결과를 반환
        return memo[i - 1][j - 1];
    }

    // A와 B의 두 부분 문자열에서 맨 마지막 문자가 같지 않다면
    // A의 부분 문자열에서 마지막 문자를 제외한 것과 B의 부분 문자열에서 구한 LCS 길이,
    // B의 부분 문자열에서 마지막 문자를 제외한 것과 A의 부분 문자열에서 구한 LCS 길이 중
    // 최댓값을 선택하여 지정

    memo[i - 1][j - 1] = max(LCS_Memoization(A, B, i - 1, j, memo),
        LCS_Memoization(A, B, i, j - 1, memo));

    return memo[i - 1][j - 1];
}

string ReconstructLCS(vector<vector<int>> DP, string A, string B, int i, int j)
{
    if (i == 0 || j == 0)
    {
        return "";
    }

    if (A[i - 1] == B[j - 1])
    {
        return ReconstructLCS(DP, A, B, i - 1, j - 1) + A[i - 1];
    }
    else if (DP[i - 1][j] > DP[i][j - 1])
    {
        return ReconstructLCS(DP, A, B, i - 1, j);
    }
    else
    {
        return ReconstructLCS(DP, A, B, i, j - 1);
    }
}

string LCS_Tabulation(string A, string B)
{
    vector<vector<int>> DP(A.size() + 1, vector<int>(B.size() + 1));

    for (int i = 0; i <= A.size(); i++)
    {
        for (int j = 0; j <= B.size(); j++)
        {
            if (i == 0 || j == 0)
            {
                DP[i][j] = 0;
            }
            else if (A[i - 1] == B[j - 1])
            {
                DP[i][j] = DP[i - 1][j - 1] + 1;
            }
            else
            {
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
            }
        }
    }

    string lcs = ReconstructLCS(DP, A, B, A.size(), B.size());

    return lcs;
}

int main()
{
    string A, B;
    A = "AABCX";
    B = "ACYXB";
    {
        int LC = LCS_BruteForce(A, B, 0, 0, {});
    }
    {
        vector <vector<int>> memo(A.size(), vector<int>(B.size(), UNKNOWN));
        int LCS = LCS_Memoization(A, B, A.size(), B.size(), memo);
    }
    {
        string lcs = LCS_Tabulation(A, B);

        int LCS = lcs.size();
    }
    return 0;
}