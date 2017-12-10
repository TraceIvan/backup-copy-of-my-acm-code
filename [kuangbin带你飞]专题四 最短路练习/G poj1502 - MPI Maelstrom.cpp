#include<iostream>
#include<queue>
#include<vector>
#include<cstdlib>
#include<algorithm>
using namespace std;
int n;
const int maxn = 110;
const int INF = 0x7fffffff;
struct node
{
    int to;
    int len;
    node(int tt = 0,int ll=0):to(tt),len(ll){ }
};
vector<node>mp[maxn];
bool vis[maxn];
int cnt[maxn];
int pre[maxn];
int dis[maxn];
bool SPFA(int root)
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i <= n; i++) dis[i] = INF, pre[i] = root;
    dis[root] = 0, vis[root] = true, cnt[root]++;
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
            if (dis[u] + len < dis[v])
            {
                dis[v] = dis[u] + len;
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
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
    char s[25];
    for (int i = 0; i <= n; i++) mp[i].clear();
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            scanf("%s", s);
            if (s[0] != 'x')
            {
                int v = atoi(s);
                mp[i].push_back(node(j, v));
                mp[j].push_back(node(i, v));
            }
        }
    }
    SPFA(1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, dis[i]);
    }
    printf("%d\n", ans);
}
int main()
{
    while (~scanf("%d", &n))
    {
        Run();
    }
    return 0;
}