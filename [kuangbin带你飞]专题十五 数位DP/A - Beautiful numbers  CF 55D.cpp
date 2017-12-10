#include <stdio.h>
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <vector>
#include <math.h>
#include <string.h>
#include <queue>
#include <string>
#include <stdlib.h>
#include <algorithm>
#define LL long long
#define eps 1e-12
#define PI acos(-1.0)
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 4010;
const int max_lcm = 2520;

LL gcd(LL a, LL b)
{
    if (b == 0)
        return a;
    return gcd(b, a%b);
}
LL lcm(LL a, LL b)
{
    return a / gcd(a, b)*b;
}
int dig[25];
LL dp[25][50][2525];//经过分析后可以设出dp[20][2050][2050]，dp[i][j][k]表示处理到i位，前面的数的最小公倍数为j，前面的数 % 2520为k。因为1~9组成的最小公倍数只有48个，可以离散化，这样数组就降到了dp[20][50][2520]。
int Hash[2525];

LL dfs(int len, int prelcm, int prenum, int up)
{
    if (len == 0)
    {
        return prenum%prelcm == 0;
    }
    if (!up && dp[len][Hash[prelcm]][prenum] != -1)
        return dp[len][Hash[prelcm]][prenum];
    int end = up ? dig[len] : 9;
    LL res = 0;
    for (int i = 0; i <= end; i++)
    {
        int nownum = (prenum * 10 + i) % max_lcm;
        int nowlcm = prelcm;
        if (i)
            nowlcm = lcm(prelcm, i);
        res += dfs(len - 1, nowlcm, nownum, up&&i == end);//flag&&i==end，在最开始，取出的end是最高位，所以如果i比end小，那么i的下一位都可以到达9，而i==num了，最大能到达的就只有,dig[pos-1] 
    }
    if (!up)
        dp[len][Hash[prelcm]][prenum] = res;
    return res;
}

LL cal(LL num)
{
    int len = 0;
    while (num)
    {
        dig[++len] = num % 10;
        num /= 10;
    }
    return dfs(len, 1, 0, 1);
}

int main()
{
    int test;
    LL a, b;
    int cnt = 0;
    for (int i = 1; i <= 2520; i++) //离散化
    {
        if (max_lcm % i == 0)
            Hash[i] = ++cnt;
    }

    scanf("%d", &test);
    memset(dp, -1, sizeof(dp));
    for (int item = 1; item <= test; item++)
    {
        scanf("%I64d %I64d", &a, &b);
        printf("%I64d\n", cal(b) - cal(a - 1));
    }

    return 0;
}
