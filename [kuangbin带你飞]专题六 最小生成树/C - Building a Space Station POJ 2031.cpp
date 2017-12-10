#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
const int maxn = 105;
int pre[maxn];
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
void Join(int x, int y)
{
    int f1 = Find(x), f2 = Find(y);
    if (f1 != f2) pre[f1] = f2;
}
double Kruskal()
{
    side tmp;
    int cnt = 1;
    for (int i = 0; i <= n; i++)pre[i] = i;
    double ans = 0;
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
struct node
{
    double x;
    double y;
    double z;
    double r;
}points[maxn];
int main()
{
    while (~scanf("%d", &n))
    {
        if (n == 0)break;
        minHeap.clear();
        for (int i = 0; i < n; i++)
        {
            scanf("%lf%lf%lf%lf", &points[i].x, &points[i].y, &points[i].z,&points[i].r);
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                double len = sqrt((points[i].x - points[j].x)*(points[i].x - points[j].x) + (points[i].y - points[j].y)*(points[i].y - points[j].y) + (points[i].z - points[j].z)*(points[i].z - points[j].z))-points[i].r-points[j].r;
                if (len < 0) len = 0;
                minHeap.push_back(side(i, j, len));
            }
        }
        make_heap(minHeap.begin(), minHeap.end());
        double ans = Kruskal();
        printf("%.3lf\n", ans);
    }
    return 0;
}