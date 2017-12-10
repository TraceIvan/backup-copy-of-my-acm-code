#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int N, A, B;
const int maxn = 110;
const int INF = 0x7fffffff;
struct node
{
    int to;
    int fee;
    node(int tt=0,int ff=0):to(tt),fee(ff){ }
};
vector<node>mp[maxn];
int dis[maxn];
bool vis[maxn];
int cnt[maxn];
int pre[maxn];
bool SPFA(int root)
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i <= N; i++) dis[i] = INF, pre[i] = root;
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
            int f = mp[u][i].fee;
            if (dis[u] + f < dis[v])
            {
                dis[v] = dis[u] + f;
                if (!vis[v])
                {
                    vis[v] = true;
                    cnt[v]++;
                    q.push(v);
                    if (cnt[v] > N)return false;
                }
            }
        }
    }
    return true;
}
int main()
{
    while (~scanf("%d%d%d", &N, &A, &B))
    {
        for (int i = 0; i <= N; i++) mp[i].clear();
        for (int i = 1; i <= N; i++)
        {
            int k;
            scanf("%d", &k);
            for (int j = 0; j < k; j++)
            {
                int to;
                scanf("%d", &to);
                if (j == 0)mp[i].push_back(node(to, 0));
                else mp[i].push_back(node(to, 1));
            }
        }
        SPFA(A);
        if(dis[B]!=INF)printf("%d\n", dis[B]);
        else printf("-1\n");
    }
    return 0;
}