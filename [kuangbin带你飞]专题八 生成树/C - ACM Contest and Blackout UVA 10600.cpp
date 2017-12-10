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
        return a.len > b.len;
    }
};
vector<side>minHeap;
vector<side>minheaptmp;
struct node
{
    int from;
    int to;
    int len;
    node(int ff = 0, int tt = 0, int ll = 0) :from(ff), to(tt), len(ll)
    {
    }
};
vector<node>mintree;
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

int Kruskal(int du, int dv, int flag)
{
    side tmp;
    int ans = 0;
    int cnt = 1;
    for (int i = 0; i <= n; i++)pre[i] = i;
    while (cnt < n && !minHeap.empty())
    {
        pop_heap(minHeap.begin(), minHeap.end());
        tmp = minHeap.back();
        minHeap.pop_back();
        if ((tmp.v1 == du&&tmp.v2 == dv) || (tmp.v2 == du&&tmp.v1 == dv))continue;
        int u = Find(tmp.v1);
        int v = Find(tmp.v2);
        if (u != v)
        {
            Join(tmp.v1, tmp.v2);
            ans += tmp.len;
            if (flag)
            {
                mintree.push_back(node(tmp.v1, tmp.v2, tmp.len));
            }
            cnt++;
        }
    }
    if (cnt < n&&minHeap.empty()) return -1;
    else return ans;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        minHeap.clear();
        mintree.clear();
        for (int i = 0; i < m; i++)
        {
            int u, v, l;
            scanf("%d%d%d", &u, &v, &l);
            minHeap.push_back(side(u, v, l));
        }
        make_heap(minHeap.begin(), minHeap.end());
        minheaptmp = minHeap;
        int inians = Kruskal(0, 0, 1);
        int len2 = INF;
        for (int i = 0; i < n - 1; i++)
        {
            int u = mintree[i].from;
            int v = mintree[i].to;
            minHeap = minheaptmp;
            int ans = Kruskal(u, v, 0);
            if (ans>0)
            {
                len2 = min(len2, ans);
            }
        }
        printf("%d %d\n", inians,len2);
    }
    return 0;
}