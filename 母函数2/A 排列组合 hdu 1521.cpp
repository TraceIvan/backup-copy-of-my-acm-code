#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long Cal(int a)
{
    long long ans = 1;
    for (int i = 1; i <= a; i++) ans = ans*i;
    return ans;
}
const int maxn = 1010;
int num[12];
double p1[maxn];
double p2[maxn];
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
        memset(p2, 0, sizeof(p2));
        memset(p1, 0, sizeof(p1));

        for (int i = 0; i <= num[1]; i++)
        {
            p1[i] = 1.0 / Cal(i);
        }
        for (int i = 2; i <= n; i++)
        {
            for (int k = 0; k <= m; k++)
            {
                for (int j = 0; j <= num[i] && j + k <= m; j++)
                {
                    p2[j + k] += p1[k] / Cal(j);
                }
            }
            for (int j = 0; j <= m; j++)
            {
                p1[j] = p2[j];
                p2[j] = 0;
            }
        }
        printf("%.0lf\n", p1[m] * Cal(m));
    }
    return 0;
}