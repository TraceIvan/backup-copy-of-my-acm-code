/*
�����������������Ŀ������⣬�������������
U:������[l,r]���ǳ�1
I:��[-��,l)(r,��]���ǳ�0
D:������[l,r]���ǳ�0
C:��[-��,l)(r,��]���ǳ�0 , ��[l,r]����0/1����
S:[l,r]����0/1����

��һ�����䱻���Ǻ�,����֮ǰ��û������Ƕ�û��������
���Ե�һ���ڵ�õ����Ǳ��ʱ����������
����һ���ڵ�õ�����ǵ�ʱ��,���жϸ��Ǳ��,�����0��1,ֱ�Ӹı�һ�¸��Ǳ��,��Ȼ�Ļ��ı������
�����������ֻҪ���ֳ���2�Ϳ��Դ���(ż����ʾ�˵�,������ʾ���˵�������)
*/
#include <cstdio>
#include <iostream>
#include<memory.h>
using namespace std;
const int M = 70000 * 2;
struct segment
{
    int tag; //1��ʾ�������б����ǣ�0��ʾ���䶼û�и��ǡ�-1��ʾ�������Ѿ�����
    bool rev; //�����
}tree[M << 2];
void build(int root, int l, int r)
{
    tree[root].tag = 0;//��ʼ��
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
        if (tree[root].rev) //��Ҫ��ת�Ļ��ͷ�ת
        {
            tree[root].rev = false;
            tree[root].tag ^= 1;
        }
        return;
    }
    if (tree[root].tag != -1) //������Ϊ��ɫ
    {
        if (tree[root].rev) tree[root].tag ^= 1;
        tree[root*2+1].tag = tree[root*2+2].tag = tree[root].tag;
        tree[root].tag = -1;//�Ѿ��·�
        tree[root*2+1].rev = tree[root*2+2].rev = tree[root].rev = false;
    }
    if (tree[root].rev)//��Ҫ���
    {
        tree[root].rev = false;
        if (tree[root*2+1].tag == -1)
            tree[root*2+1].rev ^= 1;//�·�
        else tree[root*2+1].tag ^= 1;//����ֱ�ӱ�Ǹ����������Ƿ񸲸�
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
        if (v<2) //��ֵ����
        {
            tree[root].rev = false;
            tree[root].tag = v;
        }
        else //��ת����
        {
            if (tree[root].tag != -1) //����Ϊ��ɫ,ֱ�ӷ�ת����
                tree[root].tag ^= 1;
            else tree[root].rev ^= 1; //���
        }
        return;
    }
    int m = (l + r) / 2;
    pushdown(root,l,r);//���¸�������
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
        getchar();//���뻻�з�
        l <<= 1; if (a == '(') l++;//�������䴦��
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
