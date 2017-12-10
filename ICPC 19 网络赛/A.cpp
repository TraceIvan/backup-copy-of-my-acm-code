#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 1100;
bool use[maxn];
int deg[maxn];
int n, m;
vector<int>mpp[maxn];
int Cal()
{
    for (int i = 1; i <= n; ++i)
    {
        use[i] = false;
        deg[i] = mpp[i].size();
    }
    int ans = 0;
    while (true)
    {
        int mx = -1, u;
        for (int i = 1; i <= n; ++i)
        {
            if (use[i])
                continue;
            if (deg[i] >= mx)
            {
                mx = deg[i];
                u = i;
            }
        }
        if (mx <= 0)
            break;
        ++ans;
        use[u] = true;
        int sz = mpp[u].size();
        for (int i=0;i<sz;i++)
            --deg[mpp[u][i]];
    }
    return ans;
}
int main()
{
    //freopen("in.txt", "r", stdin);
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 0; i <= n; i++) mpp[i].clear();
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            mpp[u].push_back(v);
            mpp[v].push_back(u);
        }
        int ans = Cal();
        printf("%d\n", ans);
        /*for (int i = 1; i <=n; i++)
        {
            if (use[i]) printf("%d\n", i);
        }
        printf("\n");*/

    }
    return 0;
}
