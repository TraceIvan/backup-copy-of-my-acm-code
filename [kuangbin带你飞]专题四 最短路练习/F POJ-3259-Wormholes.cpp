#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 600;
const int INF = 0x7fffffff;
int n, m, w;
double v;
struct node
{
    int to;
    int len;
    node(int tt = 0,int ll=0) :to(tt),len(ll)
    {
    }
};
vector<node>mp[maxn];
double dis[maxn];
bool vis[maxn];
int cnt[maxn];

bool SPFA(int root)
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i <= n; i++) dis[i] = INF;
    dis[root] = 0, cnt[root] = 1, vis[root] = true;
    queue<int>q;
    q.push(root);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        int sz = mp[u].size();
        for (int i = 0; i < sz; i++)
        {
            int v = mp[u][i].to;
            int len = mp[u][i].len;
            if (dis[u]+len<dis[v])
            {
                dis[v] = dis[u] + len;
                if (!vis[v])
                {
                    q.push(v);
                    vis[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n)return true;
                }
            }
        }
    }
    return false;
}
void Run()
{
    for (int i = 0; i <= n; i++) mp[i].clear();
    for (int i = 0; i < m; i++)
    {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        mp[u].push_back(node(v,l));
        mp[v].push_back(node(u,l));
    }
    for (int j = 0; j < w; j++)
    {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        l = -l;
        mp[u].push_back(node(v, l));
    }
    if (SPFA(1)) printf("YES\n");
    else printf("NO\n");
}
int main()
{
    int C;
    scanf("%d", &C);
    while (C--)
    {
        scanf("%d%d%d", &n, &m, &w);
        Run();
    }
    return 0;
}
