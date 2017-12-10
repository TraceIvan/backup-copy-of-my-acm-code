//从1到2的路径所经过的最大权值的最小值
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn = 210;
const double INF = 1e9;
int n;
double dis[maxn];
bool vis[maxn];
int pre[maxn];
double ans;
struct node
{
    int x;
    int y;
}stones[maxn];
void dijkstra(int start)
{
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++)
        dis[i] = INF;
    dis[start] = 0;
    for (int i = 1; i <= n; i++)
    {
        int MinNum;
        double Min = INF;
        for (int j = 0; j < n; j++)
            if (!vis[j] && dis[j]<Min)
            {
                MinNum = j;
                Min = dis[j];
            }
        vis[MinNum] = true;
        for (int j = 0; j < n; j++)
        {
            double len = sqrt(1.0*(stones[j].x - stones[MinNum].x)*(stones[j].x - stones[MinNum].x) + (stones[j].y - stones[MinNum].y)*(stones[j].y - stones[MinNum].y));
            //dis[j] = min(dis[j], max(dis[MinNum], len));//dis[j]为从0号石头到第j号石头所有通路中最长边中的最小边
            if (!vis[j]&&max(dis[MinNum], len) < dis[j]) dis[j] = max(dis[MinNum], len);
        }
    }
}
int main()
{
    int Case = 1;
    while (~scanf("%d", &n))
    {
        if (n == 0)break;
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &stones[i].x, &stones[i].y);
        }
        dijkstra(0);
        printf("Scenario #%d\n", Case);
        printf("Frog Distance = %.3lf\n\n", dis[1]);
        Case++;
    }
    return 0;
}