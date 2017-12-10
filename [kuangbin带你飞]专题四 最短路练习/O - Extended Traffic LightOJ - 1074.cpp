#include<iostream>
#include<vector>
#include<queue>
#include<memory.h>
#include<cstdio>
using namespace std;
const int maxn = 210;
const int INF = 0x7fffffff;
int n, m, q;
int busy[maxn];
struct node
{
    int to;
    int dd;
    node(int tt=0,int d=0):to(tt),dd(d){ }
};
vector<node>mp[maxn];
bool vis[maxn];
bool isfu[maxn];
int dis[maxn];
int cnt[maxn];
bool SPFA(int root)
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    memset(isfu, 0, sizeof(isfu));
    for (int i = 0; i <= n; i++) dis[i] = INF;
    dis[root] = 0, cnt[root]++, vis[root] = true;
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
            int v = mp[u][i].to;
            int ff = mp[u][i].dd;
            if (isfu[v])continue;
            if (dis[u] + ff < dis[v])
            {
                dis[v] = dis[u] + ff;
                if (!vis[v])
                {
                    q.push(v);
                    cnt[v]++;
                    vis[v] = true;
                    if (cnt[v] > n)isfu[v] = true;
                }
            }
        }

    }
    return true;
}
int main()
{
    int t;
    int Case = 1;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i <= n; i++) mp[i].clear();
        for (int i = 1; i <= n; i++) scanf("%d", &busy[i]);
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            int len = (busy[v] - busy[u])*(busy[v] - busy[u])*(busy[v] - busy[u]);
            mp[u].push_back(node(v, len));
        }
        SPFA(1);
        scanf("%d", &q);
        printf("Case %d:\n", Case++);
        for (int i = 0; i < q; i++)
        {
            int des;
            scanf("%d", &des);
            if (isfu[des] || dis[des] == INF || dis[des] < 3)printf("?\n");
            else printf("%d\n",dis[des]);
        }
    }
    return 0;
}