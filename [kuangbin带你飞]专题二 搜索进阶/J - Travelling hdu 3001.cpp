#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int n, m;
const int maxn = 15;
bool vis[maxn];
struct node
{
    int to;
    int len;
    node(int tt=0,int ll=0):to(tt),len(ll){ }
};
vector<vector<node> >mp;

int tcos,flag;
void DFS(int r,int cos,int cnt)
{
    if (cnt == n)
    {
        flag = true;
        if (cos < tcos) tcos = cos;
        return;
    }
    vis[r] = true;
    int sz = mp[r].size();
    for (int i = 0; i < sz; i++)
    {
        if (!vis[mp[r][i].to])
        {
            vis[mp[r][i].to] = true;
            DFS(mp[r][i].to, cos + mp[r][i].len, cnt + 1);
            vis[mp[r][i].to] = false;
        }
    }
    vis[r] = false;
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        mp.clear();
        int re=0;
        for (int i = 0; i <= n; i++) mp.push_back(vector<node>());
        for (int i = 0; i < m; i++)
        {
            int u, v, len;
            scanf("%d%d%d", &u, &v, &len);
            mp[u].push_back(node(v, len));
            mp[v].push_back(node(u, len));
            re += len;
        }
        flag = false;
        for (int i = 1; i <= n; i++)
        {
            memset(vis, 0, sizeof(vis));
            tcos = re;
            DFS(i,0,1);
            re = min(re, tcos);
        }
        if (flag)printf("%d\n", re);
        else printf("-1\n");
    }
    return 0;
}