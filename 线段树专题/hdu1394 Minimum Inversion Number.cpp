#include<iostream>
#include<memory.h>
#include<algorithm>
using namespace std;
const int maxn = 5010;
int num[maxn];
int Tree[maxn * 4];//Tree[root]是指在[l,r]区间内比l大，小于等于r的个数
int n;
void Update(int root, int l, int r, int pos)
{
    if (l > pos || r < pos)return;
    else if (l == r&&l == pos)
    {
        Tree[root]++;
        return;
    }
    else
    {
        int mid = (l + r) / 2;
        Update(root * 2 + 1, l, mid, pos);
        Update(root * 2 + 2, mid + 1, r, pos);
        Tree[root] = Tree[root * 2 + 1] + Tree[root * 2 + 2];
    }
}
int Query(int root, int l, int r, int ll, int rr)
{
    if (r<ll || l>rr) return 0;
    else if (l >= ll&&r <= rr) return Tree[root];
    else
    {
        int mid = (l + r) / 2;
        return Query(root * 2 + 1, l, mid, ll, rr) + Query(root * 2 + 2, mid + 1, r, ll, rr);
    }
}
int main()
{
    while (~scanf("%d", &n))
    {
        memset(Tree, 0, sizeof(Tree));
        int Sum = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &num[i]);
            Sum += Query(0, 0, n - 1, num[i], n - 1);//先询问[num[i],n-1]的数目，即求当前比num[i]大的数的个数
            Update(0, 0, n - 1, num[i]);//再放入num[i]
        }
        int ans = Sum;
        for (int i = 0; i < n - 1; i++)
        {
            Sum += n - 1 - num[i] - num[i];//将num[i]移到后面，比num[i]大的有n - 1 - num[i]个，比num[i]小的有num[i]个，移到最后，新增n - 1 - num[i]个逆序对，减少num[i]个逆序对
            ans = min(ans, Sum);
        }
        printf("%d\n", ans);
    }
    return 0;
}