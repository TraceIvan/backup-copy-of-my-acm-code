#include<iostream>
#include<memory.h>
using namespace std;
const int maxn=100010;
struct Node
{
    int sum, d;
    Node(int sum0=0,int d0=0):sum(sum0),d(d0){ }
};
Node Tree[maxn * 4];
int n,q;
void PushDown(int root,int l,int r)
{
    if (Tree[root].d)
    {
        int mid = (r + l) / 2;
        Tree[root * 2 + 1].d = Tree[root * 2 + 2].d = Tree[root].d;
        Tree[root * 2 + 1].sum = Tree[root].d*(mid-l+ 1);
        Tree[root*2+2].sum= Tree[root].d*(r-mid);
    }
    Tree[root].d = 0;
}
void Create(int root,int l,int r)
{
    if (l == r)
    {
        Tree[root].sum = 1;
        return;
    }
    int mid = (l + r) / 2;
    Create(root * 2 + 1, l, mid);
    Create(root * 2 + 2, mid + 1, r);
    Tree[root].sum = Tree[root * 2 + 1].sum + Tree[root * 2 + 2].sum;
}
void Update(int root, int l, int r, int ll, int rr, int v)
{
    if (r < ll || l>rr)return;
    else if (l >= ll&&r <= rr)
    {
        Tree[root].sum = v*(r - l + 1);
        Tree[root].d = v;
        return;
    }
    PushDown(root,l,r);
    int mid = (l + r) / 2;
    Update(root*2+1, l, mid, ll, rr, v);
    Update(root*2+2, mid + 1, r, ll, rr, v);
    Tree[root].sum = Tree[root * 2 + 1].sum + Tree[root * 2 + 2].sum;
}
int Query(int root, int l, int r, int ll, int rr)
{
    PushDown(root,l,r);
    if (r< ll || l>rr) return 0;
    else if (l >= ll&&r <= rr) return Tree[root].sum;
    else
    {
        int mid = (l + r) / 2;
        return Query(root * 2 + 1, l, mid, ll, rr) + Query(root * 2 + 2, mid + 1, r, ll, rr);
    }
}
int main()
{
    int t;
    int k = 1;
    scanf("%d", &t);
    while (t--)
    {
        memset(Tree, 0, sizeof(Tree));
        scanf("%d%d", &n, &q);
        Create(0, 0, n - 1);
        for (int i = 0; i < q; i++)
        {
            int l,r, v;
            scanf("%d%d%d", &l, &r, &v);
            Update(0, 0, n - 1, l-1,r-1, v);
        }
        printf("Case %d: The total value of the hook is %d.\n", k,Query(0,0,n-1,0,n-1));
        k++;
    }
    return 0;
}