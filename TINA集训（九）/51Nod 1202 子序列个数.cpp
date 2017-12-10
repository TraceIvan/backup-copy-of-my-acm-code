//dp[i] = (dp[i - 1] * 2 + 1) % MOD; ����Ԫ���״γ���
//dp[i] = (dp[i - 1] * 2 - dp[pos[val[i]] - 1] + MOD) % MOD; ����Ԫ�ط��״γ���
#include<iostream>
using namespace std;
const int maxn = 100010;
const int MOD = 1e9 + 7;
int num[maxn];
long long dp[maxn];
int vis[maxn];
int main()
{
    int n;
    while (~scanf("%d",&n))
    {
        for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
        memset(dp, 0, sizeof(dp));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++)
        {
            if (!vis[num[i]])//  �����Ԫ��û�г��ֹ�
            {//  ǰi����ɵ����м������i����ϵ������ټ��ϵ�i��������Ϊ����
                dp[i] =( 2 * dp[i - 1]+1) % MOD;
            }
            else dp[i] = (dp[i - 1] * 2 - dp[vis[num[i]]-1]+MOD)%MOD;//  ǰi����ɵ����м������i����ϵ����м�ȥ�����Ԫ��Ϊ��β�Ĵ���
            vis[num[i]] = i;
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}