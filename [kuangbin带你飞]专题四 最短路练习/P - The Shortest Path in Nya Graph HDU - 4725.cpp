#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n, m, c;
const int maxn = 100010;
const int INF = 0x7fffffff;
int layer[maxn];
struct node
{
    int to;
    int val;
    node(int tt=0,int vv=0):to(tt),val(vv){ }
};
vector<node>mp[maxn*2];

bool vis[maxn*2];
int dis[maxn*2];
int cnt[maxn*2];
int cntl[maxn];
bool SPFA(int root)
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i <= n*2; i++) dis[i] = INF;
    dis[root] = 0, cnt[root]++, vis[root] = true;
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
            int f = mp[u][i].val;
            if (dis[u] + f < dis[v])
            {
                dis[v] = dis[u] + f;
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
int main()
{
    int t;
    scanf("%d", &t);
    int Case = 1;
    while (t--)
    {
        memset(cntl, 0, sizeof(cntl));
        scanf("%d%d%d", &n, &m, &c);
        for (int i = 0; i <= n*2; i++) mp[i].clear();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &layer[i]);
            cntl[layer[i]]++;
        }
        for (int i = 1; i < n; i++)
        {//相邻层建边
            if (cntl[i] && cnt[i + 1])
            {
                mp[n + i].push_back(node(n + i + 1, c));
                mp[n + 1 + i].push_back(node(n + i, c));
            }
        }
        for (int i = 1; i <= n; i++)
        {
            mp[n + layer[i]].push_back(node(i, 0));//从点所在层到该点建边（不能反向，否则同一层的点最后距离都为0）
            if (layer[i] > 1) mp[i].push_back(node(n + layer[i] - 1, c));//从该点到其下一层建边
            if (layer[i] < n) mp[i].push_back(node(n + layer[i] + 1, c));//从该点到其上一层建边
        }
        for (int i = 0; i < m; i++)
        {
            int u,v, w;
            scanf("%d%d%d", &u, &v, &w);
            mp[u].push_back(node(v, w));
            mp[v].push_back(node(u, w));
        }
        SPFA(1);
        if (dis[n] == INF) printf("Case #%d: -1\n",Case++);
        else printf("Case #%d: %d\n", Case++, dis[n]);
    }
    return 0;
}