#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define MAXN 100+20
#define MAXM 40000+10
#define INF 1000000000+10
using namespace std;
/*建立超级源0节点 ：只连通所有发电站，发电站的最大发电量为这条边上的容量。
 建立超级汇n+1节点 ：只连通所有消耗站，消耗站的最大消耗量为这条边上的容量。 这样讲问题转化成求超级源到超级汇的 最大流问题。
注意：增边的时候，把编号自加一，因为超级源为0节点，而题目中给的节点是从0开始的。*/
struct Edge
{
    int from, to, cap, flow, next;
}edge[MAXM];
int dist[MAXN], vis[MAXN], head[MAXN], top, cur[MAXN];
int n, np, nc, m;
void init()
{
    top = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int a, int b, int c)
{
    Edge E1 = { a, b, c, 0, head[a] };
    edge[top] = E1;
    head[a] = top++;
    Edge E2 = { b, a, 0, 0, head[b] };
    edge[top] = E2;
    head[b] = top++;
}
void getmap()
{
    int a, b, d;
    while (m--)
    {
        scanf(" (%d,%d)%d", &a, &b, &d);
        addedge(a + 1, b + 1, d);
    }
    while (np--)
    {
        scanf(" (%d)%d", &b, &d);
        addedge(0, b + 1, d);//超级源 
    }
    while (nc--)
    {
        scanf(" (%d)%d", &a, &d);
        addedge(a + 1, n + 1, d);//超级汇 
    }
}
bool BFS(int start, int end)
{
    memset(dist, -1, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    while (!Q.empty()) Q.pop();
    Q.push(start);
    dist[start] = 0;
    vis[start] = 1;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i != -1; i = edge[i].next)
        {
            Edge E = edge[i];
            if (!vis[E.to] && E.cap > E.flow)
            {
                dist[E.to] = dist[u] + 1;
                vis[E.to] = 1;
                if (E.to == end) return true;
                Q.push(E.to);
            }
        }
    }
    return false;
}
int DFS(int x, int a, int end)
{
    if (x == end || a == 0) return a;
    int flow = 0, f;
    for (int& i = cur[x]; i != -1; i = edge[i].next)
    {
        Edge& E = edge[i];
        if (dist[E.to] == dist[x] + 1 && (f = DFS(E.to, min(a, E.cap - E.flow), end)) > 0)
        {
            E.flow += f;
            edge[i ^ 1].flow -= f;
            flow += f;
            a -= f;
            if (a == 0) break;
        }
    }
    return flow;
}
int Maxflow(int start, int end)
{
    int flow = 0;
    while (BFS(start, end))
    {
        memcpy(cur, head, sizeof(head));
        flow += DFS(start, INF, end);
    }
    return flow;
}
int main()
{
    while (scanf("%d%d%d%d", &n, &np, &nc, &m) != EOF)
    {
        init();
        getmap();
        printf("%d\n", Maxflow(0, n + 1));
    }
    return 0;
}