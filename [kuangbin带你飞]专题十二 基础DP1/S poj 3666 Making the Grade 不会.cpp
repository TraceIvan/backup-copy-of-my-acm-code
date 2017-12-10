#include <iostream>
#include <string.h>
#include <math.h>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <set>
#include <stdio.h>
using namespace std;
#define LL long long
#define pi acos(-1.0)
const int mod = 1e9 + 7;
const int INF = 1E15;
const double eqs = 1e-9;
const int MAXN = 2000 + 10;
LL a[MAXN], dp[MAXN][MAXN], b[MAXN];
LL Abs(LL x)
{
    return x>0 ? x : -x;
}
int main()
{
    int n, i, j;
    LL min1, ans1, ans2;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        b[i] = a[i];
    }
    sort(a + 1, a + n + 1);
    memset(dp, 0, sizeof(dp));
    for (i = 1; i <= n; i++)
    {
        min1 = INF;
        for (j = 1; j <= n; j++)
        {
            min1 = min(min1, dp[i - 1][j]);
            dp[i][j] = Abs(a[j] - b[i]) + min1;
            //dp[i][j]表示把前i个数变成单调增(不严格)且第i个数变成原来第j大的数的最小代价。

            //dp[i][j] = min{ dp[i - 1][1...j] }+abs(a[i] - b[j]).
        }
    }
    ans1 = INF;
    for (i = 1; i <= n; i++)
    {
        ans1 = min(ans1, dp[n][i]);
    }
    memset(dp, 0, sizeof(dp));
    for (i = 1; i <= n; i++)
    {
        min1 = INF;
        for (j = n; j >= 1; j--)
        {
            min1 = min(min1, dp[i - 1][j]);
            dp[i][j] = Abs(a[j] - b[i]) + min1;
        }
    }
    ans2 = INF;
    for (i = 1; i <= n; i++)
    {
        ans2 = min(ans2, dp[n][i]);
    }
    printf("%lld\n", min(ans1, ans2));
    return 0;
}