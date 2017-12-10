//dp[i] = (dp[i - 1] * 2 + 1) % MOD; ，该元素首次出现
//dp[i] = (dp[i - 1] * 2 - dp[pos[val[i]] - 1] + MOD) % MOD; ，该元素非首次出现
#include<iostream>
using namespace std;
const int maxn = 100010;
const int MOD = 1e9 + 7;
int num[maxn];
long long dp[maxn];
int vis[maxn];
int main()
{
    int n;
    while (~scanf("%d",&n))
    {
        for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
        memset(dp, 0, sizeof(dp));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++)
        {
            if (!vis[num[i]])//  如果该元素没有出现过
            {//  前i个组成的序列加上与第i个组合的序列再加上第i个单独作为序列
                dp[i] =( 2 * dp[i - 1]+1) % MOD;
            }
            else dp[i] = (dp[i - 1] * 2 - dp[vis[num[i]]-1]+MOD)%MOD;//  前i个组成的序列加上与第i个组合的序列减去以这个元素为结尾的次数
            vis[num[i]] = i;
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}