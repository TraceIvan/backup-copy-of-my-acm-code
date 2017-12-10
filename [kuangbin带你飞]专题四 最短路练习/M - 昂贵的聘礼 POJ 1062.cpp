#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int M, N;
const int maxn = 110;
const int INF = 0x7fffffff;
struct node
{
    int to;
    int fee;
    node(int tt=0,int ff=0):to(tt),fee(ff){ }
};
int lvl[maxn];
vector<node>mp[maxn];
int dis[maxn];
int cnt[maxn];
bool vis[maxn];
bool SPFA(int root, int limitl, int limitr)
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i <= N; i++) dis[i] = INF;
    dis[root] = 0, vis[root] = true, cnt[root]++;
    queue<int>q;
    q.push(root);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        int sz = mp[u].size();
        for (int i = 0; i < sz; i++)
        {
            int v = mp[u][i].to;
            int fee = mp[u][i].fee;
            if (lvl[v]<limitl || lvl[v]>limitr)continue;
            if (dis[u] + fee < dis[v])
            {
                dis[v] = dis[u] + fee;
                if (!vis[v])
                {
                    vis[v] = true;
                    cnt[v]++;
                    q.push(v);
                    if (cnt[v] > N+1)return false;
                }
            }
        }
        vis[u] = false;
    }
    return true;
}
int main()
{
    while (~scanf("%d%d", &M, &N))
    {
        for (int i = 0; i <= N; i++) mp[i].clear();
        for (int i = 1; i <= N; i++)
        {
            int cost, level, x;
            scanf("%d%d%d", &cost, &level, &x);
            mp[0].push_back(node(i, cost));
            lvl[i] = level;
            for (int j = 0; j < x; j++)
            {
                int u, cost2;
                scanf("%d%d", &u, &cost2);
                mp[u].push_back(node(i, cost2));
            }
        }
        int ans = INF;
        for (int limit = lvl[1] - M; limit <= lvl[1]; limit++)
        {
            SPFA(0,limit,limit+M);
            ans = min(ans, dis[1]);
        }
        printf("%d\n", ans);
    }
    return 0;
}