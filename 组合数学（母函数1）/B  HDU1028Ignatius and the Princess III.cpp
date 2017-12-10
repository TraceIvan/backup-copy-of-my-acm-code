#include<iostream>
#include<memory.h>
using namespace std;
const int maxn = 130;
int re[maxn];
int p1[maxn];
int p2[maxn];
int xx[maxn];
int main()
{
    int n;
    while (~scanf("%d",&n))
    {
        for (int i = 1; i <= n; i++)
        {
            xx[i] = n / i;
        }
        for (int i = 0; i <maxn; i++)
        {
            if (i <= xx[1]) p1[i] = 1;
            else p1[i] = 0;
            re[i] = p2[i] = 0;
        }

        for (int i = 2; i <= n; i++)
        {
            for (int k = 0; k <= xx[i] && k*i <maxn; k++) p2[k*i] = 1;
            for (int j = 0; j <maxn; j++)
            {
                for (int k = 0; k <= xx[i]; k++)
                {//第i个字符的多项式，每项的指数为i*k，系数为1
                    int zhishu = i*k + j;
                    if (zhishu >=maxn) continue;
                    re[zhishu] += p1[j] * p2[k*i];
                }
            }
            for (int j = 0; j <maxn; j++) p1[j] = re[j], re[j] = p2[j] = 0;
        }
        printf("%d\n", p1[n]);
    }
    return 0;
}