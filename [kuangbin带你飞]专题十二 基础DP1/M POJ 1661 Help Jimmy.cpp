#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
struct node
{
    int x1;//板子左侧
    int x2;//板子右侧
    int h;//所在高度
};
node op[1010];
int dp[20010][2];
//dp[i][0]表示以i号平台左边为起点到地面的最短时间，dp[i][1]表示以i号平台右边为起点到地面的最短时间
bool cmp(node a, node b)
{//按高度从低到高
    return a.h < b.h;
}
const int inf = 0x7f7f7f7f;
int main()
{
    int t;
    int n, x, y, maxn;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d%d%d", &n, &x, &y, &maxn);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d", &op[i].x1, &op[i].x2, &op[i].h);
        }
        sort(op + 1, op + n + 1, cmp);

        // 0 左
        // 1 右
        dp[1][0] = dp[1][1] = op[1].h;
        op[n + 1].x1 = op[n + 1].x2 = x;
        op[n + 1].h = y;// op[n+1] 其实代表的是坐标（x,y）,最高的开始跳的地方;

        for (int i = 2; i <= n + 1; i++)
        {//从高度低的向上DP
            dp[i][0] = dp[i][1] = inf;
            int flag0 = 0; // 用于标记左面端点
            int flag1 = 0; // 用于标记右面端点
            int tmp;
            for (int j = i - 1; j>0; j--) // 这里注意必须逆序，因为从上往下跳，有板子挡住的话就没法继续往下跳了。
            {
                if (op[i].h - op[j].h > maxn) continue;
                if (op[j].x1 <= op[i].x1 && op[j].x2 >= op[i].x1 &&flag0 == 0)
                {//可以从第i个平台的左侧跳到第j个平台上
                    tmp = min(dp[j][0] - op[j].x1 + op[i].x1, dp[j][1] - op[i].x1 + op[j].x2);
                    dp[i][0] = min(dp[i][0], tmp + op[i].h - op[j].h);
                    //tmp表示跳到第j个平台后向左或向右走到地面的时间的最小值
                    //tmp + op[i].h - op[j].h为再加上从第i个平台左侧跳到第j个平台所需要的时间
                    flag0 = 1; // 表示已经不能继续往下跳了，因为已经有板子了
                }
                if (op[j].x1 <= op[i].x2 && op[j].x2 >= op[i].x2&&flag1 == 0)
                {//可以从第i个平台的右侧跳到第j个平台上
                    tmp = min(dp[j][0] - op[j].x1 + op[i].x2, dp[j][1] - op[i].x2 + op[j].x2);
                    dp[i][1] = min(dp[i][1], tmp + op[i].h - op[j].h);
                    flag1 = 1; // 道理同上
                }
                if (flag0 == 1 && flag1 == 1)break;
            }
            if (flag0 == 0 && op[i].h <= maxn)
            {//平台i左侧下没有其他板子，并且距离地面的高度小于等于跳的高度
                dp[i][0] = min(dp[i][0], op[i].h);
            }
            if (flag1 == 0 && op[i].h <= maxn)
            {//平台i右侧下没有其他板子，并且距离地面的高度小于等于跳的高度
                dp[i][1] = min(dp[i][1], op[i].h);
            }// 这里判断是不是可以直接跳到地面上。
             //cout << dp[i][0] << " " << dp[i][1] << endl;
        }
        int cc = min(dp[n + 1][0], dp[n + 1][1]);
        cout << cc << endl;
    }
    return 0;
}