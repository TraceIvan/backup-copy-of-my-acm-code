#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n;
const int maxn = 110;
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

struct point
{
    int x;
    int y;
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
    while (cnt < n&&!minHeap.empty())
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
    if (minHeap.empty() && cnt < n)return -1;
    else return ans;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        minHeap.clear();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d",&points[i].x, &points[i].y);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                double dis = sqrt((points[i].x - points[j].x)*(points[i].x - points[j].x) + (points[i].y - points[j].y)*(points[i].y - points[j].y));
                if (dis < 10 || dis>1000)continue;
                minHeap.push_back(side(i, j, dis));
            }
        }
        make_heap(minHeap.begin(), minHeap.end());
        double ans = Kruskal();
        if(ans>0)printf("%.1lf\n", ans*100);
        else printf("oh!\n");
    }
    return 0;
}