#include<iostream>
using namespace std;
struct sny
{
    int p;//价值
    int m;//数量
}ss[110];
long long re[10005];
long long tmp[10005];
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &ss[i].p, &ss[i].m);
            sum += ss[i].p*ss[i].m;
        }
        if (sum % 3)
        {
            printf("sorry\n");
            continue;
        }
        memset(re, 0, sizeof(re));
        memset(tmp, 0, sizeof(tmp));
        for (int i = 0; i <= ss[1].m&&i*ss[1].p <= sum; i++)
        {
            re[i*ss[1].p] = 1;
        }
        for (int i = 2; i <= n; i++)
        {
            int count = ss[i].m, val = ss[i].p;
            for (int j = 0; j <= sum; j++)
            {
                for (int k = 0; k <= count&&k*val + j <= sum; k++)
                {
                    tmp[k*val + j] =(tmp[k*val + j]+ re[j])%10000;
                }
            }
            memcpy(re, tmp, sizeof(tmp));
            memset(tmp, 0, sizeof(tmp));
        }
        if(re[sum/3]>0)printf("%lld\n", re[sum / 3] % 10000);
        else printf("sorry\n");
    }
    return 0;
}