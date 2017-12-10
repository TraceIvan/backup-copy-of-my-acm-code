#include<stdio.h>
#include<queue>
#include<string.h>
#include<iostream>
using namespace std;
#define INF 0x3f3f3f3f
const int maxe = 300000;
const int maxn = 2000;
const int maxb = 100;
const int maxnodes = 2000;
int head[maxnodes];
int level[maxnodes];
int cur[maxnodes];

struct node
{
    int from;
    int to;
    int w;
    int next;
}e[maxe];
int map[maxn][maxb];
int barns[maxb];
int b, n, st, ed, cont;
void addeg(int from, int to, int w)
{
    e[cont].from = from;
    e[cont].to = to;
    e[cont].w = w;
    e[cont].next = head[from];
    head[from] = cont++;
    e[cont].from = to;//·´Ïò½¨±ß
    e[cont].to = from;
    e[cont].w = 0;
    e[cont].next = head[to];
    head[to] = cont++;
}
void getmap(int x, int y)
{
    st = 0;
    ed = n + b + 1;
    cont = 0;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) addeg(st, i, 1);
    for (int i = n + 1; i <= n + b; i++) addeg(i, ed, barns[i - n]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = x; j <= y; j++)
        {
            addeg(i, n + map[i][j], 1);
        }
    }
}
int BFS()
{
    memset(level, 0, sizeof(level));
    queue<int>s;
    s.push(st);
    level[st] = 1;
    while (!s.empty())
    {
        int u = s.front();
        if (u == ed)return 1;
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
int Dinic(int x, int y)
{
    getmap(x, y);
    int ans = 0;
    while (BFS())
    {
        memcpy(cur, head, sizeof(head));
        ans += Dfs(st, INF, ed);
    }
    if (ans == n)return 1;
    else return 0;
}
int main()
{
    while (~scanf("%d%d", &n, &b))
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= b; j++)
            {
                scanf("%d", &map[i][j]);
            }
        }
        for (int i = 1; i <= b; i++) scanf("%d", &barns[i]);
        int ans = INF;
        bool flag = true;
        for (int len = 1; flag&& len <= b; len++)
        {
            for (int i = 1; flag&&i + len - 1 <= b; i++)
            {
                if (Dinic(i, i + len - 1))
                {
                    ans = len;
                    flag = false;
                    break;
                }
            }
        }
        printf("%d\n", ans);
    }
}