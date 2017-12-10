#include<cstdio>
#include<cstring>
#include<iostream>
#define LL __int64
using namespace std;
LL dp[40][1<<10][11];//dp[i][j][k]:iΪ��ǰ���е�����λ��j״̬ѹ����Ϊ10�����ֳ��ֹ��ģ�����1�ĸ�����������������У�kҪ������������еĳ���
int bit[40], pos;
LL L, R; int K;
int numone(int state)
{//�õ�1�ĸ�����������������еĳ���
    int ret = 0;
    while (state)
    {
        ret += state & 1; state >>= 1;
    }
    return ret;
}
int turn(int state, int x)
{//�ҵ���һ������x���������滻����nlogn������������е�˼��

    for(int i=x;i<=9;i++)
        if ((1<<i)&state)
        {
            return ((state^(1<<i)) | (1<<x));
        }
    return (state | (1<<x));
}
LL DP(int pp, int state, bool nozero, bool big)//has �Ƿ���inc==K
{//nozeroΪǰ����Ƿ�Ϊ0��ǣ�big�Ͻ���
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
