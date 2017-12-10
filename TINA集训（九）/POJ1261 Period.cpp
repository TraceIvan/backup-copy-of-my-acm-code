#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1000010;
char des[maxn];
int Next[maxn];
int n,Case;
void GetNext(int *next, char *src, int len)
{//next和src都从下标1开始存储
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
void Solve()
{
    printf("Test case #%d\n", Case++);
    for (int i = 2; i <= n+1; i++)
    {
        int len = i - Next[i];
        if ((i-1) != len&&(i-1)%len == 0)
        {
            printf("%d %d\n", i-1, (i-1) / len);
        }
    }
    printf("\n");
}
int main()
{
    Case = 1;
    while (~scanf("%d",&n)&&n)
    {
        scanf("%s", des + 1);
        GetNext(Next, des, n);
        Solve();
    }
    return 0;
}