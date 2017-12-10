#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<string>
#include<sstream>
using namespace std;
const int maxn = 2100;
const int INF = 0x3f3f3f3f;
const int maxe = 2 * 1000 + 1000 * 500*2 + 500*2 + 10;
struct edge
{
    int from, to, cap, flow, next;
    edge(int ff=0,int tt=0,int cc=0,int ww=0,int nn=0):from(ff),to(tt),cap(cc),flow(ww),next(nn){ }
}Edge[maxe];
int Head[maxn], tmp_head[maxn],totedge;

struct Dicnic
{
    int n, st, ed, needflow;
    int level[maxn];
    int vis[maxn];

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
                if (Edge[i].cap > Edge[i].flow && !vis[v])
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
        for (int &i = tmp_head[u]; i != -1; i = Edge[i].next)
        {
            if (Edge[i].cap > Edge[i].flow&&level[Edge[i].to] == level[u] + 1)
            {
                int f = Dicnic_dfs(Edge[i].to, min(maxf, Edge[i].cap - Edge[i].flow));
                if (f > 0)
                {
                    Edge[i].flow += f;
                    Edge[i ^ 1].flow -= f;
                    flow += f;
                    maxf -= f;
                    if (maxf <= 0) break;
                }
            }
        }
        return flow;
    }

    int cal_maxflow()
    {
        int ret = 0;
        while (Dicnic_bfs())
        {
            memcpy(tmp_head, Head, sizeof(Head));
            ret += Dicnic_dfs(st, INF);
        }
        return ret;
    }

    void clearflow()
    {
        for (int i = 0; i < totedge; i++) Edge[i].flow = 0;
    }
}dnc;
int n, m;
char name[20];
string putin;
int main()
{
    while (~scanf("%d%d", &n, &m) && n + m)
    {
        dnc.Init();
        //组别为0-m-1,源点为m,人为m+1-m+n,汇点为m+n+1
        dnc.set(n + m + 2, m, m + n + 1);
        for (int i = 1; i <= n; i++)
        {
            dnc.addedge(m, m + i, 1);
        }
        getline(cin, putin);
        for (int i = 1; i <= n; i++)
        {
            getline(cin, putin);
            stringstream ssin(putin);
            ssin >> name;
            int id=0;
            while (ssin>>id)
            {
                dnc.addedge(m + i, id, 1);
            }
        }
        int nowedge =totedge;
        int ans = m;
        int l = 1,r = n;
        while (l<=r)
        {
            dnc.clearflow();
            int curmax = (l + r) / 2;
            if (totedge == nowedge)
            {
                for (int i = 0; i < m; i++)
                {
                    dnc.addedge(i, n + m + 1, curmax);
                }
            }
            else
            {
                for (int i = nowedge; i < totedge; i +=2) Edge[i].cap = curmax;
            }
            int tans = dnc.cal_maxflow();
            if (tans == n)
            {
                ans = curmax;
                r = curmax - 1;
            }
            else if (tans < n) l = curmax + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}