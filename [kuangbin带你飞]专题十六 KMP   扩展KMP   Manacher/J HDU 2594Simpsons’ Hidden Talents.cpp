#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 50010*2;
const int maxp = 50010*2;
char t[maxn];
char p[maxp];
int Next[maxp];
void GetNext(int *next, char *src, int len)
{//next和src都从下标0开始存储
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

int KMP(char*T, char *P, int *next)//在目标串T中从位置1开始查找模式串P第一次出现的位置
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
        strcat(p, t);//新增
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