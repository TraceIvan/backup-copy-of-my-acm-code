#include<iostream>
#include<algorithm>
using namespace std;
int n;
const int maxn = 1010;
char mp[maxn][maxn];
int dp[maxn][maxn];//dp[i][j]表示左下角为(i,j)的对称矩阵的维数。可以从dp[i-1][j+1]转换
int main()
{
    while (~scanf("%d", &n))
    {
        if (n == 0)break;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++) cin >> mp[i][j];
        }
        int ans = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = n; j >= 1; --j)
            {
                dp[i][j] = 1;
                if (i == 1 || j == n) continue;
                int ll = dp[i - 1][j + 1];
                for (int k = 1; k <= ll; k++)
                {
                    if (mp[i - k][j] == mp[i][j + k]) dp[i][j]++;
                    else break;
                }
                ans = max(ans, dp[i][j]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}