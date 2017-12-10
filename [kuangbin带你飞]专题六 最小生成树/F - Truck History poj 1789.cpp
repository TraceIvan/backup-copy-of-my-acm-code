#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
const int maxn = 2005;
int pre[maxn];
char mp[maxn][10];
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
    while (~scanf("%d", &n))
    {
        if (n == 0) break;
        minHeap.clear();
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", mp[i]);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                int dis = 0;
                for (int pos = 0; pos < 7; pos++)
                {
                    if (mp[i][pos] != mp[j][pos]) dis++;
                }
                minHeap.push_back(side(i, j, dis));
            }
        }
        make_heap(minHeap.begin(), minHeap.end());
        int ans = Kruskal();
        printf("The highest possible quality is 1/%d.\n", ans);
    }
    return 0;
}