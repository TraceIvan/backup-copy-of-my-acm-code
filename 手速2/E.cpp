#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 200010;
const int INF = 0x7fffffff;
struct node
{
    int l;
    int r;
    int d;
    int v;
    node(int ll=0,int rr=0,int dd=0,int vv=0):l(ll),r(rr),d(dd),v(vv){ }
}vt1[maxn], vt2[maxn];
bool Cmp1(const node&a, const node&b)
{
    if (a.l == b.l)return a.r < b.r;
    else return a.l < b.l;
}
bool Cmp2(const node&a, const node&b)
{
    if (a.r == b.r)return a.l>b.l;
    else return a.r > b.r;
}
int main()
{
    int n, x;
    while (~scanf("%d%d", &n, &x))
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d%d", &vt1[i].l, &vt1[i].r, &vt1[i].v);
            vt1[i].d = vt1[i].r - vt1[i].l + 1;
            vt2[i] = vt1[i];
        }
        int pos1 = 1, pos2 = n - 1;
        int ans = INF;
        int v1=-1, v2=-1;
        while (1)
        {
            if (vt1[pos1].r >= vt2[pos2].l)break;
            if(pos1==1) v1=
        }
    }


    return 0;
}