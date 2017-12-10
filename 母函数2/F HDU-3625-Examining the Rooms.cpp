//求N个房间形成1~K个环有多少种可能，然后除以总的分配方案数即为题目要我们求的概率
//第一类斯特林数S(N, K) = S(N - 1, K - 1) + (N - 1)*S(N - 1, k)恰恰就是求N个元素形成K个非空循环排列的方法数
//S(N,M)-S(N-1,M-1)，表示N个元素形成M个环，减去1独自成环，即剩下的N-1个元素形成M-1个环，算得的结果便是所求值
#include<iostream>
using namespace std;
long long stl[25][25], cal[25];
void Init()
{
    cal[0] = cal[1] = 1;
    for (int i = 2; i <= 20; i++) cal[i] = cal[i - 1] * i;
    for (int i = 1; i <= 20; i++)
    {
        stl[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            stl[i][j] = stl[i - 1][j - 1] + (i - 1)*stl[i - 1][j];
        }
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    Init();
    while (t--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        long long ans = 0;
        for (int i = 1; i <= k; i++)
        {
            ans += stl[n][i] - stl[n - 1][i - 1];
        }
        printf("%.4lf\n", 1.0*ans / cal[n]);
    }
    return 0;
}