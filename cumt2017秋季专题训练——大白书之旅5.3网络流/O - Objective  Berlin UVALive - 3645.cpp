#include<iostream>
#include<cstring>
#include<queue>
#include<map>
#include<string>
using namespace std;
const int maxn = 5000 * 2 + 10;
const int maxe = 5000 * 2 + 5000 * 2 + 5000 * 5000 + 5000 * 2 + 5000 * 2 + 100;
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

    int dicnic_maxflow()
    {
        int ret = 0;
        while (dicnic_bfs())
        {
            memcpy(tmp_head, Head, sizeof(Head));
            ret += dicnic_dfs(st, INF);
        }
        return ret;
    }
}dnc;
int cities;
map<string, int>mp;
char name[15];
char stname[15], edname[15];
struct fly
{
    int fromid, toid;
    int cap;
    int sttime, edtime;
}flight[maxn>>1];
int main()
{
    while (~scanf("%d", &cities))
    {
        mp.clear();
        scanf("%s", name);
        mp[name] = 1;
        scanf("%s", name);
        mp[name] = cities;
        int curcityid = 2;
        int edtime, m;
        scanf("%d%d", &edtime, &m);
        dnc.Init();
        dnc.set(m*2 + 2, 0, m*2 + 1);
        for (int i = 1; i <= m; i++)
        {
            scanf("%s%s", stname, edname);
            if (!mp[stname]) mp[stname] = curcityid++;
            if (!mp[edname]) mp[edname] = curcityid++;
            flight[i].fromid = mp[stname], flight[i].toid = mp[edname];
            scanf("%d%d%d", &flight[i].cap, &flight[i].sttime, &flight[i].edtime);
            if (flight[i].fromid == 1) dnc.addedge(0, i * 2 - 1, INF);
            if (flight[i].toid == cities&&flight[i].edtime<=edtime) dnc.addedge(i * 2, m * 2 + 1, INF);
            dnc.addedge(i * 2 - 1, i * 2, flight[i].cap);
        }
        for(int i=1;i<=m;i++)
        {
            if (flight[i].edtime > edtime)continue;
            for (int j = 1; j <=m; j++)
            {
                if (i == j) continue;
                if (flight[i].toid == flight[j].fromid&&(flight[j].sttime/100*60+ flight[j].sttime%100)-(flight[i].edtime/100*60+ flight[i].edtime%100)>=30&&flight[j].edtime<=edtime)
                {
                    dnc.addedge(i * 2, j * 2 - 1, INF);
                }
            }
        }
        int ans = dnc.dicnic_maxflow();
        printf("%d\n", ans);
    }
    return 0;
}