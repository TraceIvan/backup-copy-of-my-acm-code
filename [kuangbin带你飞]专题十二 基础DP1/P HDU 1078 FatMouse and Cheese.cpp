#include<iostream>
#include<queue>
using namespace std;
const int maxn = 110;
const int INF = 0x7fffffff;
int mp[maxn][maxn];
int dp[maxn][maxn];
int n, k;
int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1,0,0 };
int DFS(int r,int c)
{//¼ÇÒä»¯ËÑË÷DP
    int ans = 0;
    if (!dp[r][c])
    {
        for (int i = 1; i <= k; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int tr = r + dr[j] * i;
                int tc = c + dc[j] * i;
                if (tr >= 0 && tr < n&&tc >= 0 && tc < n)
                {
                    if (mp[tr][tc] > mp[r][c])
                    {
                        ans = max(ans, DFS(tr,tc));
                    }
                }
            }
        }
        dp[r][c] = ans + mp[r][c];
    }
    return dp[r][c];
}
struct node
{
    int x;
    int y;
    node(int xx=0,int yy=0):x(xx),y(yy){ }
};
int main()
{
    while (~scanf("%d%d", &n, &k))
    {
        if (n == -1 && k == -1)break;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%d", &mp[i][j]);
                dp[i][j] = 0;
            }
        }
        printf("%d\n", DFS(0,0));
    }
    return 0;
}