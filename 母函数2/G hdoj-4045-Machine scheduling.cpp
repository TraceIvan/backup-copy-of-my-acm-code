//有N个机器，每天选出R个机器，而且每两个机器的编号差要大于等于K，而且每天将R个机器最多分为M组工作，问最多有多少种方案 
//1:如果是把n个求放入k个盒子中（每个盒子必须要有球），那么由插板法得 方案数为 C(n-1,k-1);
//2:如果是把n个求放入k个盒子中（盒子可以为空），那么由插板法得 方案数为 C(n + k - 1, k - 1);
//要从n个元素编号1~n中选出r个元素来，使得任意两个元素编号相差>=k
//解法：先按照 1 k + 1 2 * k + 1 .... (r - 1)*k + 1 也就是刚好 间隔 k个排列下来
//那么 总共n个元素，剩余 n - (r - 1)*k - 1个元素可以看成空格，极为space, 将它们插入这r个元素的r + 1个空档中，
//这样就能保证枚举了素有的方法数，切满足任意两个元素编号相差 >= k的要求
//所以这个问题简化为：将space个元素分配到r + 1个区域中，可以为空(每两个机器之前至少有K个间隔，那么如果还剩余一些位置，则把这些多余的插入到R个机器中。那么剩余位置便是N - ((R - 1)*K + 1), 对于R个机器，R + 1个位置，接下来便是把N - ((R - 1)*K + 1)分为R + 1个集合，而且可以为空。做法是添加R + 1个物品，然后用插板法，这样保证 每一个集合都至少有一个，然后再把每一个集合都减掉一个便是结果，最终结果便是C[N - ((R - 1)*K + 1) + R + 1 - 1][R]。)
#include<iostream>
using namespace std;
const int maxn = 1010;
const int MOD = 1e9 + 7;
long long C[maxn][maxn];
long long stri2[maxn][maxn];//第二类斯特林数
void Init()
{
    memset(C, 0, sizeof(C));
    for (int i = 0; i < maxn; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
    for (int i = 1; i < maxn; i++)
    {
        stri2[i][0] = 0;
        stri2[i][i]=stri2[i][1] = 1;
        for (int j = 1; j < i; j++)
        {
            stri2[i][j] = (stri2[i - 1][j] * j + stri2[i - 1][j - 1]) % MOD;
        }
    }
}
int main()
{
    Init();
    int n, r, k, m;
    while (~scanf("%d%d%d%d", &n, &r, &k, &m))
    {
        int res = n - (r - 1)*k - 1;
        if (res < 0)
        {
            printf("0\n");
            continue;
        }
        long long ans = 0;
        for (int i = 0; i <= m; i++) ans = (ans + stri2[r][i]) % MOD;
        ans = (ans*C[res + r][r]) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}