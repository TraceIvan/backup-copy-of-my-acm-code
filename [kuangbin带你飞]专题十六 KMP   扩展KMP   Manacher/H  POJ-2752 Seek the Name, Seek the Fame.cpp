#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 400100;
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
void Solve(int x)
{
    if (x != 0)
    {
        Solve(Next[x]);
        if (x == n) printf("%d\n", x);
        else printf("%d ", x);
    }
}
int main()
{
    while (~scanf("%s", des))
    {
        n = strlen(des);
        GetNext(Next, des, n);
        Solve(n);
    }
    return 0;
}