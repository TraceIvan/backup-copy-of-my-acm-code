#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<queue>
using namespace std;
int n,m;
const int maxn = 35;
map<string, int>M;
struct node
{
    int to;
    double r;
    node(int tt=0,double rr=0):to(tt),r(rr){ }
};
vector<node>mp[maxn];
bool vis[maxn];
int cnt[maxn];
double dis[maxn];
bool SPFA()
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    memset(dis, 0, sizeof(dis));
    dis[1] = 1, vis[1] = true, cnt[1]++;
    queue<int>q;
    q.push(1);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        int sz = mp[u].size();
        for (int i = 0; i < sz; i++)
        {
            int v = mp[u][i].to;
            double rt = mp[u][i].r;
            double tv = dis[u] * rt;
            if (tv> dis[v])
            {
                dis[v] = dis[u] * rt;
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
int main()
{
    int Case = 1;
    while (~scanf("%d", &n))
    {
        if (n == 0) break;
        for (int i = 0; i <= n; i++) mp[i].clear();
        string s;
        M.clear();
        cin.get();
        for (int i = 0; i < n; i++)
        {
            getline(cin, s);
            M[s] = i + 1;
        }
        scanf("%d", &m);
        string a, b;
        double rt;
        for (int i = 0; i < m; i++)
        {
            cin >> a >> rt >> b;
            int ida = M[a];
            int idb = M[b];
            mp[ida].push_back(node(idb, rt));
        }
        if (SPFA()) printf("Case %d: Yes\n", Case);
        else printf("Case %d: No\n", Case);
        Case++;
    }
    return 0;
}