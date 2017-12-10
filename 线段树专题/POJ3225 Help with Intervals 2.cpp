/*
倍增区间来解决区间的开闭问题，对于区间操作：
U:把区间[l,r]覆盖成1
I:把[-∞,l)(r,∞]覆盖成0
D:把区间[l,r]覆盖成0
C:把[-∞,l)(r,∞]覆盖成0 , 且[l,r]区间0/1互换
S:[l,r]区间0/1互换

当一个区间被覆盖后,不管之前有没有异或标记都没有意义了
所以当一个节点得到覆盖标记时把异或标记清空
而当一个节点得到异或标记的时候,先判断覆盖标记,如果是0或1,直接改变一下覆盖标记,不然的话改变异或标记
开区间闭区间只要数字乘以2就可以处理(偶数表示端点,奇数表示两端点间的区间)
*/
#include <cstdio>
#include <iostream>
#include<memory.h>
using namespace std;
const int M = 70000 * 2;
struct segment
{
    int tag; //1表示区间所有被覆盖，0表示区间都没有覆盖。-1表示该区间已经更新
    bool rev; //异或标记
}tree[M << 2];
void build(int root, int l, int r)
{
    tree[root].tag = 0;//初始化
    tree[root].rev = false;
    if (l == r) return;
    int m = (l + r) / 2;
    build(root*2+1, l, m);
    build(root*2+2, m + 1, r);
}
void pushdown(int root,int l,int r)
{
    if (l == r)
    {
        if (tree[root].rev) //需要翻转的话就翻转
        {
            tree[root].rev = false;
            tree[root].tag ^= 1;
        }
        return;
    }
    if (tree[root].tag != -1) //该区间为纯色
    {
        if (tree[root].rev) tree[root].tag ^= 1;
        tree[root*2+1].tag = tree[root*2+2].tag = tree[root].tag;
        tree[root].tag = -1;//已经下放
        tree[root*2+1].rev = tree[root*2+2].rev = tree[root].rev = false;
    }
    if (tree[root].rev)//需要异或
    {
        tree[root].rev = false;
        if (tree[root*2+1].tag == -1)
            tree[root*2+1].rev ^= 1;//下放
        else tree[root*2+1].tag ^= 1;//否则直接标记该区间整个是否覆盖
        if (tree[root*2+2].tag == -1)
            tree[root*2+2].rev ^= 1;
        else tree[root*2+2].tag ^= 1;
    }
}
void update(int root,int l,int r,int ll, int rr, int v)
{
    if (l > rr || r < ll)return;
    if (l >= ll&&r <= rr)
    {
        if (v<2) //赋值操作
        {
            tree[root].rev = false;
            tree[root].tag = v;
        }
        else //翻转操作
        {
            if (tree[root].tag != -1) //区间为纯色,直接翻转即可
                tree[root].tag ^= 1;
            else tree[root].rev ^= 1; //异或
        }
        return;
    }
    int m = (l + r) / 2;
    pushdown(root,l,r);//向下更新子树
    if (rr <= m) update(root*2+1, l, m,ll,rr, v);
    else if (ll>m) update(root*2+2, m+1, r,ll,rr, v);
    else
    {
        update(root*2+1, l, m,ll,rr, v);
        update(root*2+2, m + 1, r,ll,rr, v);
    }
}
bool vis[M];
void Query(int root,int l,int r)
{
    
    if (tree[root].tag != -1)
    {
        if (tree[root].tag == 1)
            for (int i = l; i <= r; i++)
                vis[i] = true;
        return;
    }
    pushdown(root,l,r);
    int mid=(l + r)/2;
    Query(root*2+1,l,mid);
    Query(root*2+2,mid+1,r);
}
int main()
{
    //freopen("in.txt", "r", stdin);
    build(0, 0, M);
    int l, r;
    char op, a, b;
    while (scanf("%c %c%d,%d%c", &op, &a, &l, &r, &b) != -1)
    {
        getchar();//读入换行符
        l <<= 1; if (a == '(') l++;//开闭区间处理
        r <<= 1; if (b == ')') r--;
        switch (op)
        {
        case 'U':update(0,0,M, l, r, 1); break;
        case 'I':update(0,0,M, 0, l - 1, 0); update(0, 0, M, r + 1, M, 0); break;
        case 'D':update(0, 0, M, l, r, 0); break;
        case 'C':update(0, 0, M, 0, l - 1, 0); 
            update(0, 0, M, r + 1, M, 0); 
            update(0, 0, M, l, r, 2); 
            break;
        case 'S':update(0, 0, M, l, r, 2);
        }
    }
    memset(vis, 0, sizeof(vis));
    Query(0, 0, M);
    bool flag = true;
    for (int i = 0; i<M; i++)
    {
        if (!vis[i]) continue;
        flag = false;
        int start = i, end;
        while (vis[i] && i<M) i++;
        printf("%c%d,%d%c ", start & 1 ? '(' : '[', start / 2, i / 2, (i - 1) & 1 ? ')' : ']');
    }
    if (flag) puts("empty set");
    else printf("\n");
    return 0;
}
