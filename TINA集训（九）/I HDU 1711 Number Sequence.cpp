#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1000010;
const int maxm = 10010;
int p[maxm];
int des[maxn];
int Next[maxm];
int n, m;
void GetNext(int *next, int *src, int len)
{//next��src�����±�1��ʼ�洢
    next[1] = 0;
    int j = 1, i = 0;
    while (j <= len)
    {
        if (i == 0 || src[j] == src[i])
        {
            j++;
            i++;
            next[j] = i;
        }
        else i = next[i];
    }
}

int KMP(int *T, int *P, int *next)//��Ŀ�괮T�д�λ��1��ʼ����ģʽ��P��һ�γ��ֵ�λ��
{
    int lenT = n;
    int lenP = m;
    int posT = 1, posP = 1;
    while (posP <= lenP&&posT <= lenT)
    {
        if (posP == 0 || T[posT] == P[posP])
        {
            ++posT;
            ++posP;
        }
        else posP = next[posP];
    }
    if (posP <= lenP) return -1;
    else return posT - lenP;
}
int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", &des[i]);
        for (int i = 1; i <= m; i++) scanf("%d", &p[i]);
        GetNext(Next, p, m);
        printf("%d\n", KMP(des, p, Next));
    }
    return 0;
}