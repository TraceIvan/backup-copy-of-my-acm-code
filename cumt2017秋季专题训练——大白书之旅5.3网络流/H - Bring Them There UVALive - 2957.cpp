#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;

const int maxn = 5010;
const int maxe = 501000;
const int INF = 0x3f3f3f3f;

struct edge
{
    int from, to, cap,flow, next;
    edge(int ff=0,int tt=0,int cc=0,int fw=0,int nn=0):from(ff),to(tt),cap(cc),flow(fw),next(nn){ }
}Edge[maxe];
int Head[maxn], tmp_head[maxn], totedge;

struct Dicnic
{
    int n;
    bool vis[maxn];
    int level[maxn];
    int st, ed,needflow;

    void Init(int nodes,int source,int dest)
    {
        n = nodes, st = source, ed = dest;
        memset(Head, -1, sizeof(Head));
        totedge = 0;
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
        level[st] = 0;
        vis[st] = true;
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
        for (int &i = tmp_head[u]; i != -1; i = Edge[i].next)
        {
            int v = Edge[i].to;
            if (Edge[i].cap - Edge[i].flow > 0 && level[v] == level[u] + 1)
            {
                f = Dicnic_dfs(v, min(maxf, Edge[i].cap - Edge[i].flow));
                if (f > 0)
                {
                    Edge[i].flow += f;
                    Edge[i ^ 1].flow -= f;
                    flow += f;
                    maxf -= f;
                    if (maxf <= 0) break;
                    if (flow >= needflow) return flow;
                    //break;
                }
            }
        }
        if (flow == 0) level[u] = -1;
        return flow;
    }

    int Dicnic_maxflow(int ndflow=INF)
    {
        int ret = 0;
        needflow = ndflow;
        while (Dicnic_bfs())
        {
            memcpy(tmp_head, Head, sizeof(Head));
            //ret += Dicnic_dfs(st, INF);
            ret += Dicnic_dfs(st, needflow-ret);
            if (ret >= needflow) return ret;
        }
        return ret;
    }

    void set(int nodes,int source, int dest)
    {
        n=nodes,st = source, ed = dest;
    }
}dnc;

int N, M, K, S, T;
const int maxm = 210;
struct tunnel
{
    int from, to;
}tnl[maxm];
const int maxk = 110;
int prepos[maxk], ismove[maxk], ss[maxk], tt[maxk];
//prepos[i]表示第i个飞船上一次停留的位置
//ismove[i]表示第i个飞船当天是否已经飞过（从一个星球飞到另一个星球耗时一天）
//ss[i],tt[j] 表示当天存在从ss[i]到tt[j]的飞行

bool Cmp(const pair<int, int>&a, const pair<int, int>&b)
{
    return a.first < b.first;
}
int main()
{
    while (~scanf("%d%d%d%d%d", &N, &M, &K, &S, &T))
    {

        dnc.Init(N, S, T);
        for (int i = 1; i <=M; i++)
        {
            scanf("%d%d", &tnl[i].from, &tnl[i].to);
        }
        //每多加一天新增边
        int sum = 0, day = 0;
        while (sum < K)
        {
            day++;
            for (int i = 1; i <= N; i++) dnc.addedge((day - 1)*N + i, day*N + i, INF);
            for (int i = 1; i <= M; i++)
            {
                dnc.addedge((day - 1)*N + tnl[i].from, day*N + tnl[i].to, 1);
                dnc.addedge((day - 1)*N + tnl[i].to, day*N + tnl[i].from, 1);
            }
            dnc.set(N+day*N,S, T + day*N);
            sum += dnc.Dicnic_maxflow(K - sum);
        }
        //输出答案
        printf("%d\n", day);
        for (int i = 1; i <= K; i++) prepos[i] = S;
        int id = 0;
        for (int d = 1; d <= day; d++)
        {
            id += N*2;//跳过载有计算机的飞船停留在某个星球上一天的边
            int cnt = 0;//记录当天的所有飞行次数
            for (int i = 1; i <= M; i++)
            {
                int flow1 = Edge[id].flow;//从(day - 1)*N + tnl[i].from到day*N + tnl[i].to
                id += 2;
                int flow2 = Edge[id].flow;//从(day - 1)*N + tnl[i].to到day*N + tnl[i].from
                id += 2;
                //flow1和flow2不能同时有流量.如果同时有，说明两艘飞船互换位置，但对总体的进度没有影响
                if (flow1 && !flow2) ss[cnt] = tnl[i].from, tt[cnt++] = tnl[i].to;
                if (flow2 && !flow1) ss[cnt] = tnl[i].to, tt[cnt++] = tnl[i].from;
            }
            memset(ismove, 0, sizeof(ismove));
            printf("%d", cnt);
            vector<pair<int, int> >fly;
            for (int i = 0; i < cnt; i++)//对每一个飞行次数，分配给符合条件的飞船
            {
                for (int j = 1; j <= K; j++)
                {
                    if (ss[i] == prepos[j] && !ismove[j])
                    {
                        fly.push_back(make_pair(j, tt[i]));
                        //printf(" %d %d", j, tt[i]);
                        prepos[j] = tt[i];
                        ismove[j] = true;
                        break;
                    }
                }
            }
            sort(fly.begin(), fly.end(), Cmp);
            for (int i = 0; i < cnt; i++)
            {
                printf(" %d %d", fly[i].first, fly[i].second);
            }
            printf("\n");
        }
    }
    return 0;
}