//DP 序列划分
#include<map>
#include<string>
#include<iostream>
#include<memory.h>
#include<algorithm>
using namespace std;
#define maxn 1020
int dp[maxn][maxn];
int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int k;
        cin >> k;
        string s;
        cin >> s;
        int l = s.length();
        int tl = l / k;
        map<char, int>m;
        int count = 0;
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < k; i++)
        {
            if (!m[s[i]])
            {
                m[s[i]] = 1;
                count++;
            }
        }
        for (int i = 0; i < k; i++) dp[0][i] = count;
        for (int j = 1; j<tl; j++)
        {
            m.clear();
            count = 0;
            for (int i = 0; i < k; i++)
            {
                if (!m[s[i + j*k]])
                {
                    m[s[i + j*k]] = 1;
                    count++;
                }
            }
            for (int i = 0; i < k; i++) dp[j][i] = l;
            for (int i = 0; i < k; i++)
            {
                for (int l = 0; l < k; l++)
                {
                    if (m[s[l + (j - 1)*k]] && (count == 1 || s[l + (j - 1)*k] != s[i + j*k]))
                    {//如果j-1段中第l个字母在第j段中出现过，并且第j段中字母种类只有一种或者有多种但最后一个字母不是它
                        dp[j][i] = min(dp[j][i], dp[j - 1][l] + count - 1);
                    }
                    else dp[j][i] = min(dp[j][i], dp[j - 1][l] + count);
                }
            }
        }
        int mincount = l;
        for (int i = 0; i < k; i++) mincount = min(mincount, dp[tl - 1][i]);
        cout << mincount << endl;
    }
    return 0;
}
//DP[i][j]代表前i段以第i段中的第j个字母结尾的最小cent数量。
//状态转移方程DP[i][j] = min(DP[i - 1][l] + centi - 1) 首尾可以合并
//DP[i][j] = min(DP[i - 1][l] + cent)首尾不可合并。
//l为枚举的第i - 1段第l个字母结尾。
//
//如何判断两个字段首尾字母是否可以合并？
//如果i - 1段的第l个字母在i段出现过，且i段最后一个字母不是它或者i段只有一个cent，则由于每段可以自由排列，我们只确定了每段的最后一个字母，所以完全可以判定合并了两段的首尾。