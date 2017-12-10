/*
�����������������Ŀ������⣬�������������
U:������[l,r]���ǳ�1
I:��[-��,l)(r,��]���ǳ�0
D:������[l,r]���ǳ�0
C:��[-��,l)(r,��]���ǳ�0 , ��[l,r]����0/1����
S:[l,r]����0/1����
*/
#include<iostream>
using namespace std;
const int maxn =14;
struct Node
{
    int tag; //��¼������ֵ��-1��ʾ������Ϊ��ɫ  
    bool rev; //��Ǹ������Ƿ�ת
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
    {//���ǵ���
        if (Tree[root].rev)
        {//�ж��Ƿ���Ҫ��ת���
            Tree[root].tag ^= 1;
            Tree[root].rev = false;
        }
        return;
    }
    else
    {
        if (Tree[root].tag != -1)
        {//��ʾ��Ҫ�ѵ�ǰ����ȫ�����ǻ�ȫ��ȡ������
            if (Tree[root].rev) Tree[root].tag ^= 1;
            Tree[root * 2 + 1].tag = Tree[root * 2 + 2].tag = Tree[root].tag;
            Tree[root].rev = Tree[root * 2 + 1].rev = Tree[root * 2 + 2].rev = false;
            Tree[root].tag = -1;//��ʾ��ǰ�����Ѿ����¸��£����Ҹ�����Ϊ������
        }
        if (Tree[root].rev)
        {//�����Ҫ��ת
            Tree[root].rev = false;
            if (Tree[root * 2 + 1].tag == -1)
                Tree[root * 2 + 1].rev ^= 1;//������Ϊ-1�����ʾ������
            else Tree[root * 2 + 1].tag ^= 1;//�����ǣ�׼��֮�����¸���
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
        if (v < 2)// ���ǻ�ȡ�����ǲ���������������
        {
            Tree[root].tag = v;
            Tree[root].rev = false;
        }
        else//������������
        {
            if (Tree[root].tag != -1)
            {//��������仹��Ҫ���и��ǻ�ȡ�����ǲ�������ֱ�ӽ��ò�����򣬵ȴ����¸���
                Tree[root].tag ^= 1;
            }
            else Tree[root].rev ^= 1;//����ı�����ǣ��ȴ����¸���
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
    {//��ǰ����Ϊ������
        if (Tree[root].tag == 1)
        {//�ұ�ѡ�񸲸�
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
    {//��˳�������ѡ�񸲸ǵĸ�������������
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