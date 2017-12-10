#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;
const int maxa = 1100;
const int maxb = 15;
const int maxm = 1100;
const int maxn = 100050;
int n, m;
int dp[maxb][maxa];
const int INF = 0x7fffffff;
struct skill
{
    int k;
    int p;
}skills[maxm];
struct gg
{
    int a;
    int b;
}gw[maxn];
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &gw[i].a, &gw[i].b);
        }
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &skills[i].p, &skills[i].k);
        }
        for (int i = 0; i < maxb; i++)
        {
            for (int j = 0; j < maxa; j++) dp[i][j] = INF;
        }
        for (int i = 0; i <maxb; i++) dp[i][0] = 0;
        for (int b = 0; b <= 10; b++)
        {
            for (int s = 1; s <= m; s++)
            {
                int k = skills[s].k, p = skills[s].p;
                if (b >= k) continue;
                for (int a = 1; a <= 1000; a++)
                {
                    if (k - b >= a) dp[b][a] = min(dp[b][a],p);
                    else
                    {
                        dp[b][a] = min(dp[b][a], dp[b][a-(k-b)] + p);
                    }
                }
            }
        }
        long long ans = 0;
        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            if (dp[gw[i].b][gw[i].a] == INF)
            {
                flag = false;
                break;
            }
            ans += dp[gw[i].b][gw[i].a];
        }
        if(flag) printf("%lld\n", ans);
        else printf("-1\n");
    }
    return 0;
}