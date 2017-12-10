#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
const int maxn = 105;
int pre[maxn];
int mp[maxn][maxn];
struct side
{
    int v1;
    int v2;
    double len;
    side(int vv1 = 0, int vv2 = 0, double ll = 0) :v1(vv1), v2(vv2), len(ll)
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
double Kruskal(int cnt)
{
    side tmp;
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
        minHeap.clear();
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &mp[i][j]);
                if (mp[i][j] > 0) minHeap.push_back(side(i, j, mp[i][j]));
            }
        }
        int q,cnt=1;
        scanf("%d", &q);
        for (int i = 0; i <= n; i++)pre[i] = i;
        for (int i = 0; i < q; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if (!Join(u, v)) cnt++;
        }
        make_heap(minHeap.begin(), minHeap.end());
        int ans = Kruskal(cnt);
        printf("%d\n", ans);
    }
    return 0;
}