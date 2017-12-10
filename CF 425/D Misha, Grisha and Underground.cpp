#include<iostream>
#include<memory.h>
using namespace std;
int n, q;
const int maxn = 10005;
int dp[maxn][maxn];
int main()
{
    while (~scanf("%d%d", n, q))
    {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) dp[i][i] = 1;
        for (int i = 1; i <= n - 1; i++)
        {
            int v;
            scanf("%d", &v);
            dp[i][v] = dp[v][i] = 2;
        }
        for (int i = 1; i <= n; i++)
        {

        }
    }


    return 0;
}