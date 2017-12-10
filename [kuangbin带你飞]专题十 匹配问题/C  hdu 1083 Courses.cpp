#include<iostream>
#include<queue>
#include<memory.h>
using namespace std;
int n, p;
const int maxn = 310;//最大学生数
const int maxp = 110;//最大学科数
bool mp[maxp][maxn];//1表示该ij可以匹配
int cx[maxp];//记录x集合中匹配的y元素是哪一个
int cy[maxn];//记录y集合中匹配的x元素是哪一个
int vis[maxn];//标记该顶点是否访问过
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
    for (int i = 1; i <= p; i++)
        if (cx[i] == -1)//如果i未匹配
        {
            memset(vis, 0, sizeof(vis));
            ans += dfs(i);
        }
    return ans;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &p, &n);
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= p; i++)
        {
            int count;
            scanf("%d", &count);
            for (int j = 1; j <= count; j++)
            {
                int v;
                scanf("%d", &v);
                mp[i][v] = true;
            }
       }
        int ans = maxmatch();
        if (ans < p)printf("NO\n");
        else printf("YES\n");
    }

    return 0;
}