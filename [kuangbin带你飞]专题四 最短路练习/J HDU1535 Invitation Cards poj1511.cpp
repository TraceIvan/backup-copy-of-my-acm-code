#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int p, q;
const int maxp = 1000010;
const int INF = 0x7fffffff;
bool vis[maxp];
int cnt[maxp];
int pre[maxp];
int dis[maxp];
long long sum;
struct node
{
    int to;
    int fee;
    node(int tt=0,int ff=0):to(tt),fee(ff){ }
};
vector<node>mp[maxp];
struct points
{
    int from;
    int to;
    int v;
}pp[maxp];
bool SPFA(int root)
{
    for (int i = 0; i <= p; i++)
    {
        dis[i] = INF;
        pre[i] = root;
        cnt[i] = 0;
        vis[i] = false;
    }
    queue<int>q;
    q.push(root);
    dis[root]=0,cnt[root] = 1, vis[root] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        int sz = mp[u].size();
        for (int i = 0; i < sz; i++)
        {
            int v = mp[u][i].to;
            int ff = mp[u][i].fee;
            if (dis[u] + ff < dis[v])
            {
                dis[v] = dis[u] + ff;
                if (!vis[v])
                {
                    vis[v] = true;
                    cnt[v]++;
                    q.push(v);
                    if (cnt[v] > p)return false;
                }
            }
        }
    }
    return true;
}
void RSet()
{
    for (int i = 0; i <= p; i++) mp[i].clear();
    for (int i = 0; i < q; i++)
    {
        mp[pp[i].to].push_back(node(pp[i].from, pp[i].v));
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &p, &q);
        for (int i = 0; i <= p; i++) mp[i].clear();
        for (int i = 0; i < q; i++)
        {
            int u, v, f;
            scanf("%d%d%d", &u, &v, &f);
            mp[u].push_back(node(v, f));
            pp[i].from = u, pp[i].to = v, pp[i].v = f;
        }
        sum = 0;
        SPFA(1);
        for (int i = 2; i <= p; i++) sum += dis[i];
        RSet();
        SPFA(1);
        for (int i = 2; i <= p; i++) sum += dis[i];
        printf("%lld\n", sum);
    }


    return 0;
}