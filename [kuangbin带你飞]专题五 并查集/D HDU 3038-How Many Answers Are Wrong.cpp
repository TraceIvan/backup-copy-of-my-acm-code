//���ò��鼯�γɼ�����,����sum�����¼�������е�ǰ�ڵ�i����֮��ıߵ�Ȩֵ��,�����ǰ�����ڵ㲻��ͬһ�ü�������,��ôͨ�������������ϲ�,����Ȩֵ,ʹ�ܹ���֤�Ϸ���,����ֻ��Ҫ�ϲ�,��һ�����ĸ���Ϊ��һ�����ĸ����ӽڵ�,Ȼ�󽨱�,��Ϊf[i]<i,i<j,f[j]<j,����s=sum[j]+sum[f[j]]-sum[i]��Ϊ��ǰj�ĸ���f[j],����Ҫ�����¼ӵı�Ȩ,��ô�µı�Ȩ�ȿ���ͨ�����������ȡ����
#include<stdio.h>
#define MAXN 200010
int f[MAXN], r[MAXN];
int find(int x)
{
    if (x == f[x])
        return f[x];
    int t = find(f[x]);
    r[x] = r[x] + r[f[x]];//��������Ҫ������ݹ�Ĺ��̺��˽⣬���ݹ鵽ĳһ��ʱ��x��δ�ӵ����ڵ��ϣ�����r[x]��ʾ����x��f[x]�ľ��룬����һ��������f[x]�Ѿ��ӵ����ڵ����ˣ�����r[f[x]]��ʾ���Ǹ��ڵ㵽���ڵ�ľ�������x�����ڵ�ľ����ֱ�ӵ���r[x]+r[f[x]]
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
{//������ʱx<y
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
        r[a] = r[y] + sum - r[x];//r[y]��ʾy��b�ľ��룬r[x]��ʾx��a�ľ��룬sum��ʾx��y�ľ��룬����Ҫ��a�ӵ�b���棬��ôr[a]�ܱ�ʾa��b�ľ���,�����Ծ������ʽ����   
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
            a--;//�������һ�����㴦��
            if (Union(a, b, s))
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}