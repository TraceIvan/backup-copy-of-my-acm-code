#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        int ans = 0;
        int a, b, c, ab, bc, ac, abc;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d%d%d%d%d", &a, &b, &c, &ab, &bc, &ac, &abc);
            bool flag = true;
            int aa = a - ab - ac + abc;
            int bb = b - ab - bc + abc;
            int cc = c - ac - bc + abc;
            int aabb = ab - abc;
            int aacc = ac-abc;
            int bbcc = bc - abc;
            if (aa < 0 || bb < 0 || cc < 0 || aabb < 0 || aacc < 0 || bbcc < 0)continue;
            int tmp= a + b + c - ab - bc - ac + abc;
            if (tmp > ans) ans = tmp;
        }
        printf("%d\n", ans);
    }
    return 0;
}
