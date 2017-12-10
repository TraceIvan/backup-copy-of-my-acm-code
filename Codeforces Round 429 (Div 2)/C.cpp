#include<iostream>
#include<algorithm>
using namespace std;
int a[200010];
struct node
{
    int id;
    int v;
};
node b[200010];
int re[200010];
bool Cmp(const node&a, const node&b)
{
    return a.v < b.v;
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &b[i].v);
            b[i].id = i;
        }
        sort(a, a + n);
        sort(b, b + n, Cmp);
        for (int i = 0,j=n-1; i < n; i++,j--)
        {
            re[b[i].id] = a[j];
        }
        for (int i = 0; i < n; i++)
        {
            if (i > 0) printf(" ");
            printf("%d", re[i]);
        }
        printf("\n");
    }


    return 0;
}