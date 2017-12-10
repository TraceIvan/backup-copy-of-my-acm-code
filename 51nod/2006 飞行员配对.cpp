#include<iostream>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
int n, m;
const int maxn = 210;//x集合和y集合总最大的点数
bool mp[maxn][maxn];//1表示该ij可以匹配
int cx[maxn];//记录x集合中匹配的y元素是哪一个
int cy[maxn];//记录y集合中匹配的x元素是哪一个
int vis[maxn];//标记该顶点是否访问过
int cntx;
bool dfs(int u)
{
    for (int v = m+1; v <= n; v++)
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
    for (int i = 1; i <= m; i++)
        if (cx[i] == -1)//如果i未匹配
        {
            memset(vis, 0, sizeof(vis));
            ans += dfs(i);
        }
    return ans; 
}

int main()
{
    while (~scanf("%d%d", &m, &n))
    {
        memset(mp, 0, sizeof(mp));
        int a, b;
        while (scanf("%d%d", &a, &b))
        {
            if (a == -1 && b == -1)break;
            mp[a][b] = mp[b][a] = 1;
        }

        int ans = maxmatch();
        if(ans>0)printf("%d\n", ans);
        else printf("No Solution!\n");

    }

    return 0;
}