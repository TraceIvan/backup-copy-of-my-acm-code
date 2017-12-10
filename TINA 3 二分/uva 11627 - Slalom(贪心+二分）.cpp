#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int W, vh, N,S;
const int maxn = 100010;
const int maxs = 1000010;
struct Gate
{
    int x, y;
}gt[maxn];
int s[maxs];
bool Cmp(const Gate&a, const Gate&b)
{
    return a.y < b.y;
}
bool Judge(int v)
{
    double l = gt[N-1].x, r = gt[N-1].x + W;
    for (int i = N - 2; i >= 0; i--)//从下往上递归，找出每次可达区间，同时判断是否可行。若可行，则更新当前区间
    {
        int th = gt[i + 1].y - gt[i].y;
        double tt = 1.0*th / v;
        double tl = l - tt*vh;
        double tr = r + tt*vh;
        if (tr < gt[i].x) return false;
        if (tl > gt[i].x + W) return false;
        if (gt[i].x> tl) l = gt[i].x;
        else l = tl;
        if (gt[i].x + W<tr) r = gt[i].x + W;
        else r = tr;
    }
    return true;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &W, &vh, &N);
        for (int i = 0; i < N; i++) scanf("%d%d", &gt[i].x, &gt[i].y);
        scanf("%d", &S);
        for (int i = 0; i < S; i++) scanf("%d", &s[i]);
        sort(s, s+S);
        sort(gt, gt + N, Cmp);
        if (!Judge(s[0])) printf("IMPOSSIBLE\n");//如果连速度最慢的(其水平可达区间最大)都不可行，则后面速度比它快的都不可行
        else if(Judge(s[S-1]))//如果速度最大的都可行，则无需再判断速度比其小的
        {
            printf("%d\n", s[S-1]);
        }
        else
        {
            int L = 0, R = S-1;
            while (R >= L)
            {
                int mid = (L + R) / 2;
                if (Judge(s[mid])) L = mid+1;
                else R = mid - 1;
            }
            printf("%d\n", s[R]);
        }
    }
    return 0;
}
