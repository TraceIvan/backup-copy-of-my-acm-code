#include<iostream>
using namespace std;
//1^2+2^2+3^2+...+n^2=n*(n+1)*(2n+1)/6;
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        if (n == 0 && m == 0) break;
        if (n > m)
        {
            int t = n;
            n = m;
            m = t;
        }
        long long ans = 0;
        ans += 1ll*(m - 1)*m*n;//行
        ans += 1ll*(n - 1)*n*m;//列
        ans += 1ll*(m-n+1)*n*(n-1)*2+1ll*4 *(n-2)*(n-1)*n/3;//对角线
        printf("%lld\n", ans);
    }
    return 0;
}