#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,m;
const int maxn = 55;
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
void Join(int x, int y)
{
    int f1 = Find(x), f2 = Find(y);
    if (f1 != f2) pre[f1] = f2;
}
int Kruskal()
{
    side tmp;
    int cnt = 1;
    for (int i = 0; i <= n; i++)pre[i] = i;
    int ans = 0;
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
        if (n == 0)break;
        minHeap.clear();
        int v1, v2;
        int len;
        int k;
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d%d", &v1, &v2, &len);
            minHeap.push_back(side(v1, v2, len));
        }
        make_heap(minHeap.begin(), minHeap.end());
        int ans = Kruskal();
        printf("%d\n", ans);
    }
    return 0;
}