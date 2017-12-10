#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
const int maxn = 6100;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cap, flow, next;
    edge(int ff = 0, int tt = 0, int cc = 0, int ww = 0, int nn = 0) :from(ff), to(tt), cap(cc), flow(ww), next(nn)
    {
    }
};
vector<edge>Edge;
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
        Edge.clear();
    }
    void set(int nodes, int source, int dest)
    {
        n = nodes, st = source, ed = dest;
    }
    void addedge(int from, int to, int cap)
    {
        Edge.push_back(edge(from, to, cap, 0, Head[from]));
        Head[from] = totedge++;
        Edge.push_back(edge(to, from, 0, 0, Head[to]));
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
}dnc;
int visa[300010];
bool visp[3100][3100];
int main()
{
    int t;
    scanf("%d", &t);
    int Case = 1;
    while (t--)
    {
        dnc.Init();
        int na, nb;
        memset(visa, 0, sizeof(visa));
        memset(visp, 0, sizeof(visp));
        string tmp;
        int price, chnl;
        int sum = 0;

        scanf("%d", &na);
        getline(cin, tmp);
        for (int i = 1; i <= na; i++)
        {
            getline(cin, tmp);
            stringstream ssin(tmp);
            ssin >> price;
            sum += price;
            while (ssin >> chnl)
            {
                visa[chnl] = i;
            }
            dnc.addedge(0, i, price);
        }
        scanf("%d", &nb);
        getline(cin, tmp);
        for (int i = na + 1; i <= na + nb; i++)
        {
            getline(cin, tmp);
            stringstream ssin(tmp);
            ssin >> price;
            sum += price;
            while (ssin >> chnl)
            {
                if (visa[chnl] && !visp[visa[chnl]][i - na])
                {
                    dnc.addedge(visa[chnl], i, INF);
                    visp[visa[chnl]][i - na] = true;
                }
            }
            dnc.addedge(i, na + nb + 1, price);
        }
        dnc.set(na + nb + 2, 0, na + nb + 1);
        int ans = dnc.cal_maxflow();//所有矛盾的bid组数中代价的最小值
        printf("Case %d:\n", Case++);
        printf("%d\n", sum - ans);
        if (t) printf("\n");
    }
    return 0;
}