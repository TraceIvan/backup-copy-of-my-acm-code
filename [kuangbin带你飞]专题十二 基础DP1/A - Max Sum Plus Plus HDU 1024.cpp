#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
const int maxn = 1000010;
const int INF = 0x7fffffff;

int num[maxn];
int dp_now[maxn];
int max_pre[maxn];
//dp[i][j]表示前j个数在选取第j个数的前提下分成i段的最大值。
//dp[i][j]=max(dp[i][j-1]+num[j],max(dp[i-1][k]|(0<k<j))+num[j]);
//dp[i][j-1]+num[j]表示前j-1个分成i组，j放在其他组里
//max(dp[i-1][k]|(0<k<j))+num[j]表示前k个分成i-1组的最大值加上第j个独立成组的大小
int main()
{
    while (~scanf("%d%d", &m, &n))
    {
        for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
        memset(dp_now, 0, sizeof(dp_now));
        memset(max_pre, 0, sizeof(max_pre));
        int tmax;
        for (int i = 1; i <= m; i++)
        {
            tmax = -INF;
            for (int j = i; j <= n; j++)
            {
                dp_now[j] = max(dp_now[j - 1]+num[j], max_pre[j - 1] + num[j]);
                max_pre[j - 1] = tmax;
                tmax = max(tmax, dp_now[j]);
            }
        }
        printf("%d\n", tmax);
    }
    return 0;
}