#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int num[510][510];
int n;
int dp[510];
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= i; j++) scanf("%d", &num[i][j]);
        }
        for (int i = 1; i <= n; i++) dp[i] = num[n][i];
        for (int i = n - 1; i >= 1; i--)
        {
            for (int j = 1; j <= i; ++j)
            {
                dp[j] = max(dp[j], dp[j + 1]) + num[i][j];
            }
        }
        printf("%d\n", dp[1]);
    }
    return 0;
}