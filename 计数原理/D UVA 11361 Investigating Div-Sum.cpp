#include<iostream>
#include<memory.h>
using namespace std;
const int maxn = 1 << 31-1;
long long dp[15][110][110];
//dp[i][j][K]表示递推到了第i位时，数位上数字和模k为j，数本身模k为K的数中小于B的数一共有多少个.
//当前本来就比B小，那么第i+1位是什么都无所谓，直接将f[i][j][k]累加到对应的f[i+1][*][*]上即可，另一部分就是当前前i位和B的前i位都相等，那么只有第i+1位取比B的i+1位上的数子要小的数字才会生成1个新的比B小的数，这样令对应的f[i+1][*][*]都自加1即可
int num[15];
int l, r, k;
long long Solve(int v)
{
    memset(num, 0, sizeof(num));
    int s1 = 0, s2 = 0;
    int cnt = 0;
    while (v)
    {
        num[cnt++] = v % 10;
        v /= 10;
    }
    memset(dp, 0, sizeof(dp));
    for (int i = cnt; i > 0; --i)
    {//枚举位数，从高位到低位，个位外面特判
        s1 = (s1 + num[i]) % k;
        s2 = (s2 * 10 + num[i]) % k;
        for (int j = 0; j < k; j++)
        {
            for (int z = 0; z < k; z++)
            {
                for (int d = 0; d < 10; d++)
                {
                    dp[i - 1][(j + d) % k][(z * 10 + d) % k] += dp[i][j][z];
                }
            }
        }
        for (int d = 0; d < num[i - 1]; d++)
        {
            dp[i - 1][(s1 + d) % k][(s2 * 10 + d) % k]++;
        }
    }
    long long ans = dp[0][0][0];
    if ((s1 + num[0]) % k == 0 && (s2 * 10 + num[0]) % k == 0) ans++;
    return ans;
}
int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d%d", &l, &r, &k);
        if (k >= 100)
        {
            printf("0\n");
        }
        else
        {
            printf("%lld\n", Solve(r) - Solve(l - 1));
        }
    }
    return 0;
}