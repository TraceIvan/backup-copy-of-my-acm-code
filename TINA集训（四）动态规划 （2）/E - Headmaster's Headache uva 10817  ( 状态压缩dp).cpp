#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;
const int INF = 0x7f7f7f7f, MAXN = 131;
int s, m, n, teach[MAXN], cost[MAXN], dp[MAXN][1 << 8][1 << 8];

int DP(int i, int s1, int s2)//s1对应还需要一个老师教的科目,s2对应已经足够老师教的科目.状态设为dp[i][s1][s2]：代表到第i个老师为止，校长最少需要花多少钱达到目标。当i < m 时，我们必须选择，状态只能更新为添加老师，当i >= m时， 就可以更新为选或不选老师两种状态。
//s1,s2均为2进制数，每一位表示该课程有无老师
//s1：当某个学科还需要1个老师教时，该位记为1，否则记为0
//s2:当某个学科已经有足够的老师教时，该位记为1，否则记为0
{
    if (i == m + n) return s2 == (1 << s) - 1 ? 0 : INF;  //每个科目都至少两个老师了，那么就不需要再花钱了
    int &ret = dp[i][s1][s2];//引用
    if (ret >= 0) return ret;
    ret = INF;
    if (i >= m) ret = DP(i + 1, s1, s2);         //不选
    s2 |= (s1 & teach[i]);                       //老师能教，并且差一个老师，那么一并运算，剩下的就是满足条件的科目
    s1 |= teach[i];                              //或上去，没人教的科目肯定变成差一个人教
    ret = min(ret, cost[i] + DP(i + 1, s1, s2)); //选
    return ret;
}

int main()
{
    while (~scanf("%d%d%d",&s,&m,&n))
    {
        if (s == 0)break;
        cin.get();
        string ss;
        int x;
        for (int i = 0; i < m + n; ++i)
        {
            getline(cin, ss);
            stringstream sss(ss);
            sss >> cost[i];
            teach[i] = 0;
            while (sss >> x)
            {
                teach[i] |= 1 << (x - 1);
            }
        }
        memset(dp, -1, sizeof dp);
        //for (int i = 0; i < m + n; ++i) cout << cost[i] << ':' << teach[i] << endl;
        cout << DP(0, 0, 0) << '\n';
    }
    return 0;
}
