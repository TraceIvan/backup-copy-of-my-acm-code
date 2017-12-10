#include<iostream>
#include<cmath>
using namespace std;
const int maxn = 100100;
long long tree[maxn*4];
int n,m;
void Build(int root, int l, int r)
{
    if (l == r)
    {
        scanf("%lld", &tree[root]);
        return;
    }
    int mid = (l + r) / 2;
    Build(root * 2 + 1, l, mid);
    Build(root * 2 + 2, mid + 1, r);
    tree[root] = tree[root * 2 + 1] + tree[root * 2 + 2];
}
void Update(int root, int l, int r, int ll, int rr)
{
    if (l > rr || r < ll) return;
    if (l >= ll&&r <= rr&&l == r)
    {
        if (tree[root] > 1) tree[root] = (long long)sqrt(1.0*tree[root]);
        return;
    }
    int mid = (l + r) / 2;
    Update(root * 2 + 1, l, mid, ll, rr);
    Update(root * 2 + 2, mid + 1,r, ll, rr);
    tree[root] = tree[root * 2 + 1] + tree[root * 2 + 2];
}
long long Query(int root, int l, int r, int ll, int rr)
{
    if (l > rr || r < ll)return 0;
    if (l >= ll&&r <= rr)return tree[root];
    int mid = (l + r) / 2;
    return Query(root * 2 + 1, l, mid, ll, rr) + Query(root * 2 + 2, mid + 1, r, ll, rr);
}
int main()
{
    int Case = 1;
    while (~scanf("%d",&n))
    {
        printf("Case #%d:\n", Case++);
        Build(0, 0, n - 1);
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            int t, x, y;
            scanf("%d%d%d", &t, &x, &y);
            if (x > y)
            {
                int t = x;
                x = y;
                y = t;
            }
            if (t == 0)
            {
                if (Query(0, 0, n - 1, x - 1, y - 1) != y - x + 1)//判断一下是否需要继续更新
                    Update(0, 0, n - 1, x - 1, y - 1);
            }
            else printf("%lld\n", Query(0, 0, n - 1, x - 1, y - 1));
        }
        printf("\n");
    }
    return 0;
}