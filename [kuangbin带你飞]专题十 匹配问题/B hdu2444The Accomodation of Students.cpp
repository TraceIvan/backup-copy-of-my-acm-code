#include<iostream>
#include<queue>
using namespace std;
int n,m;
const int maxn = 210;//x集合和y集合总最大的点数
bool mp[maxn][maxn];//1表示该ij可以匹配
int cx[maxn];//记录x集合中匹配的y元素是哪一个
int cy[maxn];//记录y集合中匹配的x元素是哪一个
int vis[maxn];//标记该顶点是否访问过
int cntx;
bool dfs(int u)
{
    for (int v = 1; v <= n; v++)//两个集合内共有n个元素
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
    return ans/2;//对两个部里的都匹配了，这样就相当于匹配了两次了  
}
bool istwo()
{//判断是否为二分图
    queue<int>q;
    memset(vis, 0, sizeof(vis));
    q.push(1);
    vis[1] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 1; i <= n; i++)
        {
            if (mp[u][i])
            {
                if (vis[i] == 0)
                {
                    if (vis[u] == 1) vis[i] = 2;
                    else vis[i] = 1;
                    q.push(i);
                }
                else
                {
                    if (vis[i] == vis[u]) return false;
                }
            }
        }
    }
    return true;
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        memset(mp ,0, sizeof(mp));
        while (m--)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            mp[a][b] = mp[b][a] = 1;
        }
        if (!istwo()|| n == 1)
        {
            printf("No\n");
        }
        else
        {
            int ans = maxmatch();
            printf("%d\n", ans);
        }
    }

    return 0;
}