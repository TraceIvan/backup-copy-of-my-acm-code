#include<iostream>
#include<vector>
using namespace std;
int index;//给员工树从上到下依次编号
int n, m;
const int maxn = 50100;
struct node
{
    int task;
    int d;
    node(int tt=-1,int dd=-1):task(tt),d(dd){ }
}tree[maxn<<2];

vector<int>belong[maxn];
bool ischild[maxn];

int start[maxn];
int ed[maxn];

void DFS(int x)
{
    start[x] = index++;
    int sz = belong[x].size();
    for (int i = 0; i < sz; i++)
    {
        DFS(belong[x][i]);//因为不会重复，所以不用判断是否走过
    }
    ed[x] = index - 1;
}
void Create(int root, int l, int r)
{
    if (l == r)
    {
        tree[root].task = -1;
        tree[root].d = -1;
        return;
    }
    int mid = (l + r) / 2;
    Create(root * 2 + 1, l, mid);
    Create(root * 2 + 2, mid + 1, r);
}
void PushDown(int root, int l, int r)
{
    if (tree[root].d == 1 && l != r)
    {
        tree[root * 2 + 1].d = tree[root * 2 + 2].d = tree[root].d;
        tree[root * 2 + 1].task = tree[root * 2 + 2].task = tree[root].task;
    }
    tree[root].d = -1;
}
void Update(int root, int l, int r, int ll,int rr, int tsk)
{
    if (l > rr || r < ll)return;
    if (l>=ll&&r<=rr)
    {
        tree[root].task = tsk;
        tree[root].d = 1;
        return;
    }
    PushDown(root,l,r);
    int mid = (l + r) / 2;
    Update(root * 2 + 1, l, mid,ll,rr, tsk);
    Update(root * 2 + 2, mid + 1, r,ll,rr, tsk);
}

int Query(int root, int l, int r, int pos)
{
    PushDown(root, l, r);
    if (l == r&&l == pos)return tree[root].task;
    int mid = (l + r) / 2;
    if (pos <= mid)return Query(root * 2 + 1, l, mid, pos);
    else return Query(root * 2 + 2, mid + 1, r, pos);
}
int main()
{
    int T;
    scanf("%d", &T);
    int Case = 1;
    while (T--)
    {
        printf("Case #%d:\n", Case++);
        scanf("%d", &n);
        for (int i = 0; i <= n; i++) belong[i].clear();
        memset(ischild, 0, sizeof(ischild));
        for (int i = 0; i < n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);//v是u的上司
            belong[v].push_back(u);
            ischild[u] = true;
        }
        index = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!ischild[i])
            {
                DFS(i);
                break;
            }
        }
        //Create(0, 0, index - 1);

memset(tree, -1, sizeof(tree));
        scanf("%d", &m);
        char op[3];
        for (int i = 0; i < m; i++)
        {
            scanf("%s", op);
            if (op[0] == 'T')
            {
                int x, tsk;
                scanf("%d%d", &x, &tsk);
                Update(0,0,index-1,start[x],ed[x],tsk);
            }
            else
            {
                int x;
                scanf("%d", &x);
                printf("%d\n", Query(0, 0, index - 1, start[x]));
            }
        }
    }
    return 0;
}