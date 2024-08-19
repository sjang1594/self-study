/* LongestCommonSubsequence(LCS) 
*  
*  Sequence ��°� �ᱹ ��� Pattern ������ �ذ��ϱ� ���� �˰����� Dynamic Programming ���� �ذ�
*  ���ڿ� �˻�, ��, ���ڿ� �籸��
* 
*  ���� ��, git ���� ��� (approximate string matching) �Ǵ� Fuzzy String Matching �� �ʿ�
* 
* ---------------------------------------------------------------------------------------------
*  Longest Common Subsequence 
* ---------------------------------------------------------------------------------------------
* 
*  Ex:
*       A  = "ALBOCNDGZEYSXTW"
*       B  = "12L45O78N90GE9876S5432T"
*  
*  ���⿡���� Common Subsequence ��
*       A  = "A "L" B "O" C "N" D "G" Z "E" Y "S" X "T" W"
*       B  = "12 "L" 45 "O" 78 "N" 90 "G" "E" 9876 "S" 5432 "T" "
*  => LONGEST �� LCS �� ���̴�. LCS = 7
* 
*  �˰��� �������� Ȯ��!
*  
*  1) A �Ǵ� B �� Empty �� ��� ���̽�
*     - �Ѵ� Empty �� ���
*       - A = "", B = "", LCS = 0
*     - ���� �ϳ��� Empty �� ���
*       - A = "A", B = "", LCS = 0
*       - A = "",  B = "BLAHBLAH", LCS = 0
* 
*  2) A �� B �� ��� �ϳ��� ���ڷ� ������ ���
*     A = "A", B = "A", LCS = 1
*     A = "A", B = "B", LCS = 0
* 
*  3) A �� �� �����̰�, B �� �ι��ڷ� ������ ���
*     A = "A", B = "AB", LCS = 1
*     A = "A", B = "BB", LCS = 0
* 
*  4) A �� B �� ��� �ι��ڷ� �����Ǵ� ���
*     A = "AA", B = "AA", LCS = 2
*     A = "BA", B = "AB", LCS = 1 
*     A = "AA", B = "BB", LSC = 0
*  
*  5) A �� B �� ��� �� ���ڷ� ������ ���
*     A = "ABA", B = "AAB", LCS = 2
*     A = "ABC", B = "BZC", LCS = 2
* 
*  6) A �� B �� ��� �� ���ڷ� ������ ���
*     A = AAAB, B = AAAA, LCS = 3 {"AAA_", "AAA_", "AAA_", "AA_A", "A_AA", "AAA_", "_AAA"} // �ߺ� ����
*     A = AZYB, B = YZBA, LCS = 2 {"_Z_B", "_ZB_", "__YB", "Y_B_"}
* 
*  ���ڿ� ���� n �̶�� �ϸ�, 2^n �κ� ����ó�� ���ü� �ִ�.
* 
*  �κ��������� �ѹ� ����!
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
*  �˰���: 
*  1) ���� i �� A �� ���̺��� Ŀ���ų� �Ǵ� j �� B �� ���̺��� Ŀ����, ��� ����, �κ� ������ ���� ��ȯ
*  2) ���� A[i] = B[j], �� ���̰� ���ٸ�, �κ� Sequence ���̸� 1 ��ŭ �����ϰ�, i, j +=1 
*  3) ���̰� ���� �ʴٸ� �ɼ�
*     �ɼ�1) i + 1 ��°�� j ��° ���� �˻�
*     �ɼ�2) i ��°�� j+1 ��°���� �˻�
*     
*     �� ���� LCS �� �ɼ� 1 �� �ɼ� 2�� �ִ��� ����.
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
    // ���� ���� - �� ���ڿ��� ���ؼ��� 0�� ��ȯ
    if (i == 0 || j == 0)
    {
        return 0;
    }

    // �� ���ڿ��� �κ� ���ڿ��� ���� ����� ����Ǿ� ������ ��ȯ
    // Have we found a result for the prefixes of the two strings?
    if (memo[i - 1][j - 1] != UNKNOWN)
    {
        return memo[i - 1][j - 1];
    }

    // A�� B�� �� �κ� ���ڿ����� �� ������ ���ڰ� ������ Ȯ��
    if (A[i - 1] == B[j - 1])
    {
        // �� ��� A�� B�� �κ� ���ڿ����� ���� LCS ���̴� �� �κ� ���ڿ����� 
        // ������ �� ���ڸ� ������ ���ڿ��κ��� ���� LCS ���̿� 1�� ���� �Ͱ� ����

        memo[i - 1][j - 1] = 1 + LCS_Memoization(A, B, i - 1, j - 1, memo);

        // ���̺� ����� ����� ��ȯ
        return memo[i - 1][j - 1];
    }

    // A�� B�� �� �κ� ���ڿ����� �� ������ ���ڰ� ���� �ʴٸ�
    // A�� �κ� ���ڿ����� ������ ���ڸ� ������ �Ͱ� B�� �κ� ���ڿ����� ���� LCS ����,
    // B�� �κ� ���ڿ����� ������ ���ڸ� ������ �Ͱ� A�� �κ� ���ڿ����� ���� LCS ���� ��
    // �ִ��� �����Ͽ� ����

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