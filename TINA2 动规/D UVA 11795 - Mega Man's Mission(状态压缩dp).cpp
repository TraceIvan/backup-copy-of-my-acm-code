#include<iostream>
#include<cstdio>
#include<memory.h>
using namespace std;
typedef long long ll;
char s[20];
const int maxn = (1 << 16) + 10;
int N;
int w[maxn];//存储洛克人[0]和敌人[1:]的武器
int atk[maxn];//用来保存每个状态可以杀死的机器人
ll dp[maxn];// 2 的 16 次方会爆 int。 // 用来统计每种状态的顺序方案种数
int Exchange()
{
    int ans = 0;
    int sz = strlen(s);
    for (int i = 0; i < sz; i++)
    {
        if (s[i] == '1') ans = ans | (1 << i);//第i+1位如果能被杀掉，则第i+1位为1
    }
    return ans;
}
int main()
{
    int T;
    cin >> T;
    int Case = 1;
    while (T--)
    {
        cin >> N;
        for (int i = 0; i <= N; i++)
        {
            scanf("%s", s);
            w[i] = Exchange();
            //cout << i << ' ' << w[i] << endl;
        }
        int total = (1 << N) - 1;//对于N个敌人，一共最多有2^N-1种状态（每个敌人能够杀死或不能杀死）
        for (int st = 0; st <= total; st++)
        {//st即为二进制存储的状态
            atk[st] = w[0];//初始为洛克人所拿的武器能够杀死的人
            for (int i = 1; i <= N; i++)//对于每个敌人
            {
                int j = i - 1;//i其在所存二进制里的位置
                if (st&(1 << j))
                {//如果该状态可以杀死 i，那么该状态也可以杀死i所能干掉的
                    atk[st] = atk[st] | w[i];
                }
            }
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;//一个都不杀死的方案数为1
        for (int st = 1; st <= total; st++)
        {
            for (int i = 0; i < N; i++)
            {//对于N个敌人
                if (st & 1 << i)
                {//如果该状态能够杀死第i+1个敌人(敌人从1开始编号，但是在二进制存储的杀死状态中存储的位置为i),那么 st 由不能杀死 i 的状态转移过来, 即st^(1<<i)（异或）
                    if (atk[st ^ (1 << i)] & 1 << i)//并且st^(1<<i)这种状态能够杀死该敌人
                    {
                        dp[st] += dp[st ^ (1 << i)];
                    }
                }
            }
        }
        printf("Case %d: %lld\n", Case++, dp[total]);
    }
    return 0;
}