#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
const int N = 100010;
const int M = 30;
int dp[2 * N][M];  //这个数组记得开到2*N，因为遍历后序列长度为2*n-1
bool vis[N];
struct edge
{
    int u, v, w, next;
}e[2 * N];
int tot, head[N];
inline void add(int u, int v, int w, int &k)
{
    e[k].u = u; e[k].v = v; e[k].w = w;
    e[k].next = head[u]; head[u] = k++;
    u = u^v; v = u^v; u = u^v;
    e[k].u = u; e[k].v = v; e[k].w = w;
    e[k].next = head[u]; head[u] = k++;
}
int ver[2 * N], R[2 * N], first[N], dir[N];
//ver:节点编号 R：深度 first：点编号位置 dir：距离
void dfs(int u, int dep)
{
    vis[u] = true; ver[++tot] = u; first[u] = tot; R[tot] = dep;
    for (int k = head[u]; k != -1; k = e[k].next)
        if (!vis[e[k].v])
        {
            int v = e[k].v, w = e[k].w;
            dir[v] = dir[u] + w;
            dfs(v, dep + 1);
            ver[++tot] = u; R[tot] = dep;
        }
}
void ST(int n)
{
    for (int i = 1; i <= n; i++)
        dp[i][0] = i;
    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
        {
            int a = dp[i][j - 1], b = dp[i + (1 << (j - 1))][j - 1];
            dp[i][j] = R[a]<R[b] ? a : b;
        }
    }
}
//中间部分是交叉的。
int RMQ(int l, int r)
{
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1)
        k++;
    int a = dp[l][k], b = dp[r - (1 << k) + 1][k]; //保存的是编号
    return R[a]<R[b] ? a : b;
}

int LCA(int u, int v)
{
    int x = first[u], y = first[v];
    if (x > y) swap(x, y);
    int res = RMQ(x, y);
    return ver[res];
}
vector<int>cp[N];
int main()
{
    int cas;
    scanf("%d", &cas);
    while (cas--)
    {
        int n,m, q, num = 0;
        scanf("%d%d", &n, &m);
        memset(head, -1, sizeof(head));
        memset(vis, false, sizeof(vis));
        for (int i = 1; i<n; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w, num);
        }
        tot = 0; dir[1] = 0;
        dfs(1, 1);
        ST(2 * n - 1);
        for (int i = 1; i <= m; i++)
        {
            cp[i].clear();
            int g;
            scanf("%d", &g);
            for (int j = 0; j < g; j++)
            {
                int v;
                scanf("%d", &v);
                cp[i].push_back(v);
            }
        }
        scanf("%d", &q);
        
        while (q--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            int ans = 0x3f3f3f3f;
            for (int i = 0; i < cp[u].size(); i++)
            {
                for (int j = 0; j < cp[v].size(); j++)
                {
                    int uu = cp[u][i];
                    int vv = cp[v][j];
                    int lca = LCA(uu, vv);
                    ans = min(ans, dir[uu] + dir[vv] - 2 * dir[lca]);
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
