#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;
const int maxe = 1000 * 1000 * 3 * 2 + 100;
const int maxn = 1000 * 1000*2 + 100;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cost, next;
    edge(int ff=0,int tt=0,int cc=0,int nn=0):from(ff),to(tt),cost(cc),next(nn){ }
}Edge[maxe];
int Head[maxn],totedge;

struct node
{
    int id, dist;
    node(int ii=0,int dd=0):id(ii),dist(dd){ }
    friend bool operator<(const node&a, const node&b)
    {
        return a.dist > b.dist;
    }
};
struct SPFA
{
    int st, ed;
    int dis[maxn];
    bool vis[maxn];
    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
    }
    void Set(int source, int dest)
    {
        st = source, ed = dest;
    }
    void addedge(int from, int to, int cost)
    {
        Edge[totedge] = edge(from, to, cost, Head[from]);
        Head[from] = totedge++;
        Edge[totedge] = edge(to, from, cost, Head[to]);
        Head[to] = totedge++;
    }
    void Cal_spfa()
    {
        memset(dis, INF, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        dis[st] = 0;
        priority_queue<node>q;
        q.push(node(st,0));
        while (!q.empty())
        {
            node cur = q.top();
            q.pop();
            int u = cur.id;
            if (vis[u]) continue;
            vis[u] = true;
            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                int v = Edge[i].to;
                if (dis[v] > dis[u] + Edge[i].cost)
                {
                    dis[v] = dis[u] + Edge[i].cost;
                    q.push(node(v, dis[v]));
                }
            }
        }
    }
}spfa;
int main()
{
    int n, m;
    int Case = 1;
    while (~scanf("%d%d", &n, &m) && (n + m))
    {
        spfa.Init();
        int nums = (n-1)*(m-1) * 2;
        int source = nums + 1, dest = nums + 2;
        //行
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m - 1; j++)
            {
                int cap;
                scanf("%d", &cap);
                if (i == 1)
                {
                    spfa.addedge(j * 2, dest, cap);
                }
                else if (i == n) spfa.addedge(source, (i - 2) *(m-1)* 2 + j * 2-1, cap);
                else
                {
                    spfa.addedge((i - 2)*(m - 1) * 2 + j * 2 - 1, (i - 1)*(m - 1) * 2 + j * 2, cap);
                }
            }
        }
        //列
        for (int i = 1; i <= n - 1; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                int cap;
                scanf("%d", &cap);
                if (j == 1)
                {
                    spfa.addedge(source, (i - 1)*(m - 1)*2 + 1, cap);
                }
                else if (j == m)
                {
                    spfa.addedge(i*(m-1)*2, dest, cap);
                }
                else
                {
                    spfa.addedge((i - 1)*(m - 1) * 2 + (j - 1) * 2, (i - 1)*(m - 1) * 2 + (j - 1) * 2 + 1, cap);
                }
            }
        }
        //对角线
        for (int i = 1; i <= n - 1; i++)
        {
            for (int j = 1; j <= m - 1; j++)
            {
                int cap;
                scanf("%d", &cap);
                spfa.addedge((i - 1)*(m - 1) * 2 + j * 2 - 1,(i - 1)*(m - 1) * 2 + j * 2, cap);
            }
        }
        spfa.Set(source, dest);
        spfa.Cal_spfa();
        printf("Case %d: Minimum = %d\n", Case++, spfa.dis[dest]);
    }
    return 0;
}