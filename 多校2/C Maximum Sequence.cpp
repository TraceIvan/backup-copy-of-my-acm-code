#include<iostream>
#include<algorithm>
using namespace std;
int n;
const int maxn = 250005;
const int MOD = 1e9 + 7;
int inita[maxn * 2];
int da[maxn * 2];
int b[maxn];
int maxaf[maxn];//maxaf[i]表示从dai到dan的最大值
int maxab[maxn];//maxab[i]表示从da(n+i)到dan的最大值
int main()
{
    while (~scanf("%d", &n))
    {
        long long sum = (1ll * (3 * n + 1)*n / 2) % MOD;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &inita[i]);
            da[i] = inita[i] - i;
        }
        maxaf[n] = da[n];
        for (int i = n-1; i >= 1; --i)
        {
            maxaf[i] = max(maxaf[i + 1], da[i]);
        }
        maxab[0] = da[n];
        for (int i = 0; i < n; i++) scanf("%d", &b[i]);
        sort(b, b + n);
        for (int i = n + 1,j=0; i <= 2 * n;j++, i++)
        {
            inita[i] = max(maxaf[b[j]], maxab[j]);
            da[i] = inita[i] - i;
            sum = (sum + da[i]) % MOD;
            maxab[j + 1] = max(maxab[j], da[i]);
        }
        printf("%lld\n", sum);
    }
    return 0;
}