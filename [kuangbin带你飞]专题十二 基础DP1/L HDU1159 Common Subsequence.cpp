#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int maxl = 1010;
char a[maxl];
char b[maxl];
int dp[maxl][maxl];
int main()
{
    while (~scanf("%s%s", a, b))
    {
        int la = strlen(a);
        int lb = strlen(b);
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < la; i++)
        {
            for (int j = 0; j < lb; j++)
            {
                if (a[i] == b[j])
                {
                    if (i > 0 && j > 0)dp[i][j] = dp[i - 1][j - 1] + 1;
                    else dp[i][j] = 1;
                }
                else
                {
                    if(i>0&&j>0)dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    else if (i > 0) dp[i][j] = dp[i - 1][j];
                    else if (j > 0) dp[i][j] = dp[i][j - 1];
                    else dp[i][j] = 0;
                }
            }
        }
        printf("%d\n", dp[la - 1][lb - 1]);
    }
    return 0;
}