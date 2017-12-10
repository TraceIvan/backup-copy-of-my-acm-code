#include<stdio.h>
#include<queue>
#include<string.h>
#include<iostream>
using namespace std;
#define INF 0x3f3f3f3f
int head[15500];
int level[15500];
int cur[15500];
struct node
{
    int from;
    int to;
    int w;
    int next;
}e[1500000];
int map[500][500];
int k, c, m, n, ss, tt, cont;
void add(int from, int to, int w)
{
    e[cont].to = to;
    e[cont].w = w;
    e[cont].next = head[from];
    head[from] = cont++;
}
void getmap(int mid)
{
    ss = n + 1;
    tt = ss + 1;
    cont = 0;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= k; i++)
    {
        add(i, tt, m);
        add(tt, i, 0);
    }
    for (int i = k + 1; i <= n; i++)
    {
        add(ss, i, 1);
        add(i, ss, 0);
    }
    for (int i = k + 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (map[i][j] <= mid)
            {
                add(i, j, 1);
                add(j, i, 0);
            }
        }
    }
}
int BFS()
{
    memset(level, 0, sizeof(level));
    queue<int >s;
    s.push(ss);
    level[ss] = 1;
    while (!s.empty())
    {
        int u = s.front();
        if (u == tt)return 1;
        s.pop();
        for (int i = head[u]; i != -1; i = e[i].next)
        {
            int v = e[i].to;
            int w = e[i].w;
            if (w&&level[v] == 0)
            {
                level[v] = level[u] + 1;
                s.push(v);
            }
        }
    }
    return 0;
}
int Dfs(int u, int maxflow, int tt)
{
    if (u == tt)return maxflow;
    int ret = 0;
    for (int &i = cur[u]; i != -1; i = e[i].next)
    {
        int v = e[i].to;
        int w = e[i].w;
        if (w&&level[v] == level[u] + 1)
        {
            int f = Dfs(v, min(maxflow - ret, w), tt);
            e[i].w -= f;
            e[i ^ 1].w += f;
            ret += f;
            if (ret == maxflow)return ret;
        }
    }
    return ret;
}
int Dinic(int mid)
{
    getmap(mid);
    int ans = 0;
    while (BFS() )
    {
        memcpy(cur, head, sizeof(head));
        ans += Dfs(ss, INF, tt);
    }
    if (ans == c)return 1;
    else return 0;
}
int main()
{
    while (~scanf("%d%d%d", &k, &c, &m))
    {
        for (int i = 1; i <= k + c; i++)
        {
            for (int j = 1; j <= k + c; j++)
            {
                scanf("%d", &map[i][j]);
                if (i != j&&map[i][j] == 0)
                    map[i][j] = 0x3f3f3f3f;
            }
        }
        n = k + c;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                for (int k = 1; k <= n; k++)
                {
                    map[j][k] = min(map[j][i] + map[i][k], map[j][k]);
                }
            }
        }
        int ans, mid;
        int l = 0;
        int r = 10000;
        while (l<=r)
        {
            mid = (l + r) / 2;
            if (Dinic(mid))
            {
                r = mid - 1;
                ans = mid;
            }
            else l = mid + 1;
        }
        printf("%d\n", ans);
    }
}