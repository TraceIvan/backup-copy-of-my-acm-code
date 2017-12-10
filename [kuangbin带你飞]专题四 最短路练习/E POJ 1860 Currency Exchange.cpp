#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 110;
const int INF = 0x7fffffff;
int n, m, s;
double v;
struct node
{
    int to;
    double r;
    double c;
    node(int tt = 0,double rr=0,double cc=0) :to(tt),r(rr),c(cc)
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
    memset(dis, 0, sizeof(dis));
    dis[root] = v, cnt[root] = 1, vis[root] = true;
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
            double r = mp[u][i].r;
            double c = mp[u][i].c;
            if (dis[v]<(dis[u]-c)*r)
            {
                dis[v] = (dis[u] - c)*r;
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
        int u, v;
        double ruv, cuv, rvu, cvu;
        scanf("%d%d%lf%lf%lf%lf", &u, &v, &ruv,&cuv,&rvu,&cvu);
        mp[u].push_back(node(v, ruv,cuv));
        mp[v].push_back(node(u, rvu,cvu));
    }
    if (SPFA(s)) printf("YES\n");
    else printf("NO\n");
}
int main()
{
    while (~scanf("%d%d%d%lf", &n, &m,&s,&v))
    {
        Run();
    }
    return 0;
}
