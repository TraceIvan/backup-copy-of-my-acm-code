#include<iostream>
#include<queue>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn = 1100;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cap,next;
    edge(int ff=0,int tt=0,int cc=0,int nn=0):from(ff),to(tt),cap(cc),next(nn){ }
};
vector<edge>Edge;
int Head[maxn], totedge;
struct SPFA
{
    int n, st, ed;
    int vis[maxn];
    int dis[maxn];
    int cnt[maxn];
    int pre[maxn];
    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
        Edge.clear();
    }
    void set(int nodes, int source, int dest)
    {
        n = nodes, st = source, ed = dest;
    }
    void addedge(int from, int to, int cap)
    {
        Edge.push_back(edge(from, to, cap, Head[from]));
        Head[from] = totedge++;
        Edge.push_back(edge(to, from, cap, Head[to]));
        Head[to] = totedge++;
    }
    bool cal_spfa()
    {
        memset(vis, 0, sizeof(vis));
        memset(dis, INF, sizeof(dis));
        memset(cnt, 0,sizeof(cnt));
        memset(pre, -1, sizeof(pre));

        vis[st] = true, cnt[st]++, dis[st] = 0;
        queue<int>q;
        q.push(st);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = false;

            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                int v = Edge[i].to;
                if (dis[v] > dis[u] + Edge[i].cap)
                {
                    dis[v] = dis[u] + Edge[i].cap;
                    pre[v] = u;
                    if (!vis[v])
                    {
                        vis[v] = true;
                        q.push(v);
                        cnt[v]++;
                        if (v > n)return false;
                    }
                }
            }
        }
        return true;
    }
}spfa;
int n,m;
int Count[maxn];
int dfs(int u)
{
    if (Count[u] != 0) return Count[u];
    for (int i = Head[u]; i != -1; i = Edge[i].next)
    {
        int v = Edge[i].to;
        if (spfa.dis[v]<spfa.dis[u])
        {
            int tmp = dfs(v);
            Count[u] += tmp;
        }
    }
    return Count[u];
}
int main()
{
    while (~scanf("%d", &n) && n)
    {
        int from, to, d;
        spfa.Init();
        scanf("%d", &m);
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &from, &to, &d);
            spfa.addedge(from, to, d);
        }
        spfa.set(n, 2, 1);
        spfa.cal_spfa();
        memset(Count, 0, sizeof(Count));
        Count[2] = 1;
        int ans = dfs(1);
        printf("%d\n", ans);
    }
    return 0;
}