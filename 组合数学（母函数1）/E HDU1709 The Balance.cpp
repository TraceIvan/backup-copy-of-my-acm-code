#include<iostream>
#include<memory.h>
using namespace std;
const int maxv = 10010;
int re[maxv];
int p1[maxv];
int p2[maxv];
int xx[maxv];
int num[maxv];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int total = 0;
        memset(xx, 0, sizeof(xx));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &xx[i]);
            total += xx[i];
        }
        memset(re, 0, sizeof(re));
        memset(p1, 0, sizeof(p1));
        memset(p2, 0, sizeof(p2));
        for (int i = 0;i<=1;i++)
        {
            p1[i*xx[1]] = 1;
        }
        for (int i = 2; i <= n; i++)
        {
            for (int k = 0; k <= 1;k++) p2[k*xx[i]] = 1;
            for (int j = 0; j <= total; j++)
            {
                for (int k = 0;k<=1&&xx[i]*k+j<=total; k++)
                {//第i个字符的多项式，每项的指数为i*k，系数为1
                    re[xx[i]*k + j] += p1[j] * p2[k*xx[i]];
                }
            }
            memcpy(p1, re, sizeof(re));
            memset(re, 0, sizeof(re));
            memset(p2, 0, sizeof(p2));
        }
        for (int i = 0; i <= total; i++)
        {
            for (int j = i + 1; j <= total; j++)
            {
                if (p1[i] && p1[j])re[j - i] = 1;
            }
        }
        int ans = 0;
        for (int i = 1; i <= total; i++) if (re[i] == 0) ans++;
        printf("%d\n", ans);
        if (ans > 0)
        {
            bool fst = true;
            for (int i = 1; i <= total; i++)
            {
                if (re[i] == 0)
                {
                    if (fst)
                    {
                        printf("%d", i);
                        fst = false;
                    }
                    else printf(" %d", i);
                }
            }
            printf("\n");
        }
    }
    return 0;
}