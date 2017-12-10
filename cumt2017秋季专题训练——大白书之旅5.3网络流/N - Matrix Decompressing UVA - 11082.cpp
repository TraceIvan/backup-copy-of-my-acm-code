#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdio>
using namespace std;
const int maxn = 50;
const int maxe = 20 * 2 * 2 + 20 * 20 * 2 + 10;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cap, flow, next;
    edge(int ff=0,int tt=0,int cc=0,int ww=0,int nn=0):from(ff),to(tt),cap(cc),flow(ww),next(nn){ }
}Edge[maxe];
int Head[maxn], totedge, tmp_head[maxn];

struct Dicnic
{
    int n, st, ed;
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
                if (Edge[i].cap > Edge[i].flow && level[v]==-1&&!vis[v])
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
        for (int&i = tmp_head[u]; i != -1; i = Edge[i].next)
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
}dnc;
int sumr[30], sumc[30];
int main()
{
    int t, Case = 1;
    scanf("%d", &t);
    int R, C;
    while (t--)
    {
        scanf("%d%d", &R, &C);
        for (int i = 1; i <= R; i++)
        {
            scanf("%d",&sumr[i]);
        }
        int sum = sumr[R];
        for (int i = R; i>1; i--)
        {
            sumr[i] -= sumr[i - 1];
        }
        for (int i = 1; i <= C; i++)
        {
            scanf("%d", &sumc[i]);
        }
        for (int i = C; i>1; i--)
        {
            sumc[i] -= sumc[i - 1];
        }
        //起点为0，行从1-R，列从R+1-R+C,汇点为R+C+1
        dnc.Init();
        dnc.set(R + C + 2, 0, R + C + 1);
        for (int i = 1; i <= R; i++) dnc.addedge(0, i, sumr[i]-C);
        for (int i = 1; i <= C; i++) dnc.addedge(R + i, R + C + 1, sumc[i]-R);
        int nowedge = totedge;
        for (int i = 1; i <= R; i++)
        {
            for (int j = 1; j <= C; j++)
            {
                dnc.addedge(i, R + j, 19);
            }
        }
        dnc.cal_maxflow();
        nowedge -= 2;
        printf("Matrix %d\n", Case++);
        for (int i = 1; i <=R; i++)
        {
            for (int j = 1; j <= C; j++)
            {
                nowedge += 2;
                printf("%d ", Edge[nowedge].flow + 1);
            }
            printf("\n");
        }
        if(t) printf("\n");
    }
    return 0;
}