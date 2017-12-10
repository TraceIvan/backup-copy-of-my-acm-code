#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1000010;
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
    printf("Test case #%d\n", Case++);
    for (int i = 1; i <= n; i++)
    {
        int len = i - Next[i];
        if (i!= len && i % len == 0)
        {
            printf("%d %d\n", i, i / len);
        }
    }
    printf("\n");
}
int main()
{
    Case = 1;
    while (~scanf("%d", &n) && n)
    {
        scanf("%s", des);
        GetNext(Next, des, n);
        Solve();
    }
    return 0;
}