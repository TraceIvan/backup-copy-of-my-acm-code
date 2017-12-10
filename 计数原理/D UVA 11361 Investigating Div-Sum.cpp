#include<iostream>
#include<memory.h>
using namespace std;
const int maxn = 1 << 31-1;
long long dp[15][110][110];
//dp[i][j][K]��ʾ���Ƶ��˵�iλʱ����λ�����ֺ�ģkΪj��������ģkΪK������С��B����һ���ж��ٸ�.
//��ǰ�����ͱ�BС����ô��i+1λ��ʲô������ν��ֱ�ӽ�f[i][j][k]�ۼӵ���Ӧ��f[i+1][*][*]�ϼ��ɣ���һ���־��ǵ�ǰǰiλ��B��ǰiλ����ȣ���ôֻ�е�i+1λȡ��B��i+1λ�ϵ�����ҪС�����ֲŻ�����1���µı�BС�������������Ӧ��f[i+1][*][*]���Լ�1����
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
    {//ö��λ�����Ӹ�λ����λ����λ��������
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