#include<iostream>
#include<memory.h>
using namespace std;
typedef long long LL;
const int maxn = 200050;
struct Node
{
    LL sum;
    LL d;
    Node(LL s=0,LL d0=0):sum(s),d(d0){ }
}Tree[maxn*4];
int n, q;
void PushDown(int root, int l, int r)
{
    if (Tree[root].d)
    {
        int mid = (l + r) / 2;
        Tree[root * 2 + 1].d += Tree[root].d;
        Tree[root * 2 + 2].d += Tree[root].d;
        Tree[root * 2 + 1].sum += 1ll*Tree[root].d*(mid - l + 1);
        Tree[root * 2 + 2].sum += 1ll*Tree[root].d*(r - mid);
    }
    Tree[root].d = 0;
}
void PushUp(int root)
{
    Tree[root].sum = Tree[root * 2 + 1].sum + Tree[root * 2 + 2].sum;
}
void Create(int root, int l, int r)
{
    if (l == r)
    {
        scanf("%lld", &Tree[root].sum);
        return;
    }
    int mid = (l + r) / 2;
    Create(root * 2 + 1, l, mid);
    Create(root * 2 + 2, mid + 1, r);
    PushUp(root);
}

void Update(int root, int l, int r, int ll, int rr, int v)
{
    if (l > rr || r < ll) return;
    else if (l >= ll&&r <= rr)
    {
        Tree[root].sum += 1ll*v*(r - l + 1);
        Tree[root].d += v;
        return;
    }
    PushDown(root, l, r);
    int mid = (l + r) / 2;
    Update(root * 2 + 1, l, mid, ll, rr, v);
    Update(root * 2 + 2, mid + 1, r, ll, rr, v);
    PushUp(root);
}
LL Query(int root, int l, int r, int ll, int rr)
{
    PushDown(root, l, r);
    if (l > rr || r < ll) return 0;
    else if (l >= ll&&r <= rr)
    {
        return Tree[root].sum;
    }
    else
    {
        int mid = (l + r) / 2;
        LL ans = Query(root * 2 + 1, l, mid, ll, rr) + Query(root * 2 + 2, mid + 1, r, ll, rr);
        PushUp(root);
        return ans;
    }
}
int main()
{
    while (~scanf("%d%d", &n, &q))
    {
        memset(Tree, 0, sizeof(Tree));
        Create(0, 0, n - 1);
        char c[2];
        for (int i = 0; i < q; i++)
        {
            scanf("%s", c);
            if (c[0] == 'Q')
            {
                int ll, rr;
                scanf("%d%d", &ll, &rr);
                printf("%lld\n", Query(0, 0, n - 1, ll - 1, rr - 1));
            }
            else
            {
                int ll, rr, v;
                scanf("%d%d%d", &ll, &rr, &v);
                Update(0, 0, n - 1, ll-1, rr-1, v);
            }
        }
    }
    return 0;
}