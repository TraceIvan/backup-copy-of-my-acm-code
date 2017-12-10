//状压DP
#include<iostream>
#include<algorithm>
using namespace std;
const int maxst = (1 << 17);
int ini[20];
int cover[maxst];
int dp[maxst];
int main()
{
    int n;
    int Case = 1;
    while (~scanf("%d", &n))
    {
        if (n == 0) break;
        for (int i = 0; i < n; i++)
        {
            ini[i] = 0|(1<<i);//包括自身
            int m;
            scanf("%d", &m);
            for (int j = 0; j < m; j++)
            {
                int k;
                scanf("%d", &k);
                ini[i] |= (1 << k);//加上邻居
            }
        }
        int total = (1 << n) - 1;//总状态数
        for (int i = 0; i <=total; i++)
        {
            cover[i] = 0;
            for (int j = 0; j < n; j++)
            {
                if (i&(1 << j))//如果该状态能够瘫坏第j台电脑
                {
                    cover[i] |= ini[j];//那么也能瘫坏其邻接的电脑
                }
            }
        }
        dp[0] = 0;
        for (int i = 1; i <= total; i++)
        {
            dp[i] = 0;
            //枚举子集
            for (int j = i; j > 0; j = (j - 1)&i)
            {
                if (cover[j] == total)//如果子集的状态下能够干掉所有的电脑
                {
                    dp[i] = max(dp[i], dp[i^j] + 1);//那么该状态的能够关闭的服务为max{该状态下能最多关闭的服务数,该状态i和能够干掉所有的电脑的子集的补集所能能关闭的方案数+1（这个1由该子集j提供）}
                }
            }
        }
        printf("Case %d: %d\n",Case, dp[total]);
        Case++;
    }
    return 0;
}