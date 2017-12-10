#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;
const int maxn = 1010;
const int maxe = maxn * 2;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cap, flow, next;
    edge(int ff=0,int tt=0,int cc=0,int ww=0,int nn=0):from(ff),to(tt),cap(cc),flow(ww),next(nn){ }
}Edge[maxe];
int Head[maxn], tmp_Head[maxn], totedge;

struct Dicnic
{
    int n,st,ed,needflow;
    int level[maxn];
    int vis[maxn];

    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
    }

    void Set(int nodes, int source, int dest)
    {
        n = nodes, st = source, ed = dest;
    }

    void addedge(int from, int to, int cap)
    {
        Edge[totedge] = edge(from, to, cap, 0, Head[from]);
        Head[from] = totedge++;
        Edge[totedge] = edge(to, from, 0, 0, Head[to]);
        Head[to] = totedge++;
    }

    bool Dicnic_bfs()
    {
        queue<int>q;
        int i, u, v;
        memset(level, -1, sizeof(level));
        memset(vis, 0, sizeof(vis));

        q.push(st);
        vis[st] = true;
        level[st] = 0;
        while (!q.empty())
        {
            u = q.front();
            q.pop();
            if (u == ed) return true;

            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                v = Edge[i].to;
                if (Edge[i].cap > Edge[i].flow && !vis[v] && level[v] == -1)
                {
                    vis[v] = true;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return false;
    }

    int Dicnic_dfs(int u, int maxf)
    {
        if (u == ed || maxf == 0) return maxf;

        int flow = 0, f;
        for (int &i = tmp_Head[u]; i != -1; i = Edge[i].next)
        {
            int v = Edge[i].to;
            if (Edge[i].cap > Edge[i].flow&&level[v] == level[u] + 1)
            {
                f = Dicnic_dfs(v, min(maxf, Edge[i].cap - Edge[i].flow));
                if (f > 0)
                {
                    Edge[i].flow += f;
                    Edge[i ^ 1].flow -= f;
                    flow += f;
                    maxf -= f;
                    if (maxf == 0) break;
                    if (flow >= needflow) return flow;
                }
            }
        }
        return flow;
     }

    int Dicnic_maxflow(int ndflow = INF)
    {
        int ret = 0;
        needflow = ndflow;
        while (Dicnic_bfs())
        {
            memcpy(tmp_Head, Head, sizeof(Head));
            ret += Dicnic_dfs(st, needflow);
            if (ret >= needflow) return ret;
        }
        return ret;
    }
}dnc;

int win[30], lost[30], remain[30][30];
vector<int>canwin;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d%d", &win[i], &lost[i]);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++) scanf("%d", &remain[i][j]);
        }

        canwin.clear();
        for (int i = 1; i <= n; i++)
        {
            int totwin = win[i];
            for (int j = 1; j <= n; j++) totwin += remain[i][j];
            bool ok = true;
            for (int j = 1; j <= n; j++)
            {
                if (j != i&&win[j] > totwin)
                {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            dnc.Init();
            dnc.Set(n*n + n + 2, 0, n*n + n + 1);
            int full = 0;
            for (int k = 1; k <= n; k++)
            {
                for (int j = k + 1; j <= n; j++)
                {
                    full += remain[k][j];
                    if (remain[k][j] > 0) dnc.addedge(0, k*n + j, remain[k][j]);
                    dnc.addedge(k*n + j, n*n + k, INF);
                    dnc.addedge(k*n + j, n*n + j, INF);
                }
                if (totwin > win[k]) dnc.addedge(n*n + k, n*n + n + 1, totwin-win[k]);
            }
            int flow = dnc.Dicnic_maxflow();
            if (flow == full) canwin.push_back(i);
        }
        int sz = canwin.size();
        for (int i = 0; i < sz; i++)
        {
            if (i) printf(" ");
            printf("%d", canwin[i]);
        }
        printf("\n");
    }
    return 0;
}