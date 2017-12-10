#include<iostream>
using namespace std;
const int maxn = 1010;
int num[maxn];
int dp[maxn];//dp[i]代表以第i个数结尾的最大上升子序列的和
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        if (n == 0) break;
        for (int i = 0; i < n; i++) scanf("%d", &num[i]);
        memset(dp, 0, sizeof(dp));
        dp[0] = num[0];
        int ans = dp[0];
        for (int i = 1; i < n; i++)
        {
            dp[i] = num[i];
            for (int j = 0; j <= i; j++)
            {
                if (num[j] < num[i])
                {
                    if (dp[j] + num[i] > dp[i])
                    {
                        dp[i] = dp[j] + num[i];
                    }
                }
            }
            if (dp[i] > ans) ans = dp[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}