#include<iostream>
#include<memory.h>
#include<algorithm>
using namespace std;
const int maxn = 5010;
int num[maxn];
int Tree[maxn * 4];//Tree[root]��ָ��[l,r]�����ڱ�l��С�ڵ���r�ĸ���
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
            Sum += Query(0, 0, n - 1, num[i], n - 1);//��ѯ��[num[i],n-1]����Ŀ������ǰ��num[i]������ĸ���
            Update(0, 0, n - 1, num[i]);//�ٷ���num[i]
        }
        int ans = Sum;
        for (int i = 0; i < n - 1; i++)
        {
            Sum += n - 1 - num[i] - num[i];//��num[i]�Ƶ����棬��num[i]�����n - 1 - num[i]������num[i]С����num[i]�����Ƶ��������n - 1 - num[i]������ԣ�����num[i]�������
            ans = min(ans, Sum);
        }
        printf("%d\n", ans);
    }
    return 0;
}