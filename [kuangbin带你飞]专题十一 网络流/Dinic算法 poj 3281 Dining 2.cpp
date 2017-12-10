#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define MAXN 400+10//ʳ���2*n+1��ʼ �� 2*n+f ���ϴ�2*n+f+1 ��ʼ ��2*n+1+f+d 
#define MAXM 200000+100
#define INF 200000+10
using namespace std;
struct Edge
{
    int from, to, cap, flow, next;
}edge[MAXM];
int dist[MAXN], vis[MAXN], head[MAXN], cur[MAXN], top;
int n, f, d;
void init()
{
    top = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int w)
{
    Edge E1 = { u, v, w, 0, head[u] };
    edge[top] = E1;
    head[u] = top++;
    Edge E2 = { v, u, 0, 0, head[v] };
    edge[top] = E2;
    head[v] = top++;
}
void getmap()
{
    int i, j;
    int fnum, dnum;
    for (i = 1; i <= n; i++)
    {
        scanf("%d%d", &fnum, &dnum);
        while (fnum--)//ʳ�� ���2*n+j 
        {
            scanf("%d", &j);
            addedge(2 * n + j, i, 1);//ʳ��Ͷ�Ӧ��ţ��ͨ 
        }
        while (dnum--)//���� ���2*n+f+j 
        {
            scanf("%d", &j);
            addedge(n + i, 2 * n + f + j, 1);//��ţ�Ͷ�Ӧ������ͨ 
        }
        addedge(i, n + i, 1);//��ţ�Լ����Լ���һ�� 
    }
    for (i = 1; i <= f; i++)
        addedge(0, 2 * n + i, 1);//����Դ����ͨ����ʳ��
    for (i = 1; i <= d; i++)
        addedge(2 * n + f + i, 2 * n + f + d + 1, 1);//����������ͨ������� 
}
bool BFS(int start, int end)
{
    queue<int> Q;
    memset(dist, -1, sizeof(dist));
    memset(vis, 0, sizeof(vis));
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
                vis[E.to] = 1;
                dist[E.to] = dist[u] + 1;
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
    while (scanf("%d%d%d", &n, &f, &d) != EOF)
    {
        init();
        getmap();
        printf("%d\n", Maxflow(0, 2 * n + f + d + 1));
    }
    return 0;
}
