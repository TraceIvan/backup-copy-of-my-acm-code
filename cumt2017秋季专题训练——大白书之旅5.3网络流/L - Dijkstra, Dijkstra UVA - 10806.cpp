#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int maxn = 110;
const int maxe = maxn*maxn*4+10;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cap, flow, cost, next;
    edge(int ff = 0, int tt = 0, int cc = 0, int ww = 0, int ss = 0, int nn = 0) :from(ff), to(tt), cap(cc), flow(ww), cost(ss), next(nn){ }
}Edge[maxe];
int Head[maxn], totedge;

struct MCMF
{
    int pre[maxn];
    int dist[maxn];
    bool vis[maxn];
    int N, st, ed;

    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
    }

    void set(int nodes, int source, int dest)
    {
        N = nodes, st = source, ed = dest;
    }

    void addedge(int from, int to, int cap, int cost)
    {
        Edge[totedge] = edge(from, to, cap, 0, cost, Head[from]);
        Head[from] = totedge++;
        Edge[totedge] = edge(to, from, 0, 0, -cost, Head[to]);
        Head[to] = totedge++;
    }

    bool SPFA()
    {
        queue<int>q;
        memset(dist, INF, sizeof(dist));
        memset(vis, 0, sizeof(vis));
        memset(pre, -1, sizeof(pre));

        dist[st] = 0;
        vis[st] = true;
        q.push(st);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = false;

            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                if (dist[Edge[i].to] > dist[u] + Edge[i].cost&&Edge[i].cap > Edge[i].flow)
                {
                    dist[Edge[i].to] = dist[u] + Edge[i].cost;
                    pre[Edge[i].to] = i;
                    if (!vis[Edge[i].to])
                    {
                        vis[Edge[i].to] = true;
                        q.push(Edge[i].to);
                    }
                }
            }
        }
        return pre[ed] != -1;
    }

    void cal_MCMF(int &cost, int &flow)
    {
        flow = 0, cost = 0;
        while (SPFA())
        {
            int Min = INF;
            for (int i = pre[ed]; i != -1; i = pre[Edge[i ^ 1].to])
            {
                Min = min(Min, Edge[i].cap - Edge[i].flow);
            }
            for (int i = pre[ed]; i != -1; i = pre[Edge[i ^ 1].to])
            {
                Edge[i].flow += Min;
                Edge[i ^ 1].flow -= Min;
                cost += Edge[i].cost*Min;
            }
            flow += Min;
        }
    }
}mcmf;

int n, m;
int main()
{
    while (~scanf("%d", &n) && n)
    {
        scanf("%d", &m);
        mcmf.Init();
        mcmf.set(n + 1, 0, n);
        mcmf.addedge(0, 1, 2, 0);
        for (int i = 1; i <= m; i++)
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            mcmf.addedge(u, v, 1, c);
            mcmf.addedge(v, u, 1, c);
        }
        int cost, flow;
        mcmf.cal_MCMF(cost, flow);
        if (flow == 2) printf("%d\n", cost);
        else printf("Back to jail\n");
    }
    return 0;
}