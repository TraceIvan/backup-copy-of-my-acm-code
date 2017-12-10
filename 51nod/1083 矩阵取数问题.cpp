#include<iostream>
#include<algorithm>
using namespace std;
int dp[510];
int n;
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++)
        {
            int num;
            scanf("%d", &num);
            if (i == 0) dp[i] = num;
            else dp[i] = num + dp[i - 1];
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int num;
                scanf("%d", &num);
                if (j == 0)dp[j] = dp[j] + num;
                else dp[j] = max(dp[j], dp[j - 1]) + num;
            }
        }
        printf("%d\n", dp[n - 1]);
    }
    return 0;
}