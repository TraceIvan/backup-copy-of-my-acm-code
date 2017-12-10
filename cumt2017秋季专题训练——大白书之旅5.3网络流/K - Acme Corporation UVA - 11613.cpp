#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int maxn = 510;
const int maxe = (maxn + maxn + maxn*maxn) * 2 + 10;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cap, flow, cost, next;
    edge(int ff=0,int tt=0,int cc=0,int ww=0,int ss=0,int nn=0):from(ff),to(tt),cap(cc),flow(ww),cost(ss),next(nn){ }
}Edge[maxe];
int Head[maxn], totedge;

struct MCMF
{
    int pre[maxn];//记录在增广路径上，到达i的边的编号
    int dist[maxn];
    bool vis[maxn];
    int N,st,ed;

    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
    }

    void Set(int nodes, int source, int dest)
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

    bool SPFA(int s, int t)//跑一遍SPFA 找s——t的最少花销路径 且该路径上每一条边不能满流 ,若存在 说明可以继续增广，反之不能  
    {
        queue<int>q;
        memset(dist, INF , sizeof(dist));
        memset(vis, 0, sizeof(vis));
        memset(pre, -1, sizeof(pre));
        
        dist[s] = 0;
        vis[s] = true;
        q.push(s);
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
        return pre[t] != -1&&dist[t]<=0;
    }

    void cal_MCMF(long long&cost,long long&flow)
    {
        flow = 0, cost = 0;
        while (SPFA(st, ed))
        {
            //通过反向弧,在源点到汇点的最少花费路径 找最小增广流
            int Min = INF;
            for (int i = pre[ed]; i != -1; i = pre[Edge[i ^ 1].to])
            {
                Min = min(Min, Edge[i].cap - Edge[i].flow);
            }
            //增广
            for (int i = pre[ed]; i != -1; i = pre[Edge[i ^ 1].to])
            {
                Edge[i].flow += Min;
                Edge[i ^ 1].flow -= Min;
                cost +=1ll*Edge[i].cost*Min;
            }
            flow += Min;
        }
    }
}mcmf;

int M, I;//总月份，每保存一个月的花费
struct node
{
    int mi, ni, pi, si, Ei;//单位生产费用；最大生产量；单位销售价格；最大销售量限制；可保存月份
    node(int mm=0,int nn=0,int pp=0,int ss=0,int ee=0):mi(mm),ni(nn),pi(pp),si(ss),Ei(ee){ }
}parameters[110];
int main()
{
    int t;
    scanf("%d", &t);
    int Case = 1;
    while (t--)
    {
        scanf("%d%d", &M, &I);
        for (int i = 1; i <= M; i++)
        {
            scanf("%d%d%d%d%d", &parameters[i].mi, &parameters[i].ni, &parameters[i].pi, &parameters[i].si, &parameters[i].Ei);
        }
        mcmf.Init();
        mcmf.Set(2 * M + 2, 0, 2 * M + 1);
        for (int i = 1; i <= M; i++)
        {
            mcmf.addedge(0, 2 * i - 1, parameters[i].ni, parameters[i].mi);//本题求最大利润，费用+
            mcmf.addedge(2 * i, 2 * M + 1, parameters[i].si,-parameters[i].pi);//本题求最大利润，卖出-
        }
        for (int i = 1; i <= M; i++)
        {
            for (int j = i; j <= min(i + parameters[i].Ei, M); j++)
            {
                mcmf.addedge(2 * i - 1, 2 * j, INF, I*(j - i));//I*(j - i)表示每单位从i月保存至j月需要的费用
            }
        }
        long long flow, cost;
        mcmf.cal_MCMF(cost, flow);
        printf("Case %d: %lld\n", Case++, -cost);
    }
    return 0;
}