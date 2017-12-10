#include<iostream>
#include<memory.h>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn = 8010;
int tree[maxn << 2];
int n;
int tg[maxn];
int cnt[maxn];
void PushDown(int root,int l,int r)
{
    if (tree[root]!= -1)
    {
        tree[root * 2 + 1]= tree[root * 2 + 2]= tree[root];
        tree[root] = -1;
    }
}
void Update(int root, int l, int r, int ll, int rr, int color)
{
    if (l > rr || r < ll) return;
    if (ll <= l&&r <= rr)
    {
        tree[root] = color;
        return;
    }
    PushDown(root,l,r);
    int mid = (l + r) / 2;
    Update(root * 2 + 1, l, mid, ll, rr, color);
    Update(root * 2 + 2, mid + 1, r, ll, rr, color);
    if (tree[root * 2 + 1]== tree[root * 2 + 2]&& tree[root * 2 + 1]!=-1) tree[root] = tree[root * 2 + 1];
    else tree[root] = -1;
}
void Query(int root, int l, int r)
{
    //PushDown(root,l,r);
    if (tree[root] != -1)
    {
        for (int i = l; i <= r; i++)
        {
            tg[i] = tree[root];
        }
        return;
    }
    if (l == r)return;
    int mid = (l + r) / 2;
    Query(root * 2 + 1, l, mid);
    Query(root * 2 + 2, mid + 1, r);
}
int main()
{
    while (~scanf("%d", &n))
    {
        memset(tree, -1, sizeof(tree));
        memset(tg, -1, sizeof(tg));
        for (int i = 0; i < n; i++)
        {
            int l, r, color;
            scanf("%d%d%d", &l, &r, &color);
            Update(0, 0, maxn, l, r-1, color);//输入涂色范围为端点，建立时涂色范围改为区域
        }
        Query(0, 0, maxn);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i < maxn; i++)
        {
            if (tg[i] != tg[i - 1])
            {
                if (tg[i - 1] != -1)
                {
                    cnt[tg[i - 1]]++;
                }
            }
        }
        for (int i = 0; i < maxn; i++)
        {
            if (cnt[i]) printf("%d %d\n", i, cnt[i]);
        }
        printf("\n");
    }
    return 0;
}
