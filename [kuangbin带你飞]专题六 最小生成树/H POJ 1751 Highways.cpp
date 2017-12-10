#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
int n;
const int maxn =760;
int pre[maxn];
char mp[maxn][10];
bool vis[maxn];
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
double Kruskal(int cnt0)
{
    side tmp;
    double ans=0;
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
            points[cnt - cnt0].x = tmp.v1, points[cnt - cnt0].y = tmp.v2;
            cnt++;
        }
    }
    return ans;
}
int main()
{
    while (~scanf("%d",&n))
    {
        minHeap.clear();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &points[i].x, &points[i].y);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                double dis = sqrt(1.0*(points[i].x - points[j].x)*(points[i].x - points[j].x) + (points[i].y - points[j].y)*(points[i].y - points[j].y));
                minHeap.push_back(side(i, j, dis));
            }
        }
        for (int i = 0; i <= n; i++) pre[i] = i;
        int m;
        scanf("%d", &m);
        memset(vis, 0, sizeof(vis));
        int cnt = 1;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if (!Join(u, v)) cnt++;
        }
        make_heap(minHeap.begin(), minHeap.end());
        Kruskal(cnt);
        for (int i = 0; i < n - cnt; i++)
        {
            printf("%d %d\n", points[i].x, points[i].y);
        }
    }
    return 0;
}