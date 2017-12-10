#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 50010*2;
const int maxp = 50010*2;
char t[maxn];
char p[maxp];
int Next[maxp];
void GetNext(int *next, char *src, int len)
{//next��src�����±�0��ʼ�洢
    next[0] = -1;
    int j = 0, i = -1;
    while (j < len)
    {
        if (i == -1 || src[j] == src[i])
        {
            j++;
            i++;
            next[j] = i;
        }
        else i = next[i];
    }
}

int KMP(char*T, char *P, int *next)//��Ŀ�괮T�д�λ��1��ʼ����ģʽ��P��һ�γ��ֵ�λ��
{
    int lenT = strlen(T);
    int lenP = strlen(P);
    int posT = 0, posP = 0;
    while (posT <lenT)
    {
        if (posP == -1 || T[posT] == P[posP])
        {
            ++posT;
            ++posP;
        }
        else posP = next[posP];
    }
    return posP;
}
int main()
{
    while (~scanf("%s", &p))
    {
        scanf("%s", t);
        int lt = strlen(t), lp = strlen(p);
        strcat(p, t);//����
        GetNext(Next, p, strlen(p));
        //int ll=KMP(t, p, Next);
        int ll = lt+lp;
        while (Next[ll] > lt || Next[ll] > lp) ll = Next[ll];
        ll = Next[ll];
        if (ll>0)
        {
            for (int i = 0; i < ll; i++) printf("%c", p[i]);
            printf(" %d\n", ll);
        }
        else printf("0\n");
    }
    return 0;
}