#include<iostream>
#include<cstdio>
#include<vector>
#include<memory.h>
using namespace std;
const int maxn = 10005;
const int maxq = 10000;
vector<int> node[maxn];//邻接表
vector<int>query[maxn];//保存询问
int nstf[maxn][maxn];//保存查询结果
int n, qnum,s;
int pre[maxn];//并查集
bool vis[maxn];//标记是否访问过
pair<int, int>queq[maxq];//保存查询顺序
int f[maxn];//保存临时祖先
int Find(int x)
{
    int r = x;
    while (pre[r] != r)
    {
        r = pre[r];
    }
    int i = x, j;
    while (i != r)
    {
        int j = pre[i];
        if (j != r) pre[i] = r;
        i = j;
    }
    return r;
}
void Join(int root, int child)
{
    int rx = Find(root), ry = Find(child);
    if (rx != ry) pre[child] = root;
}
void LCA(int root)
{
    f[Find(root)] = root;
    vis[root] = true;//标记被访问过
    int sz = node[root].size();
    for (int i = 0; i < sz; i++)
    {//访问所有root子节点
        if (!vis[node[root][i]])
        {
            LCA(node[root][i]);//继续往下遍历
            Join(root, node[root][i]);//合并
            f[Find(root)] = root;
        }
    }
    int q = query[root].size();
    for (int i = 0; i < q; i++)//访问所有和root有询问关系的点
    {
        if (vis[query[root][i]])//如果被访问过
        {
            nstf[root][query[root][i]] = nstf[query[root][i]][root] = f[Find(query[root][i])];
        }
    }
}
void Init()//初始化
{
    for (int i = 0; i <= n; i++)
    {
        node[i].clear();
        query[i].clear();
        pre[i] = i;
    }
    memset(nstf, 0, sizeof(nstf));
    memset(vis, 0, sizeof(vis));
    memset(f, 0, sizeof(f));
}
int main()
{
    scanf("%d%d%d", &n, &qnum, &s);
    Init();
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        node[u].push_back(v);
        node[v].push_back(u);
    }
    scanf("%d", &qnum);
    pair<int, int>p;
    for (int i = 0; i < qnum; i++)
    {
        scanf("%d%d", &p.first, &p.second);
        query[p.first].push_back(p.second);
        query[p.second].push_back(p.first);
        queq[i] = p;
    }
    int root = s;
    LCA(root);
    for (int i = 0; i < qnum; i++)
    {
        printf("%d\n", nstf[queq[i].first][queq[i].second]);
    }
    return 0;
}