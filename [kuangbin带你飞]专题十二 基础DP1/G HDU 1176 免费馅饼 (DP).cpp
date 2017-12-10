#include<iostream>
#include<cstdio>
#include<memory.h>
#include<algorithm>
using namespace std;
int n;
const int maxn = 100010;
const int maxt = 100010;
const int INF = 0x7fffffff;
int dp[maxt][12];
int main()
{
    while (~scanf("%d", &n))
    {
        if (n == 0)break;
        memset(dp,0, sizeof(dp));
        int maxtt = 0;
        for (int i = 0; i < n; i++)
        {
            int x, t;
            scanf("%d%d", &x, &t);
            dp[t][x]++;
            if (t > maxtt) maxtt=t;
        }
        for (int i = maxtt-1; i >= 0; i--)
        {
            for (int st = 0; st <= 10; st++)
            {
                if (st == 0) dp[i][st] += max(dp[i + 1][st], dp[i + 1][st + 1]);
                else if(st==10)dp[i][st] += max(dp[i + 1][st], dp[i + 1][st - 1]);
                else dp[i][st] += max(dp[i + 1][st - 1], max(dp[i + 1][st], dp[i + 1][st + 1]));
            }
        }
        printf("%d\n", dp[0][5]);
    }
    return 0;
}