#include<stdio.h>
#include<math.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 12
#define M 59050
#define LL long long
const int inf = 0x1f1f1f1f;  //注意初始化值
int tri[N] = { 0,1,3,9,27,81,243,729,2187,6561,19683,59049 };//3^i次
int g[N][N];//地图
int dig[M][N]; //dig[i][j]记录I状态下J点是否出现，出现几次
int dp[M][N]; //dp[s][j] 在状态s下，以j为终点的最短距离
void inti()     //求出每个状态s对应的3进制位的信息
{
    int i, j, t;
    for (i = 1; i<M; i++)//所有状态数
    {
        for (t = i, j = 1; j <= 10; j++)
        {
            dig[i][j] = t % 3;//求出该状态下到达每个的城市次数
            t /= 3;
            if (!t) break;
        }
    }
}
int main()
{
    int i, j, a, b, c;
    int n, m, s;
    inti();
    while (scanf("%d%d", &n, &m) != -1)
    {
        memset(g, inf, sizeof(g));
        memset(dp, inf, sizeof(dp));
        for (i = 0; i<m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            g[a][b] = g[b][a] = min(c, g[a][b]);
        }
        for (i = 1; i <= n; i++)      //起始状态，可以任一城市为起点，
            dp[tri[i]][i] = 0;   //距离自然初始化为0
        int ans = inf;
        for (s = 1; s<tri[n + 1]; s++)  //在s状态以i为终点时更新其他状态的值
        {
            int f = 1;
            for (i = 1; i <= n; i++)
            {
                if (dig[s][i] == 0)     //判断当前状态S下，每个城市是否都已到达
                    f = 0;
                if (dp[s][i] == inf)
                    continue;
                for (j = 1; j <= n; j++) //dp[s][i]状态到dp[s+tri[j]][j]状态
                {
                    if (g[i][j] == inf || i == j || dig[s][j] >= 2)
                        continue;
                    int news = s + tri[j];
                    dp[news][j] = min(dp[news][j], dp[s][i] + g[i][j]);
                }
            }
            if (f)//判断当前状态S下，每个城市都已到达
                for (i = 1; i <= n; i++)
                    ans = min(ans, dp[s][i]);
        }
        if (ans == inf)
            ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}
