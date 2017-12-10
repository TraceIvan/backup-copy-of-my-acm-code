#include<iostream>
#include<algorithm>
using namespace std;
const int maxw = 50010;
const int maxn = 10010;
int dp[maxw];
int dv[maxn];
int dw[maxn];
int main()
{
    int n, w;
    while (~scanf("%d%d", &n, &w))
    {
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            int wi, pi, ci;
            scanf("%d%d%d", &wi, &pi, &ci);
            int num = 1;
            while (ci)
            {
                if (ci > num)
                {
                    dw[cnt] = num*wi;
                    dv[cnt] = num*pi;
                    ci -= num;
                    num *= 2;
                    cnt++;
                }
                else
                {
                    dw[cnt] = ci*wi;
                    dv[cnt] = ci*pi;
                    ci = 0;
                    cnt++;
                }
            }
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < cnt; i++)
        {
            for (int j = w; j - dw[i] >= 0; j--)
            {
                dp[j] = max(dp[j], dp[j - dw[i]] + dv[i]);
            }
        }
        printf("%d\n", dp[w]);
    }
    return 0;
}