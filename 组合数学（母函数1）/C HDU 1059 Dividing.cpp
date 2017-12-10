#include<iostream>
#include<memory.h>
using namespace std;
const int maxn = 120010;
int re[maxn];
int p1[maxn];
int p2[maxn];
int xx[7];
int main()
{
    int Case = 1;
    while (~scanf("%d%d%d%d%d%d", &xx[1],&xx[2],&xx[3],&xx[4],&xx[5],&xx[6]))
    {
        int count = xx[1]%60 + 2 * (xx[2]%60) + 3 *(xx[3]%60) + 4 * (xx[4]%60) + 5 * (xx[5]%60) + 6 * (xx[6]%60);//对1~6这6个数的最小公倍数取余(也可以选择其他偶数)
        if (count == 0) break;
        if (count % 2)
        {
            printf("Collection #%d:\nCan't be divided.\n\n", Case++);
            continue;
        }
        count /= 2;
        memset(re, 0, sizeof(re));
        memset(p1, 0, sizeof(p1));
        p1[0] = 1;
        for (int i = 0; i <= xx[1]&&i<=count; i++) p1[i] = 1;
        for (int i = 2; i <= 6; i++)
        {
            for (int j = 0; j <=count; j++)
            {
                for (int k = 0; k <= xx[i]&&(i*k + j<=count); k++)
                {//第i个字符的多项式，每项的指数为i*k，系数为1
                    
                    re[i*k + j] += p1[j];
                }
            }
            memcpy(p1, re, sizeof(re));
            memset(re, 0, sizeof(re));
        }
        if (p1[count]) printf("Collection #%d:\nCan be divided.\n\n", Case++);
        else printf("Collection #%d:\nCan't be divided.\n\n", Case++);
    }
    return 0;
}