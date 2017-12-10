#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn = 100010;
struct node
{
    int id;
    int num;
}a[maxn];
bool Cmp(const node&a, const node&b)
{
    return a.num > b.num;
}
int b[maxn];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i].num);
            a[i].id = i + 1;
        }
        sort(a, a + n, Cmp);
        for (int i = 2; i <= n; i++)
        {
            int pos = 0;
            while (a[pos].id%i == 0) pos++;
            b[i] = a[pos].num;
        }
        for (int i = 2; i <= n; i++)
        {
            if (i > 2)printf(" ");
            printf("%d", b[i]);
        }
        printf("\n");
    }
    return 0;
}