//线段树-区间最值，单点更新，区间查询
#include<iostream>
#include<memory.h>
#include<algorithm>
using namespace std;
int n, m;
const int maxn = 200010;
int Score[maxn];
int Tree[4 * maxn];
void Create(int root, int l, int r)
{
    if (l == r)
    {
        Tree[root] = Score[l];
        return;
    }
    int mid = (l + r) / 2;
    Create(root * 2 + 1, l, mid);
    Create(root * 2 + 2, mid + 1, r);
    Tree[root] = max(Tree[root * 2 + 1], Tree[root * 2 + 2]);
}
void Update(int root, int l, int r, int pos, int v)
{
    if (l > pos || r < pos) return;
    else if (l == r&&l == pos)
    {
        Tree[root] = v;
        return;
    }
    else
    {
        int mid = (l + r) / 2;
        Update(root * 2 + 1, l, mid, pos, v);
        Update(root * 2 + 2, mid + 1, r, pos, v);
        Tree[root] = max(Tree[root * 2 + 1], Tree[root * 2 + 2]);
    }
}
int Query(int root, int l, int r, int ll, int rr)
{
    if (l > rr || r < ll) return 0;
    else if (l >= ll&&r <= rr) return Tree[root];
    else
    {
        int mid = (l + r) / 2;
        return max(Query(root * 2 + 1, l, mid, ll, rr), Query(root * 2 + 2, mid + 1, r, ll, rr));
    }

}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        memset(Tree, 0, sizeof(Tree));
        for (int i = 0; i < n; i++) scanf("%d",&Score[i]);
        char c[5];
        Create(0, 0, n - 1);
        for (int i = 0; i < m; i++)
        {
            scanf("%s",c);
            switch (c[0])
            {
            case 'Q':
                int ll, rr;
                scanf("%d%d", &ll, &rr);
                printf("%d\n",Query(0,0,n - 1,ll-1,rr-1));
                break;
            case 'U':
                int id, v;
                scanf("%d%d", &id, &v);
                Update(0, 0, n - 1, id - 1, v);
                break;
            }
        }
    }
    return 0;
}