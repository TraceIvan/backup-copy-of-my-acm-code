#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
#include<queue>
#include<memory.h>
using namespace std;
int n, m;
const int maxn = 110;
const int maxm = 10010;
const int INF = 0x7fffffff;
int pre[maxn];
struct side
{
    int v1;
    int v2;
    int len;
    side(int vv1 = 0, int vv2 = 0, int ll = 0) :v1(vv1), v2(vv2), len(ll)
    {
    }
    friend bool operator <(const side&a, const side&b)
    {
        return a.len < b.len;
    }
};
vector<side>minHeap;
struct node
{
    int to;
    int len;
    node(int tt = 0, int ll = 0) : to(tt), len(ll)
    {
    }
};
vector<node>mintree[maxn];
vector<int>mintreenodes;
int pathmax[maxn][maxn];
void DFS(int cur, int fa,int dis)
{
    int sz = mintreenodes.size();
    for (int i = 0; i < sz; i++)
    {
        int prefa = mintreenodes[i];
        pathmax[prefa][cur] = pathmax[cur][prefa] = max(pathmax[prefa][fa], dis);
    }
    mintreenodes.push_back(cur);
    for (int i = 0; i < mintree[cur].size(); i++)
    {
        if (mintree[cur][i].to!=fa)
        {
            DFS(mintree[cur][i].to, cur, mintree[cur][i].len);
        }
    }
}
int Find(int x)
{
    int r = x;
    while (r != pre[r])
    {
        r = pre[r];
    }
    int c = x, p;
    while (c != r)
    {
        p = pre[c];
        pre[c] = r;
        c = p;
    }
    return r;
}
bool Join(int x, int y)
{
    int f1 = Find(x), f2 = Find(y);
    if (f1 != f2)
    {
        pre[f1] = f2;
        return false;
    }
    else return true;
}

bool vis[maxm];
int Kruskal()
{
    side tmp;
    int ans = 0;
    for (int i = 0; i <= n; i++)pre[i] = i;
    sort(minHeap.begin(), minHeap.end());
    for(int i=0;i<m;i++)
    {
        tmp = minHeap[i];
        int u = Find(tmp.v1);
        int v = Find(tmp.v2);
        if (u != v)
        {
            Join(tmp.v1, tmp.v2);
            ans += tmp.len;
            mintree[tmp.v1].push_back(node(tmp.v2, tmp.len));
            mintree[tmp.v2].push_back(node(tmp.v1, tmp.len));
            vis[i] = true;
        }
    }
    return ans;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);

        minHeap.clear();
        mintreenodes.clear();
        memset(pathmax, 0, sizeof(pathmax));
        for (int i = 0; i <= n;i++)mintree[i].clear();


        for (int i = 0; i < m; i++)
        {
            int u, v, l;
            scanf("%d%d%d", &u, &v, &l);
            minHeap.push_back(side(u, v, l));
        }
        memset(vis, 0, sizeof(vis));
        int inians = Kruskal();
        DFS(1, 0, 0);
        int len2 = INF;
        for (int i = 0; i < m; i++)
        {
            if (!vis[i])
            {
                len2 = min(len2, inians + minHeap[i].len - pathmax[minHeap[i].v1][minHeap[i].v2]);
            }
        }
        printf("%d %d\n", inians, len2);
    }
    return 0;
}