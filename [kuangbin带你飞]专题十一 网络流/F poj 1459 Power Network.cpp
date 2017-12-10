#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define MAXN 100+20
#define MAXM 40000+10
#define INF 1000000000+10
using namespace std;
/*��������Դ0�ڵ� ��ֻ��ͨ���з���վ������վ����󷢵���Ϊ�������ϵ�������
 ����������n+1�ڵ� ��ֻ��ͨ��������վ������վ�����������Ϊ�������ϵ������� ����������ת�����󳬼�Դ��������� ��������⡣
ע�⣺���ߵ�ʱ�򣬰ѱ���Լ�һ����Ϊ����ԴΪ0�ڵ㣬����Ŀ�и��Ľڵ��Ǵ�0��ʼ�ġ�*/
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
        addedge(0, b + 1, d);//����Դ 
    }
    while (nc--)
    {
        scanf(" (%d)%d", &a, &d);
        addedge(a + 1, n + 1, d);//������ 
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