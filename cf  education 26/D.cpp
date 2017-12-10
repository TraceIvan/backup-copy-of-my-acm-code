#include <cstdio>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 205;
const int maxm = 105;
const ll mod = 1e9 + 7;
const int INF = 0x3f3f3f;
const double eps = 1e-9;

int dp[maxn][maxm];
int n, k;
ll x;

int main()
{
    while (~scanf("%d%d", &n, &k))
    {
        for (int i = 0; i <= k; i++)
            for (int j = 0; j<maxm; j++)
            {
                dp[i][j] = -INF;
            }
        dp[0][0] = 0;
        for (int i = 0; i<n; i++)
        {
            int n2 = 0, n5 = 0;
            scanf("%I64d", &x);
            while (x % 2 == 0) x /= 2, n2++;//2因子的个数
            while (x % 5 == 0) x /= 5, n5++;//5因子的个数
            for (int j = k; j >= 1; j--)
                for (int l = n2; l<maxm; l++)
                {
                    dp[j][l] = max(dp[j][l], dp[j - 1][l - n2] + n5);//选择j个数
                }
        }
        int ans = 0;
        for (int i = 1; i<maxm; i++)
        {
            ans = max(ans, min(i, dp[k][i]));
        }
        printf("%d\n", ans);
    }
    return 0;
}