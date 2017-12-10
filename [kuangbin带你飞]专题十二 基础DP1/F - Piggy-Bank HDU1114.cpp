#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 510;
const int maxw = 10010;
const int maxp = 50010;
const int INF = 0x7fffffff;

int dp[maxw];
struct coin
{
    int p;
    int w;
}coins[maxn];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int e, f;
        scanf("%d%d", &e, &f);
        int totalw = f - e;//装硬币的重量
        int minwight = maxw;
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &coins[i].p, &coins[i].w);
            if (coins[i].w < minwight) minwight = coins[i].w;
        }
        if (minwight > totalw)
        {
            printf("This is impossible.\n");
            continue;
        }
        for (int i = 0; i <= totalw; i++) dp[i] = INF;
        dp[0] = 0;
        for (int i = 0; i < n; i++)
        {
            for (int v = 0; v <= totalw; v++)
            {
                if (v - coins[i].w >= 0&& dp[v - coins[i].w]!=INF)
                {
                    /*if(dp[v]>=0)dp[v] = min(dp[v], dp[v - coins[i].w] + coins[i].p);
                    else dp[v] = dp[v - coins[i].w] + coins[i].p;*/
                    dp[v] = min(dp[v], dp[v - coins[i].w] + coins[i].p);
                }
            }
        }
        if(dp[totalw]<INF)printf("The minimum amount of money in the piggy-bank is %d.\n", dp[totalw]);
        else
        {
            printf("This is impossible.\n");
        }
    }
    return 0;
}