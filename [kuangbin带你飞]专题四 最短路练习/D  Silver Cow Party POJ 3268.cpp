#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 1010;
const int INF = 0x7fffffff;
int n, m,x;
int sumdis[maxn];
struct node
{
    int to;
    int length;
    node(int tt = 0, int ll = 0) :to(tt), length(ll)
    {
    }
};
vector<node>mp[maxn];
int dis[maxn][maxn];
bool vis[maxn];
int cnt[maxn];

bool SPFA(int root)
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) dis[root][i] = INF;
    queue<int>q;
    dis[root][root] = 0, vis[root] = true, cnt[root]++;
    q.push(root);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        int sz = mp[u].size();
        for (int i = 0; i < sz; i++)
        {
            int v = mp[u][i].to, len = mp[u][i].length;
            if (dis[root][u] + len < dis[root][v])
            {
                dis[root][v] = dis[root][u] + len;
                if (!vis[v])
                {
                    q.push(v);
                    vis[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n)return false;
                }
            }
        }
    }
    return true;
}
void Run()
{
    for (int i = 0; i <= n; i++) mp[i].clear();
    for (int i = 0; i < m; i++)
    {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        mp[u].push_back(node(v, l));
    }
    int maxl=0;
    for (int i = 1; i <= n; i++)
    {
        if (i == x)continue;
        SPFA(i);
        sumdis[i] = dis[i][x];
    }
    SPFA(x);
    for (int i = 1; i <= n; i++)
    {
        if (i == x) continue;
        sumdis[i] += dis[x][i];
        maxl = max(maxl, sumdis[i]);
    }
    printf("%d\n",maxl);
}
int main()
{
    while (~scanf("%d%d%d", &n, &m,&x))
    {
        Run();
    }
    return 0;
}
