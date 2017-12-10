#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
const int maxn = 1005;
int pre[maxn];
int adp[maxn];
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
double Kruskal()
{
    side tmp;
    int cnt = 1;
    int ans = 0;
    for (int i = 0; i <= n; i++) pre[i] = i;
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
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        minHeap.clear();
        for (int i = 1; i <= n; i++) scanf("%d", &adp[i]);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &mp[i][j]);
                if (i!=j) minHeap.push_back(side(i, j, mp[i][j]+adp[i]+adp[j]));
            }
        }
        make_heap(minHeap.begin(), minHeap.end());
        int ans = Kruskal();
        printf("%d\n", ans);
    }
    return 0;
}