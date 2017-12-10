#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 50010;
int num[maxn];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
        long long tsum = 0, ans = 0;
        for (int i = 1; i <= n; i++)
        {
            tsum += num[i];
            if (tsum < 0)
            {
                tsum = 0;
            }
            ans = max(ans, tsum);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}