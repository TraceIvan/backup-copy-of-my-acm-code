#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 100010;
const int maxp = 100010;
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
int main()
{
    int C;
    scanf("%d", &C);
    while (C--)
    {
        scanf("%s", &t);
        int ll = strlen(t);
        GetNext(Next, t,ll);
        int len = ll - Next[ll];//循环节长度
        if (len != ll&&ll%len == 0) printf("0\n");
        else printf("%d\n", len - Next[ll] % len);
    }
    return 0;
}