#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1010;
const int maxp = 1010;
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
    int cnt = 0;
    while (posT <lenT)
    {
        if (posP == -1 || T[posT] == P[posP])
        {
            ++posT;
            ++posP;
        }
        else posP = next[posP];
        if (posP == lenP)
        {
            cnt++;
            posP++;
        }
    }
    return cnt;
}
int main()
{
    while (~scanf("%s",&t))
    {
        if (t[0] == '#')break;
        scanf("%s", p);
        GetNext(Next, p, strlen(p));
        printf("%d\n", KMP(t, p, Next));
    }
    return 0;
}