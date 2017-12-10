//次小生成树可由最小生成树换一条边得到.
//题意：
//有n个城市，秦始皇要修用n-1条路把它们连起来，要求从任一点出发，都可以到达其它的任意点。秦始皇希望这所有n-1条路长度之和最短。然后徐福突然有冒出来，说是他有魔法，可以不用人力、财力就变出其中任意一条路出来。
//秦始皇希望徐福能把要修的n - 1条路中最长的那条变出来，但是徐福希望能把要求的人力数量最多的那条变出来。对于每条路所需要的人力，是指这条路连接的两个城市的人数之和。
//最终，秦始皇给出了一个公式，A / B，A是指要徐福用魔法变出的那条路所需人力， B是指除了徐福变出来的那条之外的所有n - 2条路径长度之和，选使得A / B值最大的那条。

#include<iostream>
#include<algorithm>
using namespace std;
int n;//结点（城市）数目
const int maxn = 1010;
struct node
{
    int x;
    int y;
    int v;
}points[maxn];//记录每个城市的坐标，以及城市的人口(结点值)
double dis[maxn][maxn];//根据点的坐标得到两点之间的距离
bool mintree[maxn][maxn];//标记最小生成树的边
double pathmax[maxn][maxn];//记录最小生成树中两点间路径的最大权值
int pre[maxn];//标记生成最小生成树中，每个结点的父结点
bool vis[maxn];//记录加入最小生成树的结点

void Init()//初始化：得到结点间的距离
{
    for (int i = 1; i <= n; i++)
    {
        dis[i][i] = 0;
        for (int j = i + 1; j <= n; j++)
        {
            double distance = sqrt((points[i].x - points[j].x)*(points[i].x - points[j].x) + (points[i].y - points[j].y)*(points[i].y - points[j].y));
            dis[i][j] = dis[j][i] = distance;
        }
    }
}

double Prime()
{
    memset(vis, 0, sizeof(vis));
    memset(mintree, 0, sizeof(mintree));
    memset(pathmax, 0, sizeof(pathmax));
    double sum = 0;
    double mincost[maxn];//记录当前权值
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
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d", &points[i].x, &points[i].y, &points[i].v);
        }
        Init();
        double inilen=Prime();
        double ratio = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j) continue;
                if (mintree[i][j])//如果选择的是最小生成树中的一条边，则剩下的路径长为inilen - dis[i][j]
                {
                    ratio = max(ratio, (points[i].v + points[j].v) / (inilen - dis[i][j]));
                }
                else//如果选择的不是最小生成树中的边，那么加入该条边后就会形成一个环，需要删去最小生成树中i到j的路径中权值最大的边
                {
                    ratio = max(ratio, (points[i].v + points[j].v) / (inilen - pathmax[i][j]));
                }
            }
        }
        printf("%.2lf\n", ratio);
    }
    return 0;
}