#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn = 210;
const int maxe = 100 * 2 + 100 * 100 * 2 + 100 * 2 + 100 * 2+100;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cap, flow, next;
    edge(int ff=0,int tt=0,int cc=0,int ww=0,int nn=0):from(ff),to(tt),cap(cc),flow(ww),next(nn){ }
}Edge[maxe];
int Head[maxn], tmp_head[maxn], totedge;

struct dicnic
{
    int n, st, ed;
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
    bool dicnic_bfs()
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
    int dicnic_dfs(int u, int maxf)
    {
        if (u == ed || maxf == 0) return maxf;

        int flow = 0, f;
        for (int &i = tmp_head[u]; i != -1; i = Edge[i].next)
        {
            int v = Edge[i].to;
            if (Edge[i].cap > Edge[i].flow&&level[v] == level[u] + 1)
            {
                f = dicnic_dfs(v, min(maxf, Edge[i].cap - Edge[i].flow));
                if (f > 0)
                {
                    Edge[i].flow += f;
                    Edge[i ^ 1].flow -= f;
                    flow += f;
                    maxf -= f;
                    if (maxf == 0) break;
                }
            }
        }
        return flow;
    }
    int cal_maxflow()
    {
        int ret = 0;
        while (dicnic_bfs())
        {
            memcpy(tmp_head, Head, sizeof(Head));
            ret += dicnic_dfs(st, INF);
        }
        return ret;
    }
    void clearflow()
    {
        for (int i = 0; i < totedge; i++) Edge[i].flow = 0;
    }
}dnc;

struct node
{
    int x, y;
    int n, m;
}nn[maxn];
int n;
double d;
vector<int>ans;
bool check(int i,int j)
{
    if (1.0*(nn[i].x - nn[j].x)*(nn[i].x - nn[j].x) + (nn[i].y - nn[j].y)*(nn[i].y - nn[j].y) <= d*d) return true;
    else return false;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%lf", &n, &d);
        dnc.Init();
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d%d", &nn[i].x, &nn[i].y, &nn[i].n, &nn[i].m);
            sum += nn[i].n;
            dnc.addedge(0, 2 * i - 1, nn[i].n);
            dnc.addedge(2 * i - 1, 2 * i, nn[i].m);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j) continue;
                if (check(i, j)) dnc.addedge(2 * i, 2 * j - 1, INF);
            }
        }
        ans.clear();
        for (int i = 1; i <= n; i++)
        {
            dnc.set(2 * n + 2, 0, i * 2-1);
            dnc.clearflow();
            int rec = dnc.cal_maxflow();
            if (rec == sum) ans.push_back(i);
        }
        int sz = ans.size();
        if (sz == 0) printf("-1\n");
        else
        {
            for (int i = 0; i < sz; i++)
            {
                if (i) printf(" ");
                printf("%d", ans[i]-1);
            }
            printf("\n");
        }
    }
    return 0;
}