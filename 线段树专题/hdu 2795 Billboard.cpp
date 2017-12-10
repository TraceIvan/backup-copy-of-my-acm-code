#include<iostream>
#include<algorithm>
using namespace std;
int h, w, n;
const int maxn = 200010;
int Tree[maxn * 4];
void Create(int root, int l, int r)
{
    if (l == r)
    {
        Tree[root] = w;
        return;
    }
    int mid = (l + r) / 2;
    Create(root * 2 + 1, l, mid);
    Create(root * 2 + 2, mid + 1, r);
    Tree[root] = max(Tree[root * 2 + 1], Tree[root * 2 + 2]);
}
int Query(int root, int l, int r, int v)
{
    if (l == r)
    {
        Tree[root] -= v;
        return l+1;
    }
    else
    {
        int mid = (l + r) / 2;
        int ans;
        if (Tree[root * 2 + 1] >= v) ans=Query(root * 2 + 1, l, mid, v);
        else ans=Query(root * 2 + 2, mid + 1, r, v);
        Tree[root] = max(Tree[root * 2 + 1], Tree[root * 2 + 2]);
        return ans;
    }
}
int main()
{
    while (~scanf("%d%d%d", &h, &w, &n))
    {
        memset(Tree, 0, sizeof(Tree));
        if (h > n) h = n;
        Create(0,0,h - 1);
        for (int i = 0; i < n; i++)
        {
            int len;
            scanf("%d", &len);
            if (Tree[0] < len) printf("-1\n");
            else printf("%d\n", Query(0, 0, h - 1, len));
        }
    }
    return 0;
}