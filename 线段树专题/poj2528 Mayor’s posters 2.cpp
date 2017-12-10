#include<iostream>
#include<memory.h>
#include<algorithm>
using namespace std;
int n, m;
const int maxn = 11111;
int Tree[maxn*2* 4*2];
struct Num
{
    int l;
    int r;
    Num(int ll = 0, int rr = 0) :l(ll), r(rr)
    {
    }
}num[maxn];
bool vis[maxn];
int Hush[maxn*4];
int cnt = 0;
int PosHush(int v)
{
    int l = 0, r = m - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (Hush[mid] == v) return mid;
        else if (Hush[mid] > v) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}
void PushDown(int root, int l, int r)
{
    if (l == r) return;
    if (Tree[root])
    {
        Tree[root * 2 + 1] = Tree[root * 2 + 2] = Tree[root];
        Tree[root] = 0;
    }
}
void Update(int root, int l, int r, int ll, int rr, int v)
{
    PushDown(root, l, r);
    if (l > rr || r < ll) return;
    else if (ll <= l&&r <= rr)
    {
        Tree[root] = v;
        return;
    }
    int mid = (l + r) / 2;
    Update(root * 2 + 1, l, mid, ll, rr, v);
    Update(root * 2 + 2, mid + 1, r, ll, rr, v);
}

void Query(int root, int l, int r)
{
    PushDown(root, l, r);
    if (Tree[root])
    {
        if (!vis[Tree[root]]) cnt++;
        vis[Tree[root]] = true;
        return;
    }
    if (l == r) return;
    int mid = (l + r) / 2;
    Query(root * 2 + 1, l, mid);
    Query(root * 2 + 2, mid + 1, r);
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        m = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &num[i].l, &num[i].r);
            Hush[m++] = num[i].l;
            Hush[m++] = num[i].r;
        }
        sort(Hush, Hush + m);
        int m2 = 1;
        for (int i = 1; i < m; i++)
        {
            if (Hush[i] != Hush[i - 1]) Hush[m2++] = Hush[i];
        }
        m = m2;
        for (int i = 1; i < m2; i++)
        {
            if (Hush[i] != Hush[i - 1] + 1) Hush[m++] = Hush[i - 1] + 1;
        }
        sort(Hush, Hush + m);
        memset(Tree, 0, sizeof(Tree));
        for (int i = 0; i < n; i++)
        {
            int ll = PosHush(num[i].l);
            int rr = PosHush(num[i].r);
            Update(0, 0, m - 1, ll, rr, i + 1);
        }
        memset(vis, 0, sizeof(vis));
        cnt = 0;
        Query(0, 0, m - 1);
        printf("%d\n", cnt);
    }
    return 0;
}