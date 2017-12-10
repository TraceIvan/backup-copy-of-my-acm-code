#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn = 1010;
const int maxe = 50010;
int n, m;
struct edge
{
    int from;
    int to;
    int w;
    edge(int ff=0,int tt=0,int ww=0):from(ff),to(tt),w(ww){ }
    friend bool operator<(const edge&a, const edge&b)
    {
        return a.w < b.w;
    }
};
vector<edge>minheap;
bool vis[maxn];
int pre[maxn];
int Find(int x)
{
    int r = x;
    while (r != pre[r])
    {
        r = pre[r];
    }
    int i = x, j;
    while (i != r)
    {
        j = pre[i];
        pre[i] = r;
        i = j;
    }
    return r;
}
bool Join(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx != fy)
    {
        pre[fx] = fy;
        return false;
    }
    return true;
}
int Kruskal()
{
    for (int i = 0; i <= n; i++) pre[i] = i;
    sort(minheap.begin(), minheap.end());
    int cnt = 1;
    int sum = 0;
    int i = 0;
    while (cnt < n)
    {
        while (Join(minheap[i].from,minheap[i].to)) i++;
        sum += minheap[i].w;
        cnt++;
    }
    return sum;
}
int Solve()
{
    minheap.clear();
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        minheap.push_back(edge(u, v, w));
    }
    return Kruskal();
}
int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        printf("%d\n", Solve());
    }
    return 0;
}