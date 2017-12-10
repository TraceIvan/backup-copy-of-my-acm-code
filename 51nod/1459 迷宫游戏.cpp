#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
using namespace std;
int n, m, st, ed, sum;
const int maxn = 510;
const int maxv = 700;
const int INF = 0x3f3f3f3f;
map<int, int>score;
struct node
{
    int to;
    int cost;
    node(int tt = 0, int cc = 0) :to(tt), cost(cc)
    {
    }
};
vector<node>mp[maxn];
int cnt[maxn];
int pre[maxn];
int dis[maxn];
bool vis[maxn];
int value[maxn];
bool SPFA()
{
    queue<int>q;
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    memset(value, 0, sizeof(value));

    for (int i = 0; i < n; i++)
    {
        pre[i] = st;
        dis[i] = INF;
    }
    dis[st] = 0;
    vis[st] = true;
    cnt[st]++;
    q.push(st);
    value[st] = score[st];
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        int sz = mp[u].size();
        for (int i = 0; i < sz; i++)
        {
            int v = mp[u][i].to;
            int c = mp[u][i].cost;
            if (dis[u] + c < dis[v])
            {
                dis[v] = dis[u] + c;
                pre[v] = u;
                value[v] =value[u] + score[v];
                if (!vis[v])
                {
                    vis[v] = true;
                    cnt[v]++;
                    q.push(v);
                }
            }
            else if (dis[u] + c == dis[v])
            {
                    if (value[v]<value[u] + score[v])
                    {
                        value[v] = value[u] + score[v];
                        pre[v] = u;
                        if (!vis[v])
                        {
                            vis[v] = true;
                            cnt[v]++;
                            q.push(v);
                        }
                    }
                
            }
        }
    }
    return true;
}
int main()
{
    while (~scanf("%d%d%d%d", &n, &m, &st, &ed))
    {
        score.clear();
        for (int i = 0; i < n; i++)
        {
            int val;
            scanf("%d", &val);
            score[i] = val;
            mp[i].clear();
        }
        for (int i = 1; i <= m; i++)
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            mp[u].push_back(node(v, c));
            mp[v].push_back(node(u, c));

        }
        SPFA();
        int minc = dis[ed];
        int sum = value[ed];
        printf("%d %d\n", minc, sum);
    }
    return 0;
}