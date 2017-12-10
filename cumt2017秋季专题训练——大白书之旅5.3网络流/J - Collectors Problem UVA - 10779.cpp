#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int maxn = 110;
const int INF = 0x3f3f3f3f;
const int maxe = 510;
struct edge
{
    int from, to, cap, flow, next;
    edge(int ff=0,int tt=0,int cc=0,int ww=0,int nn=0):from(ff),to(tt),cap(cc),flow(ww),next(nn){ }
}Edge[maxe];
int Head[maxn], tmp_head[maxn],totedge;

struct Dicnic
{
    int n, needflow, st, ed;
    int level[maxn];
    bool vis[maxn];

    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
    }

    void set(int nodes, int source, int dest)
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
        memset(level, -1, sizeof(level));
        memset(vis, 0, sizeof(vis));

        queue<int>q;
        q.push(st);
        vis[st] = true;
        level[st] = 0;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            if (u == ed) return true;
            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                int v = Edge[i].to;
                if (!vis[v] && Edge[i].cap > Edge[i].flow)
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
        for (int& i = tmp_head[u]; i != -1; i = Edge[i].next)
        {
            int v = Edge[i].to;
            if (Edge[i].cap > Edge[i].flow&&level[v] == level[u] + 1)
            {
                f = Dicnic_dfs(v, min(maxf, Edge[i].cap - Edge[i].flow));
                if (f>0)
                {
                    Edge[i].flow += f;
                    Edge[i ^ 1].flow -= f;
                    flow += f;
                    maxf -= f;
                    if (maxf <= 0) break;
                    if (flow >= needflow) return flow;
                }
            }
        }
        return flow;
    }

    int Dicnic_maxflow(int ndflow=INF)
    {
        int ret = 0;
        needflow = ndflow;
        while (Dicnic_bfs())
        {
            memcpy(tmp_head, Head, sizeof(Head));
            ret += Dicnic_dfs(st, needflow);
            if (ret >= needflow) return ret;
        }
        return ret;
    }


}dnc;

int cnt[15][30];
int main()
{
    int t;
    scanf("%d", &t);
    int Case = 1;
    while (t--)
    {
        int n,m;
        scanf("%d%d", &n,&m);
        //Bob为1，朋友为2~n,类型为n+1~n+m,汇点为n+m+1
        dnc.Init();
        dnc.set(n + m + 1, 1, n + m + 1);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++)
        {
            int k;
            scanf("%d", &k);
            for (int j = 1; j <= k; j++)
            {
                int v;
                scanf("%d", &v);
                cnt[i][v]++;
            }
        }
        for (int i = 1; i <= m; i++)
        {
            if (cnt[1][i]) dnc.addedge(1, n + i, cnt[1][i]);
            dnc.addedge(n + i, n + m + 1, 1);
        }
        for (int i = 2; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (cnt[i][j] > 1) dnc.addedge(i, n + j, cnt[i][j] - 1);
                else if (cnt[i][j] == 0) dnc.addedge(n + j, i, 1);
            }
        }
        int flow = dnc.Dicnic_maxflow();
        printf("Case #%d: %d\n",Case++, flow);
    }
    return 0;
}