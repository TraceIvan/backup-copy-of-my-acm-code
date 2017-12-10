#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define inf 999999999
using namespace std;
int n, m, g[510][510], dis[510], node[510], ans;
bool vis[510];

void stoer_wagner()
{
    ans = inf;
    for (int i = 1; i <= n; i++)
        node[i] = i - 1;
    while (n>1)
    {
        int mx = -1, mxi = 1, pre;
        for (int i = 2; i <= n; i++)
        {
            dis[node[i]] = g[node[1]][node[i]];
            vis[node[i]] = 0;
            if (dis[node[i]]>mx)
            {
                mx = dis[node[i]]; mxi = i;
            }
        }
        pre = 1; vis[node[1]] = 1;
        for (int i = 1; i<n; i++)
        {
            vis[node[mxi]] = 1;
            if (i != n - 1)
            {
                pre = mxi;
                mx = -1;
                for (int j = 1; j <= n; j++)
                    if (!vis[node[j]])
                    {
                        dis[node[j]] += g[node[pre]][node[j]];
                        if (dis[node[j]]>mx)
                        {
                            mx = dis[node[j]]; mxi = j;
                        }
                    }
            }
            else
            {
                ans = min(ans, mx);
                for (int j = 1; j <= n; j++)
                {
                    g[node[pre]][node[j]] += g[node[mxi]][node[j]];
                    g[node[j]][node[pre]] = g[node[pre]][node[j]];
                }
                node[mxi] = node[n--];
            }
        }
    }
}

int main()
{
    while (scanf("%d%d", &n, &m) != EOF)
    {
        memset(g, 0, sizeof(g));
        for (int i = 1, c, x, y; i <= m; i++)
        {
            scanf("%d%d%d", &x, &y, &c);
            g[y][x] = g[x][y] = g[x][y] + c;
        }

        stoer_wagner();

        printf("%d\n", ans);
    }

    return 0;
}
