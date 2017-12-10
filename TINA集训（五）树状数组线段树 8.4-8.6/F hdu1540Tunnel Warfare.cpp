#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
using namespace std;

const int maxn = 50000 + 10;

int n, m;
int s[maxn], top;//sΪģ��ջ
//����ϲ�
struct node
{
    int l, r;
    int ls, rs, ms;//ls,�������������䣬rs�Ҷ�����������䣬ms���������ڵ������������
} a[maxn << 2];

void init(int l, int r, int root)
{
    a[root].l = l;
    a[root].r = r;
    a[root].ls = a[root].rs = a[root].ms = r - l + 1;
    if (l != r)
    {
        int mid = (l + r) >> 1;
        init(l, mid, root * 2);
        init(mid + 1, r, 2 * root + 1);
    }
}

void insert(int root, int t, int x)
{
    if (a[root].l == a[root].r)
    {
        if (x == 1)
            a[root].ls = a[root].rs = a[root].ms = 1;//�޸�
        else
            a[root].ls = a[root].rs = a[root].ms = 0;//�ƻ�
        return;
    }
    int mid = (a[root].l + a[root].r) >> 1;
    if (t <= mid)
        insert(2 * root, t, x);
    else
        insert(2 * root + 1, t, x);
    a[root].ls = a[2 * root].ls;//������
    a[root].rs = a[2 * root + 1].rs;//������
    a[root].ms = max(max(a[2 * root].ms, a[2 * root + 1].ms), a[2 * root].rs + a[2 * root + 1].ls);//���������ڵ��������ض��ǣ�������������䣬������������䣬���������ϲ����м����䣬��������������ֵ
    if (a[2 * root].ls == a[2 * root].r - a[2 * root].l + 1)//�������������˵Ļ�������������Ҫ�����Һ��ӵ�������
        a[root].ls += a[2 * root + 1].ls;
    if (a[2 * root + 1].rs == a[2 * root + 1].r - a[2 * root + 1].l + 1)//ͬ��
        a[root].rs += a[2 * root].rs;
}

int query(int root, int t)
{
    if (a[root].l == a[root].r || a[root].ms == 0 || a[root].ms == a[root].r - a[root].l + 1)//����Ҷ�ӽڵ���߸÷�������Ϊ�ջ�������������Ҫ��������
        return a[root].ms;
    int mid = (a[root].l + a[root].r) >> 1;
    if (t <= mid)
    {
        if (t >= a[2 * root].r - a[2 * root].rs + 1)//�жϵ�ǰ������Ƿ�����������������У���Ϊt<=mid������������a[2*i].r-a[2*i].rs+1�����������ұ������������߽�ֵ�����t�����������������ڣ���Ҫ�����������������ж೤������
            return query(2 * root, t) + query(2 * root + 1, mid + 1);
        else
            return query(2 * root, t);//����������������ұ߽������ڣ���ֻ��Ҫ��������
    }
    else
    {
        if (t <= a[2 * root + 1].l + a[2 * root + 1].ls - 1)//ͬ��
            return query(2 * root + 1, t) + query(2 * root, mid);
        else
            return query(2 * root + 1, t);
    }
}

int main()
{
    int i, j, x;
    char ch[2];
    while (~scanf("%d%d", &n, &m))
    {
        top = 0;
        init(1, n, 1);
        while (m--)
        {
            scanf("%s", ch);
            if (ch[0] == 'D')
            {
                scanf("%d", &x);
                s[top++] = x;
                insert(1, x, 0);
            }
            else if (ch[0] == 'Q')
            {
                scanf("%d", &x);
                printf("%d\n", query(1, x));
            }
            else
            {
                if (x>0)
                {
                    x = s[--top];
                    insert(1, x, 1);
                }
            }
        }
    }
    return 0;
}
