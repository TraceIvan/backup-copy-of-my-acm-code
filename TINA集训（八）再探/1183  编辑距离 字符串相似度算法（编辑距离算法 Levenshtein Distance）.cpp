#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1005;
char s1[maxn];
char s2[maxn];
int dp[maxn][maxn];
int main()
{
    while (~scanf("%s%s", s1+1, s2+1))
    {

        int ln = strlen(s1+1);
        int lm = strlen(s2 + 1);
        for (int i = 0; i <= lm; i++) dp[0][i] = i;
        for (int i = 0; i <= lm; i++) dp[i][0] = i;
        for (int i = 1; i <= ln; i++)
        {
            for (int j = 1; j <= lm; j++)
            {
                int t = (s1[i] == s2[j] ? 0 : 1);
                dp[i][j] = min(dp[i - 1][j] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j - 1]+t));
            }
        }
        printf("%d\n", dp[ln][lm]);
    }
    return 0;
}