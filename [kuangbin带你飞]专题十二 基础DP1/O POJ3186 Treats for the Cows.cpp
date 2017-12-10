#include<iostream>
#include<memory.h>
#include<algorithm>
using namespace std;
const int maxn = 2010;
int num[maxn];
int dp[maxn][maxn];//[i][j]表示从第i到第j最大的收益。
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &num[i]);
            dp[i][i] =num[i]* n;
        }
        for (int l=2;l<=n;l++)
        {
            for (int j = 1; j+l-1 <= n; j++)
            {
                dp[j][j + l - 1] = max(dp[j + 1][j + l - 1] + num[j] * (n - l + 1), dp[j][j + l - 2] + num[j+l-1] * (n - l + 1));
            }
        }
        printf("%d\n", dp[1][n]);
    }
    return 0;
}