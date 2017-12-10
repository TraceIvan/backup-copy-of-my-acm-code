#include<iostream>
#include<queue>
#include<memory.h>
using namespace std;
int n, m, k;
const int maxr = 110;//最大行数
const int maxc = 110;//最大列数
const int maxk = 10010;//最多可放位置
bool mp[maxr][maxc];//1表示该ij可以匹配
int cx[maxc];//记录x集合中匹配的y元素是哪一个
int cy[maxr];//记录y集合中匹配的x元素是哪一个
int vis[maxr];//标记该顶点是否访问过
struct point
{
    int x;
    int y;
}points[maxk];
bool dfs(int u)
{
    for (int v = 1; v <= m; v++)
    {
        if (mp[u][v] && !vis[v])
        {
            vis[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))//)//如果y集合中的v元素没有匹配或者是v已经匹配，但是从cy[v]中能够找到一条增广路
            {
                cx[u] = v; cy[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
int maxmatch()//匈牙利算法主函数
{
    int ans = 0;
    memset(cx, 0xff, sizeof cx);//初始值为-1表示两个集合中都没有匹配的元素！
    memset(cy, 0xff, sizeof cy);
    for (int i = 1; i <= n; i++)
        if (cx[i] == -1)//如果i未匹配
        {
            memset(vis, 0, sizeof(vis));
            ans += dfs(i);
        }
    return ans;
}

int main()
{
    int Case = 1;
    while (~scanf("%d%d%d", &n, &m, &k))
    {
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= k; i++)
        {
            scanf("%d%d", &points[i].x, &points[i].y);
            mp[points[i].x][points[i].y] = 1;
        }
        int ans = maxmatch();
        int import = 0;
        for (int i = 1; i <= k; i++)
        {
            mp[points[i].x][points[i].y] = 0;
            int tmp = maxmatch();
            mp[points[i].x][points[i].y] = 1;
            if (tmp < ans) import++;
        }
        printf("Board %d have %d important blanks for %d chessmen.\n", Case++, import, ans);
    }

    return 0;
}