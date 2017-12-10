//线段树单点更新，区间查询
#include<iostream>
using namespace std;
const int maxn = 50010;
int N;
int barracks[maxn];
int Tree[4 * maxn];
void Create(int root, int l, int r)
{
    if (l == r)
    {
        Tree[root] = barracks[l];
        return;
    }
    int mid = (l + r) / 2;
    Create(root * 2 + 1, l, mid);
    Create(root * 2 + 2, mid + 1, r);
    Tree[root] = Tree[root * 2 + 1] + Tree[root * 2 + 2];
}
void Update(int root, int l, int r, int pos, int v)
{//在第i个营地加上v个人
    if (l > pos || r < pos) return;
    else if (l == r&&l == pos)
    {
        Tree[root] += v;
        return;
    }
    else
    {
        int mid = (l + r) / 2;
        Update(root * 2 + 1, l, mid, pos, v);
        Update(root * 2 + 2, mid + 1, r, pos, v);
        Tree[root] = Tree[root * 2 + 1] + Tree[root * 2 + 2];
    }
}
int Query(int root, int l, int r, int ll, int rr)
{//查询区间ll~rr的总人数
    if (l > rr || r < ll) return 0;
    else if (r <= rr&&l >= ll) return Tree[root];
    else
    {
        int mid = (l + r) / 2;
        return Query(root * 2 + 1, l, mid, ll, rr) + Query(root * 2 + 2, mid + 1, r, ll, rr);
    }
}
int main()
{
    int T;
    int k = 1;
    scanf("%d", &T);
    while (T--)
    {
        memset(Tree, 0, sizeof(Tree));
        scanf("%d", &N);
        for (int i = 0; i < N; i++) scanf("%d", &barracks[i]);
        Create(0, 0, N - 1);
        char op[10];
        printf("Case %d:\n", k);
        while (scanf("%s", op))
        {
            if (op[0] == 'E')
            {
                break;
            }
            else if (op[0] == 'A')
            {
                int i, j;
                scanf("%d%d", &i, &j);
                Update(0, 0, N - 1, i - 1, j);
            }
            else if (op[0] == 'S')
            {
                int i, j;
                scanf("%d%d", &i, &j);
                j = -j;
                Update(0, 0, N - 1, i - 1, j);
            }
            else
            {
                int i, j;
                scanf("%d%d", &i, &j);
                printf("%d\n", Query(0, 0, N - 1, i - 1, j - 1));
            }
        }
        k++;
    }
    return 0;
}