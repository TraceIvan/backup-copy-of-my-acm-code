#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
int n;
const int maxn = 760;
int pre[maxn];
char mp[maxn][10];
bool vis[maxn];
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
struct node
{
    int x;
    int y;
    node(int xx = 0, int yy = 0) :x(xx), y(yy)
    {
    }
}points[maxn];
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
int Kruskal(int cnt0)
{
    side tmp;
    int ans = 0;
    int cnt = cnt0;

    while (cnt < n)
    {
        pop_heap(minHeap.begin(), minHeap.end());
        tmp = minHeap.back();
        minHeap.pop_back();
        int u = Find(tmp.v1);
        int v = Find(tmp.v2);
        if (u != v)
        {
            Join(tmp.v1, tmp.v2);
            ans += tmp.len;
            cnt++;
        }
    }
    return ans;
}
int main()
{
    while (~scanf("%d", &n))
    {
        minHeap.clear();
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int dis;
                scanf("%d", &dis);
                if (i == j)continue;
                minHeap.push_back(side(i, j, dis));
            }
        }
        for (int i = 0; i <= n; i++) pre[i] = i;
        int cnt = 1;
        make_heap(minHeap.begin(), minHeap.end());
        int ans=Kruskal(cnt);
        printf("%d\n", ans);
    }
    return 0;
}