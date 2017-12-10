#include<iostream>
#include<cstdio>
#include<vector>
#include<memory.h>
using namespace std;
const int maxn = 10010;
const int maxq = 10;
vector<int> node[maxn];//邻接表
int q1, q2, ans;
int n, qnum;
int index[maxn];//入度
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
        j = pre[i];
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
    if (q1 == root&&vis[q2]) ans = f[Find(q2)];
    else if (q2 == root&&vis[q1]) ans = f[Find(q1)];
}
void Init()//初始化
{
    for (int i = 0; i <= n; i++)
    {
        node[i].clear();
        pre[i] = i;
    }
    memset(vis, 0, sizeof(vis));
    memset(f, 0, sizeof(f));
    memset(index, 0, sizeof(index));
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        Init();
        for (int i = 1; i <= n - 1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            node[u].push_back(v);//有向图
            index[v]++;
        }
        scanf("%d%d", &q1, &q2);
        int root = 1;
        for (; root <= n; root++) if (!index[root]) break;//入度为0的为根
        LCA(root);
        printf("%d", ans);
        printf("\n");
    }
    return 0;
}