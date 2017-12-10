#include<iostream>
#include<algorithm>
#include<memory.h>
#include<cstring>
using namespace std;
const int maxn = 1010;
const int MOD = 1e9 + 7;
long long dp[2][maxn * 9];
int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;//避免n==1时讨论前导零
        for (int i = 0; i <= 9; i++) dp[1][i] = 1;
        for (int i = 2; i <= n; i++)
        {//对于第i个数
            for (int k = 0; k <= n * 9; k++)
            {//和为k
                dp[i % 2][k] = 0;
                for (int j = 0; j <= min(k, 9); j++)
                {//第i个数的取值
                    dp[i%2][k] = (dp[i%2][k]+dp[(i-1)%2][k - j]) % MOD;
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i <= n * 9; i++)
        {
            ans = (ans + dp[n % 2][i] * (dp[n % 2][i] - dp[(n - 1) % 2][i])) % MOD;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}