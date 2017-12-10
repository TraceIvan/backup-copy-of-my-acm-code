#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 1010;
const int INF = 0x7fffffff;
int n, t;
struct node
{
    int to;
    int length;
    node(int tt=0,int ll=0):to(tt),length(ll){ }
};
vector<node>mp[maxn];
int dis[maxn];
bool vis[maxn];
int cnt[maxn];

bool SPFA(int root)
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) dis[i] = INF;
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
            int v = mp[u][i].to,len = mp[u][i].length;
            if (dis[u] + len < dis[v])
            {
                dis[v] = dis[u] + len;
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
    for (int i = 0; i < t; i++)
    {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        mp[u].push_back(node(v, l));
        mp[v].push_back(node(u, l));
    }
    SPFA(n);
    printf("%d\n", dis[1]);
}
int main()
{
    while (~scanf("%d%d", &t, &n))
    {
        Run();
    }
    return 0;
}
