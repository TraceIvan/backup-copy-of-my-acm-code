#include <iostream>
#include <functional>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <set>
#include <queue>
//#pragma comment (linker,"/STACK:102400000,102400000")
//#define pi acos(-1.0)
//#define eps 1e-6
//#define lson rt<<1,l,mid
//#define rson rt<<1|1,mid+1,r
//#define FRE(i,a,b)  for(i = a; i <= b; i++)
//#define FREE(i,a,b) for(i = a; i >= b; i--)
//#define FRL(i,a,b)  for(i = a; i < b; i++)
//#define FRLL(i,a,b) for(i = a; i > b; i--)
//#define mem(t, v)   memset ((t) , v, sizeof(t))
//#define sf(n)       scanf("%d", &n)
//#define sff(a,b)    scanf("%d %d", &a, &b)
//#define sfff(a,b,c) scanf("%d %d %d", &a, &b, &c)
//#define pf          printf
//#define DBG         pf("Hi\n")
//typedef long long ll;
using namespace std;

#define INF 0x3f3f3f3f
const int maxn = 55;
const int MAXN = 125;
const int MAXM = 200010;

struct Edge
{
    int to, next, cap, flow, cost;
}edge[MAXM];

int head[MAXN], tol;
int pre[MAXN], dis[MAXN], MIN[MAXN];
bool vis[MAXN];
int N, n, m, k, p;

int order[maxn][maxn];
int supply[maxn][maxn];
int cost[maxn][maxn][maxn];

void init(int n)
{
    N = n;
    tol = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int cap, int cost)
{
    edge[tol].to = v;
    edge[tol].cap = cap;
    edge[tol].cost = cost;
    edge[tol].flow = 0;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = 0;
    edge[tol].cost = -cost;
    edge[tol].flow = 0;
    edge[tol].next = head[v];
    head[v] = tol++;
}

bool spfa(int s, int t)
{
    queue<int>q;
    for (int i = 0; i<N; i++)
    {
        dis[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    MIN[s] = INF;
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if (edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost)
            {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                MIN[v] = min(edge[i].cap - edge[i].flow, MIN[u]);
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return pre[t] != -1;
}

//返回的是最大流，cost存的是最小费用
int minCostMaxflow(int s, int t, int &cost)
{
    int flow = 0;
    cost = 0;
    while (spfa(s, t))
    {
        int Min = MIN[t];
        for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to])
        {
            edge[i].flow += Min;
            edge[i ^ 1].flow -= Min;
            cost += edge[i].cost*Min;
        }
        flow += Min;
    }
    return flow;
}

void build(int r)
{
    init(n + m + 2);
    for (int i = 1; i <= m; i++)
        addedge(0, i, supply[i][r], 0);
    for (int i = 1; i <= n; i++)
        addedge(i + m, n + m + 1, order[i][r], 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            addedge(j, i + m, INF, cost[r][i][j]);
}


int main()
{
    int i, j, r;
    while (~scanf("%d%d%d", &n, &m, &k))
    {
        if (n == 0 && m == 0 && k == 0) break;
        int su = 0, ord = 0;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= k; j++)
                scanf("%d", &order[i][j]), ord += order[i][j];
        for (i = 1; i <= m; i++)
            for (j = 1; j <= k; j++)
                scanf("%d", &supply[i][j]), su += supply[i][j];
        for (r = 1; r <= k; r++)
            for (i = 1; i <= n; i++)
                for (j = 1; j <= m; j++)
                    scanf("%d", &cost[r][i][j]);
        if (ord>su)
        {
            printf("-1\n");
            continue;
        }
        int ans = 0, Cost = 0, c;
        for (r = 1; r <= k; r++)
        {
            build(r);
            int x = minCostMaxflow(0, n + m + 1, c);
            ans += x;
            Cost += c;
        }
        if (ans<ord)
            printf("-1\n");
        else
            printf("%d\n", Cost);
    }
    return 0;
}
