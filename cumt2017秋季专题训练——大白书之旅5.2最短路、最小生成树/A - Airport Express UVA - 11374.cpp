#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn = 510;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cost,next;
    edge(int ff=0,int tt=0,int cc=0,int nn=0):from(ff),to(tt),cost(cc),next(nn){ }
};
vector<edge>Edge;
int Head[maxn], totedge;
int N, S, E;
int M, K;
struct DIJ
{
    bool vis[maxn];
    int preS[maxn];
    int disS[maxn];
    int disT[maxn];
    int preT[maxn];
    int st, ed,n;
    void set(int nodes,int source,int dest)
    {
        n=nodes,st = source, ed = dest;
    }
    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
        Edge.clear();
    }
    void addedge(int from, int to, int cost)
    {
        Edge.push_back(edge(from, to, cost, Head[from]));
        Head[from] = totedge++;
        Edge.push_back(edge(to, from, cost, Head[to]));
        Head[to] = totedge++;
    }
    void cal_dij(int *dis,int *pre)
    {
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++) dis[i] = INF,pre[i]=-1;
        for (int i = Head[st]; i != -1; i = Edge[i].next)
        {
            dis[Edge[i].to] = Edge[i].cost;
            pre[Edge[i].to] = st;
        }
        vis[st] = true, dis[st] = 0;
        for (int i = 1; i < n; i++)
        {
            int u = st, Min = INF;
            for (int j = 1; j <= n; j++)
            {
                if (!vis[j] && dis[j] < Min) u = j, Min = dis[j];
            }
            vis[u] = true;
            for (int k = Head[u]; k != -1; k = Edge[k].next)
            {
                int v = Edge[k].to;
                if (!vis[v] && dis[v] > dis[u] + Edge[k].cost)
                {
                    dis[v] = dis[u] + Edge[k].cost;
                    pre[v] = u;
                }
            }
        }
    }
    void PrintS(int u)
    {
        if (u != S) PrintS(preS[u]);
        if (u == S) printf("%d",u);
        else printf(" %d", u);
    }
    void PrintT(int u)
    {
        printf(" %d", u);
        if(u!=E) PrintT(preT[u]);
    }
}dij;

int main()
{
    int Case = 1;
    while (~scanf("%d%d%d", &N, &S, &E))
    {
        if (Case > 1) printf("\n");
        scanf("%d", &M);
        dij.Init();
        for (int i = 1; i <= M; i++)
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            dij.addedge(u, v, c);
        }
        dij.set(N, S, E);
        dij.cal_dij(dij.disS,dij.preS);
        dij.set(N, E, S);
        dij.cal_dij(dij.disT,dij.preT);
        scanf("%d", &K);
        int ans = dij.disS[E],from,to;
        for(int i=1;i<=K;i++)
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            if (dij.disS[u] + dij.disT[v] + c < ans) ans = dij.disS[u] + dij.disT[v] + c, from = u, to = v;
            if (dij.disS[v] + dij.disT[u] + c < ans) ans = dij.disS[v] + dij.disT[u] + c, from = v, to = u;
        }
        if (ans == dij.disS[E])
        {
            dij.PrintS(E);
            printf("\n");
            printf("Ticket Not Used\n");
            printf("%d\n", ans);
        }
        else
        {
            dij.PrintS(from);
            dij.PrintT(to);
            printf("\n");
            printf("%d\n", from);
            printf("%d\n", ans);
        }
        Case++;
    }
    return 0;
}