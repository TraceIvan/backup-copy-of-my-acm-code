#include<iostream>
#include<memory.h>
#include<algorithm>
using namespace std;
int n, k;
const int maxk = 2100;
int dp[maxk];
int singlep[maxk];
int dbp[maxk];
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &k);
        for (int i = 1; i <= k; i++) scanf("%d", &singlep[i]);
        for (int i = 1; i <= k - 1; i++) scanf("%d", &dbp[i]);
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= k; i++)
        {
            if (i == 1)dp[i] = singlep[i];
            else
            {
                dp[i] = min(dp[i - 1] + singlep[i], dp[i - 2] + dbp[i - 1]);
            }
        }
        int hh = 8;
        int mm = 0, ss = 0;
        hh += dp[k]/3600;
        mm += dp[k]%3600/ 60;
        ss += dp[k] % 60;
        char t1[4] = "am", t2[4] = "pm";
        printf("%02d:%02d:%02d %s\n", (hh<=12?hh:hh-12), mm, ss, (hh >= 13 ? t2 : t1));
    }
    return 0;
}