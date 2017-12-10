#include<iostream>
#include<cstdio>
#include<string.h>
using namespace std;
const int maxn = 35;
long long f[maxn];
long long d[maxn][maxn];//d[i][j]��ʾÿ����������i��Ҷ�ӣ�һ����j��Ҷ�ӵķ�������
long long C(long long n, long long m)
{//��n������ѡm�����ķ���
    double ans = 1;
    for (int i = 0; i < m; i++)
    {
        ans *= n - i;
    }
    for (int i = 0; i < m; i++)
    {
        ans /= i + 1;
    }
    return (long long)(ans + 0.5);
}

int main()
{
    f[1] = 1;
    memset(d, 0, sizeof(d));
    int n = 30;
    for (int i = 0; i <= n; i++) d[i][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        d[i][1] = 1;
        d[0][i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 2; j <= n; j++)
        {
            d[i][j] = 0;
            for (int p = 0; p*i <= j; p++)
            {//ǡ�ð���i��Ҷ�ӵ�������p�á�C(f[i] + p - 1, p)��ʾ��f[i]������ѡp��
                d[i][j] += C(f[i] + p - 1, p)*d[i - 1][j - p*i];
            }
        }
        f[i + 1] = d[i][i + 1];
    }

    while (scanf("%d", &n) && n)
    {
        printf("%lld\n", n == 1 ? 1 : 2 * f[n]);
    }
    return 0;
}