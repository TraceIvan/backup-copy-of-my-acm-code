#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MOD = 1e9 + 7;
long long dp[1005][1005];
int main()
{
    int t;
    scanf("%d", &t);
    int n, m;
    while (t--)
    {
        scanf("%d%d", &n, &m);
        long long ans = 0;
        if (m == n)
        {
            ans = 1;
            printf("%I64d\n", ans);
        }
        else if (n == 1) printf("%d\n", m);
        else if (m == 1) printf("%d\n", n);
        else
        {
            int c,r;
            if(m>n)
            {
                c = m - n + 1;
                r = n;
            }
            else
            {
                c = n - m + 1;
                r = m;
            }
            for (int i = 1; i<=r; i++)
            {
                for (int j = 1; j <= c; j++)
                {
                    if (i == 1 || j == 1) dp[i][j] = 1;
                    else dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
                }
            }
            for (int i = 1; i <= c; i++) ans = (ans + dp[r][i]) % MOD;
            printf("%I64d\n", ans);
        }
    }
    return 0;
}