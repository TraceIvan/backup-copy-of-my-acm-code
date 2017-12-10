#include<iostream>
#include<algorithm>
using namespace std;
const int maxn2 = 70*200;
const int maxn = 210;
const int INF = 0x7fffffff;
int dp[maxn][maxn2];
int n, k;
int main()
{
    while (~scanf("%d%d", &n, &k))
    {
        for (int i = 0; i <= k; i++)
        {
            for (int j = 0; j < maxn2; j++)
            {
                dp[i][j] = -INF;//防止不合法处
            }
        }
        dp[0][0] = 0;
        int totaln2 = 0;
        for (int i = 1; i <= n; i++)
        {
            long long num;
            scanf("%I64d", &num);
            int n2=0, n5=0;
            long long t = num;
            while (t % 2 == 0) t /= 2, n2++;
            while (t % 5 == 0) t /= 5, n5++;
            totaln2 += n2;
            for (int j = 1; j <=min(i,k); j++)
            {
                for (int p =n2; p <=totaln2; p++)
                {
                    dp[j][p] = max(dp[j][p], dp[j - 1][p - n2] + n5);//如果不选，则为dp[j][p];如果选,从j-1个n2个数为p-n2转移过来
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= totaln2; i++)
        {
            ans = max(ans, min(i, dp[k][i]));
        }
        printf("%d\n", ans);
    }
    return 0;
}