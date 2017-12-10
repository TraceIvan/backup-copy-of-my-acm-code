/*
倍增区间来解决区间的开闭问题，对于区间操作：
U:把区间[l,r]覆盖成1
I:把[-∞,l)(r,∞]覆盖成0
D:把区间[l,r]覆盖成0
C:把[-∞,l)(r,∞]覆盖成0 , 且[l,r]区间0/1互换
S:[l,r]区间0/1互换
*/
#include<iostream>
using namespace std;
const int maxn =14;
struct Node
{
    int tag; //纪录区间点的值。-1表示该区间为杂色  
    bool rev; //标记该区间是否翻转
}Tree[maxn*6];
void Create(int root, int l, int r)
{
    
    if (l == r)
    {
        Tree[root].tag = 0;
        Tree[root].rev = false;
        return;
    }
    int mid = (l + r) / 2;
    Create(root * 2 + 1, l, mid);
    Create(root * 2 + 2, mid + 1, r);
    Tree[root].tag = 0, Tree[root].rev = false;
}
void PushDown(int root, int l, int r)
{
    if (l == r)
    {//考虑单点
        if (Tree[root].rev)
        {//判断是否需要翻转异或
            Tree[root].tag ^= 1;
            Tree[root].rev = false;
        }
        return;
    }
    else
    {
        if (Tree[root].tag != -1)
        {//表示需要把当前区间全部覆盖或全部取消覆盖
            if (Tree[root].rev) Tree[root].tag ^= 1;
            Tree[root * 2 + 1].tag = Tree[root * 2 + 2].tag = Tree[root].tag;
            Tree[root].rev = Tree[root * 2 + 1].rev = Tree[root * 2 + 2].rev = false;
            Tree[root].tag = -1;//表示当前区间已经向下更新，而且该区间为纯区间
        }
        if (Tree[root].rev)
        {//如果需要翻转
            Tree[root].rev = false;
            if (Tree[root * 2 + 1].tag == -1)
                Tree[root * 2 + 1].rev ^= 1;//如果标记为-1，则表示纯区间
            else Tree[root * 2 + 1].tag ^= 1;//否则标记，准备之后向下更新
            if (Tree[root * 2 + 2].tag == -1)
                Tree[root * 2 + 2].rev ^= 1;
            else Tree[root * 2 + 2].tag^= 1;
        }
    }
}
void Update(int root, int l, int r, int ll, int rr, int v)
{
    if (l > r) return;
    if (l > rr || r < ll) return;
    if (l >= ll &&r<=rr)
    {
        if (v < 2)// 覆盖或取消覆盖操作，把异或标记清空
        {
            Tree[root].tag = v;
            Tree[root].rev = false;
        }
        else//区间内异或操作
        {
            if (Tree[root].tag != -1)
            {//如果该区间还需要进行覆盖或取消覆盖操作，则直接将该操作异或，等待向下更新
                Tree[root].tag ^= 1;
            }
            else Tree[root].rev ^= 1;//否则改变异或标记，等待向下更新
        }
        return;
    }
    PushDown(root, l, r);
    int mid = (l + r) / 2;
    Update(root * 2 + 1, l, mid, ll, rr, v);
    Update(root * 2 + 2, mid + 1, r, ll, rr, v);
}
bool vis[maxn];
void Display(int root, int l, int r)
{
    PushDown(root, l, r);
    if (Tree[root].tag != -1)
    {//当前区间为纯区间
        if (Tree[root].tag == 1)
        {//且被选择覆盖
            for (int i = l; i <= r; i++) vis[i] = true;
        }
        return;
    }
    if (l == r) return;
    int mid = (l + r) / 2;
    Display(root * 2 + 1, l, mid);
    Display(root * 2 + 2, mid + 1, r);
}
int main()
{
    freopen("in.txt", "r", stdin);
    Create(0, 0, maxn);
    int l, r;
    char op, a, b;
    while (~scanf("%c %c%d,%d%c\n", &op, &a, &l, &r, &b))
    {
        getchar();
        l = l * 2, r = r * 2;
        if (a == '(') l++;
        if (b == ')') r--;
        switch (op)
        {
        case 'U':Update(0, 0, maxn, l, r, 1);
            break;
        case 'I':Update(0, 0, maxn, 0, l - 1, 0);
            Update(0, 0, maxn, r + 1, maxn, 0);
            break;
        case 'D':Update(0, 0, maxn, l, r, 0);
            break;
        case 'C':
            Update(0, 0, maxn, 0, l - 1, 0);
            Update(0, 0, maxn, r + 1, maxn, 0);
            Update(0, 0, maxn, l, r, 2);
            break;
        case 'S':
            Update(0, 0, maxn, l, r, 2);
            break;
        }

    }
    memset(vis, 0, sizeof(vis));
    Display(0, 0, maxn);
    bool flag = false;
    for (int i = 0; i < maxn; i++)
    {//按顺序输出被选择覆盖的各个连续的区间
        if (!vis[i]) continue;
        if (flag) printf(" ");
        flag = true;
        int start = i, ed;
        while (vis[i] && i < maxn) i++;
        printf("%c%d,%d%c ", start & 1 ? '(' : '[', start / 2, i / 2, (i - 1) & 1 ? ')' : ']');
    }
    if (!flag) printf("empty set");
    printf("\n");
    return 0;
}