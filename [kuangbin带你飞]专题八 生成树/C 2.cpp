#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;
int n,m;//结点（城市）数目
const int maxn = 110;
const int INF = 0x7fffffff;
int dis[maxn][maxn];//根据点的坐标得到两点之间的距离
bool mintree[maxn][maxn];//标记最小生成树的边
int pathmax[maxn][maxn];//记录最小生成树中两点间路径的最大权值
int pre[maxn];//标记生成最小生成树中，每个结点的父结点
bool vis[maxn];//记录加入最小生成树的结点

int Prime()
{
    memset(vis, 0, sizeof(vis));
    memset(mintree, 0, sizeof(mintree));
    memset(pathmax, 0, sizeof(pathmax));
    int sum = 0;
    int mincost[maxn];//记录当前权值
    for (int i = 1; i <= n; i++)
    {
        mincost[i] = dis[1][i];
        pre[i] = 1;
    }
    vis[1] = true;
    for (int i = 1; i < n; i++)
    {//每次选1个点加入
        int u = 0;
        for (int j = 1; j <= n; j++)
        {//从未加入的点找到一条最小的边
            if (!vis[j])
            {
                if (u == 0 || mincost[j] < mincost[u])
                {
                    u = j;
                }
            }
        }
        mintree[u][pre[u]] = mintree[pre[u]][u] = true;
        sum += dis[u][pre[u]];
        vis[u] = true;

        for (int j = 1; j <= n; j++)
        {
            if (vis[j] && j != u)
            {//更新树中两点路径的最大权值
                pathmax[u][j] = pathmax[j][u] = max(pathmax[j][pre[u]], dis[u][pre[u]]);
            }
            else if (!vis[j])
            {//更新已选结点到未选结点的最短距离
                if (dis[u][j] < mincost[j])
                {
                    mincost[j] = dis[u][j];
                    pre[j] = u;
                }
            }
        }
    }
    return sum;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)//t组测试数据
    {
        scanf("%d%d", &n,&m);
        for (int i = 1; i <= n; i++)
        {
            dis[i][i] = 0;
            for (int j = i+1; j <= n; j++)
            {
                dis[i][j] = dis[j][i] = INF;
            }
        }
        for (int i = 1; i <= m; i++)
        {
            int u, v, l;
            scanf("%d%d%d", &u, &v, &l);
            dis[u][v] = dis[v][u] = l;
        }
        int inilen = Prime();
        int len2 = INF;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j||dis[i][j]==INF) continue;
                if (mintree[i][j])continue;
                len2 = min(len2, inilen + dis[i][j] - pathmax[i][j]);
                
            }
        }
        printf("%d %d\n", inilen, len2);
    }
    return 0;
}