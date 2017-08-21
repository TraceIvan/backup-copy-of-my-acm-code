#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1000100;
char des[maxn];
int Next[maxn];
int n, Case;
void GetNext(int *next, char *src, int len)
{
    next[0] = -1;
    int j = 0, i = -1;
    while (j <len)
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
void Solve()
{
    if(n%(n-Next[n])==0)printf("%d\n", n/(n - Next[n]));
    else printf("1\n");
}
int main()
{
    while (~scanf("%s", des))
    {
        if (des[0] == '.')break;
        n = strlen(des);
        GetNext(Next, des, n);
        Solve();
    }
    return 0;
}