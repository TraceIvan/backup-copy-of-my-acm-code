#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 100010;
int num[maxn];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        long long sum = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &num[i]);
            sum += num[i];
        }
        long long tsum = 0, ans = 0;
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            tsum += num[i];
            if (tsum < 0)
            {
                tsum = 0;
            }
            else ans = max(ans, tsum);
        }
        long long ans2 = 0;
        tsum = 0;
        for (int i = 1; i <= n; i++)
        {
            tsum += num[i];
            if (tsum >0)
            {
                tsum = 0;
            }
            else ans2 = min(ans2, tsum);
        }
        printf("%I64d\n",max(ans,sum-ans2));
    }
    return 0;
}