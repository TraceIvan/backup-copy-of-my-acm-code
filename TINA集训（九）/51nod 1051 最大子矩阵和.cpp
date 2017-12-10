#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
long long tsum[550];
int mp[550][550];
int main()
{
    int n, m;
    while (~scanf("%d%d", &m, &n))
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++) scanf("%d", &mp[i][j]);
        }
        long long ans = 0;
        for (int i = 1; i <= n; i++)
        {
            memset(tsum, 0, sizeof(tsum));//记录从第i行到第j行每列的和
            for (int j = i; j <= n; j++)
            {
                for (int k = 1; k <= m; k++) tsum[k] += mp[j][k];
                long long tmax = 0;
                for (int k = 1; k <= m; k++)
                {
                    tmax += tsum[k];
                    if (tmax < 0) tmax = 0;
                    else ans = max(tmax, ans);
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}