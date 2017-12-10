#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<functional>
#include<memory>
#include<memory.h>
#include<cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 210;
int num[maxn];
int sum[maxn];
int dp[maxn][maxn];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        memset(dp, 0, sizeof(dp));
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &num[i]);
            sum[i] = sum[i - 1] + num[i];
        }
        for (int len = 2; len <= n; len++)
        {
            for (int start = 1; start <= n-len+1; start++)
            {
                int ed = start +len-1;
                dp[start][ed] = INF;
                for (int k = start; k <ed; k++)
                {
                    dp[start][ed] = min(dp[start][k] + dp[k + 1][ed] + sum[ed] - sum[start - 1], dp[start][ed]);
                }
            }
        }
        printf("%d\n", dp[1][n]);
    }
    return 0;
}
/*
dp[start][end]表示从第start堆开始到end堆进行合并，dp[1][n]为合并的最优得分。其中start和要合并的长度确定了，end也就确定，不用end进行迭代。
思考：在过程中，任何一堆石子都是有两堆合并而来的，假设过程刚开始时，是将给出的相邻的第i堆和第i+1堆合并。过程最后是将，从第1到k堆合并成的一堆(1)，与从k+1堆到n堆合并成的一堆(2)，(1)(2)这两堆合并的。
dp[start][start+len] =
min(dp[start][k]+dp[k+1][start+len]+∑a[start~start+len]) ;
(start<=k < start+len), len为要合并的堆数（1～n）
*/