#include<iostream>
#include<memory.h>
using namespace std;
const int maxn = 20;
const int maxv = 400;
int wp[maxn];
int re[maxv];
int tmp[maxv];
int main()
{
    for (int i = 1; i <= 17; i++)
    {
        wp[i] = 300 / (i*i);
    }
    for (int i = 0; i <= wp[1]; i++)
    {
        re[i] = 1*1*1;
    }
    for (int i = 2; i <= 17; i++)
    {
        for (int j = 0; j <= 300; j++)
        {
            for (int k = 0; k <= wp[i] && k*i*i + j <= 300; k++)
            {
                tmp[k*i*i + j] += re[j]*1;
            }
        }
        memcpy(re, tmp, sizeof(tmp));
        memset(tmp, 0, sizeof(tmp));
    }
    int n;
    while (~scanf("%d", &n)&&n)
    {
        printf("%d\n", re[n]);
    }
    return 0;
}