//利用并查集形成集合树,利用sum数组记录集合树中当前节点i到根之间的边的权值和,如果当前两个节点不在同一棵集合树中,那么通过两个集合树合并,调整权值,使能够保证合法的,所以只需要合并,将一棵树的根变为另一棵树的根的子节点,然后建边,因为f[i]<i,i<j,f[j]<j,所以s=sum[j]+sum[f[j]]-sum[i]因为当前j的根是f[j],所以要加上新加的边权,那么新的边权既可以通过这个方程求取即可
#include<stdio.h>
#define MAXN 200010
int f[MAXN], r[MAXN];
int find(int x)
{
    if (x == f[x])
        return f[x];
    int t = find(f[x]);
    r[x] = r[x] + r[f[x]];//这里首先要对这个递归的过程很了解，当递归到某一层时，x还未接到根节点上，所以r[x]表示的是x到f[x]的距离，经上一步操作，f[x]已经接到根节点上了，所以r[f[x]]表示的是父节点到根节点的距离所以x到根节点的距离就直接等于r[x]+r[f[x]]
    f[x] = t;
    return f[x];
}
int fun(int x, int y)
{
    if (x>y)
        return x - y;
    else y - x;
}
int Union(int x, int y, int sum)
{//传进来时x<y
    int a = find(x);
    int b = find(y);
    if (a == b)
    {
        if (fun(r[x], r[y]) == sum)
            return 0;
        else return 1;
    }
    else
    {
        f[a] = b;
        r[a] = r[y] + sum - r[x];//r[y]表示y到b的距离，r[x]表示x到a的距离，sum表示x到y的距离，现在要将a接到b后面，那么r[a]很表示a到b的距离,很明显就是这个式子了   
        return 0;
    }
}
int main()
{
    int n, m, i, ans, a, b, s;
    while (scanf("%d %d", &n, &m) != EOF)
    {
        ans = 0;
        for (i = 0; i <= n; i++)
        {
            f[i] = i;
            r[i] = 0;
        }
        for (i = 1; i <= m; i++)
        {
            scanf("%d %d %d", &a, &b, &s);
            a--;//左区间减一，方便处理
            if (Union(a, b, s))
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}