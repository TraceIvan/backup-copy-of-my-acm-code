#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1000100;
const int maxp = 10010;
char t[maxn];
char p[maxp];
int Next[maxp];
void GetNext(int *next, char *src, int len)
{//next和src都从下标1开始存储
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
    int cnt = 0;
    while (posT <lenT)
    {
        if (posP == -1 || T[posT] == P[posP])
        {
            ++posT;
            ++posP;
        }
        else posP = next[posP];
        if (posP== lenP)
        {
            cnt++;
            posP = next[posP];
        }
    }
    return cnt;
}
int main()
{
    int Case;
    scanf("%d", &Case);
    while (Case--)
    {
        scanf("%s", p);
        scanf("%s", t);
        GetNext(Next, p, strlen(p));
        printf("%d\n", KMP(t,p, Next));
    }
    return 0;
}