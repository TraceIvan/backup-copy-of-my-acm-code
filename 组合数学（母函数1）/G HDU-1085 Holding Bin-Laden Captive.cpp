#include<iostream>
#include<memory.h>
using namespace std;
const int maxv = 8005;
int re[maxv];
int tmp[maxv];
int main()
{
    int n1, n2, n5;
    while (~scanf("%d%d%d", &n1, &n2, &n5))
    {
        if (n1 == 0 && n2 == 0 && n5 == 0) break;
        int tsum = n1 +n2*2 + n5* 5;
        memset(re, 0, sizeof(re));
        memset(tmp, 0, sizeof(tmp));
        for (int i = 0; i <= n1&&i * 1 <= tsum; i++)
        {
            re[i*1] = 1;
        }
        for (int i = 2; i <= 3; i++)
        {
            int v = (i == 2 ? 2 : 5);
            for (int j = 0; j <= tsum; j++)
            {
                int num = (i == 2 ? n2 : n5);
                for (int k = 0; k <= num&&k*v + j <= tsum; k++)
                {
                    tmp[k*v + j] += re[j];
                }
            }
            memcpy(re, tmp, sizeof(tmp));
            memset(tmp, 0, sizeof(tmp));
        }
        int pos = 0;
        while (pos<=tsum&&re[pos] != 0)pos++;
        printf("%d\n", pos);
    }
    return 0;
}