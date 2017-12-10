#include<iostream>
#include<queue>
#include<memory.h>
#include<algorithm>
using namespace std;
int n;
const int maxr = 110;//最大行数
const int maxc = 110;//最大列数
const int maxk = 1010;//最多可放位置
bool mp[maxr][maxc];//1表示该ij可以匹配
int cx[maxc];//记录x集合中匹配的y元素是哪一个
int cy[maxr];//记录y集合中匹配的x元素是哪一个
int vis[maxr];//标记该顶点是否访问过
struct stp
{
    int x;
    int y;
}stps[maxk];
bool dfs(int u)
{
    for (int v = 1; v <= n; v++)
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
    while (~scanf("%d", &n))
    {
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int v;
                scanf("%d", &v);
                if (v > 0) mp[i][j] = 1;
            }
        }
        int ans = maxmatch();
        if (ans < n)printf("-1\n");
        else
        {
            int t = 0;
            for (int i = 1; i <= n; i++)
            {
                int j;
                for (j = 1; j <= n; j++) if (cy[j] == i)break;
                if (i != j)
                {
                    stps[t].x = i, stps[t].y = j;
                    t++;
                    swap(cy[i], cy[j]);
                }
            }
            printf("%d\n", t);
            for (int i = 0; i < t; i++)
            {
                printf("C %d %d\n", stps[i].x, stps[i].y);
            }
        }
    }

    return 0;
}