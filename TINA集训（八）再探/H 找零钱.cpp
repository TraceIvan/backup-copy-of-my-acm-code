#include<iostream>
using namespace std;
int w[13] = { 1,2,5,10,20,50,100,200,500,1000,2000,5000,10000 };
const int MOD = 1e9 + 7;
int dp[100010];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 0; i < 13; i++)
        {
            for (int j = w[i]; j <= n; j++)
            {
                dp[j] =(dp[j]+ dp[j - w[i]])%MOD;
            }
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}