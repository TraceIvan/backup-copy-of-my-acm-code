//dp[i][0]:表示第i个取1时，s值最大（到i为止）
//dp[i][1] : 表示第i个取最大时，s值最大
//转移
//dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + abs(a[i - 1] - 1));
//dp[i][1] = max(dp[i - 1][0] + abs(a[i] - 1), dp[i - 1][1] + abs(a[i] - a[i - 1]));
//答案：max(dp[n][0], dp[n][1])
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 50010;
int dp[maxn][2];
int numb[maxn];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++) scanf("%d", &numb[i]);
        memset(dp, 0, sizeof(dp));
        dp[1][0] = 0;
        dp[1][1] = 0;
        for (int i = 2; i <= n; i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + abs(numb[i - 1] - 1));
            dp[i][1] = max(dp[i - 1][1]+abs(numb[i]-numb[i-1]), dp[i - 1][0] + abs(1 - numb[i]));
        }
        printf("%d\n", max(dp[n][0], dp[n][1]));
    }
    return 0;
}