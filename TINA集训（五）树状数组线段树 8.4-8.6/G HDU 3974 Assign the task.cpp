##include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

const int MAXN = 50005;

int Start[MAXN], End[MAXN];//每个员工所有下属的开始和结束节点，包含本身
int index;//DFS用记录节点的编号
vector<int> G[MAXN];//保存边

void DFS(int k)
{
    Start[k] = ++index;
    for (int i = 0, len = G[k].size(); i<len; i++)
        DFS(G[k][i]);
    End[k] = index;
}

struct SegmentTree
{
    int L, R, task;
    bool isCover;
    int Mid()
    {
        return (L + R) / 2;
    }
}a[MAXN * 4];

void BuildTree(int r, int L, int R)
{
    a[r].L = L, a[r].R = R;
    a[r].task = -1, a[r].isCover = false;//初始化

    if (L == R)return;

    BuildTree(r << 1, L, a[r].Mid());
    BuildTree(r << 1 | 1, a[r].Mid() + 1, R);
}
void Down(int r)
{//延迟更新
    if (a[r].L != a[r].R && a[r].isCover)
    {
        a[r << 1].isCover = a[r << 1 | 1].isCover = true;
        a[r << 1].task = a[r << 1 | 1].task = a[r].task;
        a[r].isCover = false;
    }
}
void Insert(int r, int L, int R, int task)
{
    Down(r);

    if (a[r].L == L && a[r].R == R)
    {
        a[r].isCover = true;
        a[r].task = task;
        return;
    }

    if (R <= a[r].Mid())
        Insert(r << 1, L, R, task);
    else if (L > a[r].Mid())
        Insert(r << 1 | 1, L, R, task);
    else
    {
        Insert(r << 1, L, a[r].Mid(), task);
        Insert(r << 1 | 1, a[r].Mid() + 1, R, task);
    }
}
int  Query(int r, int k)
{
    Down(r);

    if (a[r].L == a[r].R)
        return a[r].task;

    if (k <= a[r].Mid())
        return Query(r << 1, k);
    else
        return Query(r << 1 | 1, k);
}

int main()
{
    int T, t = 1;

    scanf("%d", &T);

    while (T--)
    {
        int i, N, M, u, v; char s[10];

        scanf("%d", &N);

        for (i = 1; i <= N; i++)
            G[i].clear();
        bool use[MAXN] = { 0 };
        for (i = 1; i<N; i++)
        {
            scanf("%d%d", &u, &v);//v是u的直属上司
            G[v].push_back(u);
            use[u] = true;//表明下属
        }

        index = 0;
        for (i = 1; i <= N; i++)if (!use[i])//总boss
        {
            DFS(i); break;
        }

        BuildTree(1, 1, N);
        printf("Case #%d:\n", t++);

        scanf("%d", &M);

        while (M--)
        {
            scanf("%s", s);

            if (s[0] == 'C')
            {
                scanf("%d", &u);
                printf("%d\n", Query(1, Start[u]));
            }
            else
            {
                scanf("%d%d", &u, &v);
                Insert(1, Start[u], End[u], v);
            }
        }
    }
    return 0;
}