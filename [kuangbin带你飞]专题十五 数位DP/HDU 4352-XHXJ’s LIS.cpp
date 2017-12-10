#include<cstdio>
#include<cstring>
#include<iostream>
#define LL __int64
using namespace std;
LL dp[40][1<<10][11];//dp[i][j][k]:i为当前进行到的数位，j状态压缩，为10个数字出现过的，其中1的个数就是最长上升子序列，k要求的上升子序列的长度
int bit[40], pos;
LL L, R; int K;
int numone(int state)
{//得到1的个数，即最长递增子序列的长度
    int ret = 0;
    while (state)
    {
        ret += state & 1; state >>= 1;
    }
    return ret;
}
int turn(int state, int x)
{//找到第一个大于x的数并且替换他，nlogn求最长递增子序列的思想

    for(int i=x;i<=9;i++)
        if ((1<<i)&state)
        {
            return ((state^(1<<i)) | (1<<x));
        }
    return (state | (1<<x));
}
LL DP(int pp, int state, bool nozero, bool big)//has 是否有inc==K
{//nozero为前面的是否为0标记，big上界标记
    if (pp == 0)return numone(state) == K;
    if (big&&dp[pp][state][K] != -1)return dp[pp][state][K];
    LL ret = 0;
    int kn = big ? 9 : bit[pp];
    for(int i=0;i<=kn;i++)
    {
        ret += DP(pp - 1, (nozero || i != 0) ? turn(state, i) : 0, nozero || i != 0, big || kn != i);
    }
    if (big)dp[pp][state][K] = ret;
    return ret;
}
LL get(LL x)
{
    pos = 0;
    while (x)
    {
        bit[++pos] = x % 10;
        x /= 10;
    }
    return DP(pos, 0, 0, 0);
}
int main()
{
    int t; 
    memset(dp, -1, sizeof(dp));
    scanf("%d", &t);
    int Case = 1;
    while (t--)
    {
            scanf("%I64d%I64d%d", &L, &R, &K);
            printf("Case #%d: %I64d\n", Case++, get(R) - get(L - 1));
    }
    return 0;
}
