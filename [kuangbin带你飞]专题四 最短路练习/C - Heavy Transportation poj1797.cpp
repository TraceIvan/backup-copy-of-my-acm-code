//求1到n的路径的最小权值的最大值
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn = 1010;
const int INF = 0x7fffffff;
int n, m,Case;
struct node
{
    int to;
    int length;
    node(int tt = 0, int ll = 0) :to(tt), length(ll)
    {
    }
};
vector<node>mp[maxn];
int dis[maxn];
bool vis[maxn];
int cnt[maxn];
int ans;
bool SPFA(int root)
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    memset(dis, 0, sizeof(dis));
    dis[root] =INF, cnt[root] = 1, vis[root] = true;
    queue<int>q;
    q.push(root);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        int sz = mp[u].size();
        for (int i = 0; i < sz; i++)
        {
            int v = mp[u][i].to, len = mp[u][i].length;
            if (min(dis[u],len) > dis[v])
            {
                dis[v] = min(dis[u],len);
                if (!vis[v])
                {
                    q.push(v);
                    vis[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n)return false;
                }
            }
        }
    }
    return true;
}
void Dij(int root)
{
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    int sz = mp[root].size();
    for (int i = 0; i < sz; i++)
    {
        dis[mp[root][i].to] = mp[root][i].length;
    }
    vis[1] = true;//标记点1已经访问过  
    for (int i = 1; i <= n - 1; i++)
    {
        int maxx = 0,u=root;
        for (int j = 1; j <= n; j++)
        {
            if (!vis[j] && dis[j]>maxx)
            {
                maxx = dis[j];
                u = j;
            }
        }
        vis[u] = true;
        int sz = mp[u].size();
        for (int j = 0; j < sz; j++)
        {
            int v = mp[u][j].to;
            if (!vis[v] && dis[v] < min(dis[u],mp[u][j].length))
                dis[v] = min(dis[u], mp[u][j].length);
        }
    }
}
void Run()
{
    for (int i = 0; i <= n; i++) mp[i].clear();
    for (int i = 0; i < m; i++)
    {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        mp[u].push_back(node(v, l));
        mp[v].push_back(node(u, l));
    }
    //SPFA(1);
    Dij(1);
    printf("Scenario #%d:\n", Case);
    printf("%d\n\n",dis[n]);
}
int main()
{
    int C;
    Case = 1;
    scanf("%d", &C);
    while (C--)
    {
        scanf("%d%d", &n, &m);
        Run();
        Case++;
    }
    return 0;
}
