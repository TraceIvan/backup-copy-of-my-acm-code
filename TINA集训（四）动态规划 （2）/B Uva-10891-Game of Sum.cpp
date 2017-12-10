#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int maxn = 100;
int n;
//const int maxV=12;
int a[maxn + 10];
int dp[maxn + 5][maxn + 5];
int L[maxn + 5][maxn + 5], R[maxn + 5][maxn + 5];
int sum[maxn + 10];
int main()
{
    while (~scanf("%d", &n) && n)
    {
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            dp[i][i] = a[i];//dp[st][ed]表示[st,ed]区间，先手最多得分。
            sum[i] = sum[i - 1] + a[i];//L[st,ed]=min{dp[st][k]  } ;(st<=k<=ed)
            L[i][i] = R[i][i] = dp[i][i];//R[st,ed]=min{dp[k][ed]};(st<=k<=ed)
        }
        for (int add = 1; add<n; add++)
        {
            for (int st = 1; st + add <= n; st++)
            {
                int ed = st + add;
                int m = 0;              //m表示此阶段的后手最少能拿多少
                m = min(m, L[st][ed - 1]);//表示从右边拿起
                m = min(m, R[st + 1][ed]);//表示从左边拿起
                dp[st][ed] = sum[ed] - sum[st - 1] - m;
                L[st][ed] = min(L[st][ed - 1], dp[st][ed]);
                R[st][ed] = min(R[st + 1][ed], dp[st][ed]);
            }
        }
        printf("%d\n", dp[1][n] - (sum[n] - sum[0] - dp[1][n]));
    }
    return 0;
}
