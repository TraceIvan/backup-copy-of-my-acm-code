#include<iostream>
#include<memory.h>
using namespace std;
int re[55];
int p1[55];
int p2[55];
int xx[27];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        for (int i = 1; i <= 26; i++) scanf("%d", &xx[i]);
        for (int i = 0; i <= 50; i++)
        {
            if (i <= xx[1]) p1[i]= 1;
            else p1[i] =0;
            re[i]=p2[i] = 0;
        }
        
        for (int i = 2; i <= 26; i++)
        {
            for (int k = 0; k <= xx[i] && k*i <= 50; k++) p2[k*i] = 1;
            for (int j = 0; j <=50; j++)
            {
                for (int k = 0; k <= xx[i]; k++)
                {//第i个字符的多项式，每项的指数为i*k，系数为1
                    int zhishu = i*k+j;
                    if (zhishu > 50) continue;
                    re[zhishu] += p1[j]*p2[k*i];
                }
            }
            for (int j = 0; j <= 50; j++) p1[j]=re[j],re[j]=p2[j]=0;
        }
        int sum = 0;
        for (int i = 1; i <= 50; i++) sum += p1[i];
        printf("%d\n", sum);
    }
    return 0;
}