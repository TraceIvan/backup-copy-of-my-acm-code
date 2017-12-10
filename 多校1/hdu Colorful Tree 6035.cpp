//#include <bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<memory.h>
#include<vector>
using namespace std;
const int MAXN = 2e5 + 10;
typedef long long LL;

//题解地址
//http://blog.csdn.net/Bahuia/article/details/76141574
LL color[MAXN], sz[MAXN], sum[MAXN], vis[MAXN]; //sum[i]记录的是到达当前节点时，颜色为i的高度最高一批结点为根的子树大小总和
                                                //sz：全部节点数
vector <int> tree[MAXN];
LL ans;

LL dfs(int u, int pa)
{
    sz[u] = 1;
    LL allson = 0;
    int cnt = tree[u].size();
    for (int i = 0; i < cnt; i++)
    {
        int v = tree[u][i];
        if (v == pa) continue;
        LL last = sum[color[u]];            // 保存递归之前的sum值
        sz[u] += dfs(v, u);
        LL add = sum[color[u]] - last;      // add就是结点v为根的子树中颜色为color[u]且高度最高的若干子树的大小
                                            // 对于结点v来说，sz[v]-add就是v这棵子树最上端的，且不包含颜色为color[u]的连通块大小
        ans += (sz[v] - add) * (sz[v] - add - 1) / 2;  // 对这个连通块中任意两个点的路径都不包含颜色color[u]
        allson += sz[v] - add;          // allson记录下儿子结点v组成的不含颜色color[u]的连通块大小总和
    }
    sum[color[u]] += allson + 1;        // sum更新，此时要加上不含color[u]连通块的大小总和以及u自己
    return sz[u];
}

int main()
{
    //freopen("data2.in", "r", stdin);
    int n, cs = 0;
    while (scanf("%d", &n) != EOF)
    {
        memset(vis, 0, sizeof(vis));
        memset(sum, 0, sizeof(sum));
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%I64d", &color[i]);
            if (!vis[color[i]]) ++cnt;
            vis[color[i]] = 1;
            tree[i].clear();
        }
        for (int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        printf("Case #%d: ", ++cs);
        if (cnt == 1)
        {             // 只有一种颜色的特殊情况
            printf("%I64d\n", (LL)n * (n - 1LL) / 2LL);
            continue;
        }
        ans = 0;
        dfs(1, -1);
        for (int i = 1; i <= n; i++)
        {      // 注意最后要对整棵树来补充所有颜色剩下的联通块
            if (!vis[i]) continue;
            else
            {
                ans += (n - sum[i]) * (n - sum[i] - 1LL) / 2LL;//子树下的统计完了，然后统计非子树的
            }
        }
        printf("%I64d\n", (LL)n * (n - 1LL) / 2LL * cnt - ans);
    }
    return 0;
}