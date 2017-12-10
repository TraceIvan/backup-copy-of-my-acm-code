#include<iostream>
#include<stack>
#include<cstdio>
#include<memory.h>
using namespace std;
int n;
const int maxn = 16;
const int INF = 0x7fffffff;
struct sbj
{
    char nm[110];//科目名称
    int deadline;//截止日期
    int cost;//完成需花费的时间
}homework[maxn];
struct node
{
    int tm;
    int score;
    int pre;
    int now;
}dp[1 << maxn];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        {
            int total = (1 << n) - 1;
            for (int i = 0; i < n; i++)
            {
                scanf("%s%d%d", homework[i].nm, &homework[i].deadline, &homework[i].cost);
            }
            memset(dp, 0, sizeof(dp));
            for (int st = 1; st <= total; st++)
            {//从小的枚举
                dp[st].score = INF;
                for (int j = n - 1; j >= 0; j--)
                {//从最后往前枚举
                    if (st&(1 << j))
                    {
                        int st2 = st ^ (1 << j);
                        int t = dp[st2].tm + homework[j].cost - homework[j].deadline;
                        if (t < 0) t = 0;
                        if (t + dp[st2].score < dp[st].score)
                        {
                            dp[st].score = t + dp[st2].score;
                            dp[st].pre = st2;
                            dp[st].now = j;
                            dp[st].tm = dp[st2].tm + homework[j].cost;
                        }
                    }
                }
            }
            printf("%d\n", dp[total].score);
            int pre = total;
            stack<int>s;
            while (pre)
            {
                s.push(dp[pre].now);
                pre = dp[pre].pre;
            }
            while (!s.empty())
            {
                printf("%s\n", homework[s.top()].nm);
                s.pop();
            }
        }
    }
    return 0;
}