//将一堆正整数分为2组，要求2组的和相差最小。
#include<iostream>
#include<algorithm>
#include<cmath>
const int maxn = 110;
int num[maxn];
int dp[5010];
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int tsum = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &num[i]);
            tsum += num[i];
        }
        for (int i = 0; i <= tsum / 2; i++) dp[i] = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = tsum / 2; j-num[i]>= 0; j--)
            {
                dp[j] = max(dp[j], dp[j - num[i]] + num[i]);
            }
        }
        printf("%d\n", abs(tsum-2*dp[tsum / 2]));
    }

    return 0;
}