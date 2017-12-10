#include<cstdio>
#include<ctype.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
int dp[21][801];//dp(j, k)表示，取j 个候选人，使其辩控差为k 的所有方案中，辩控和最大的那个方案（该方案称为“方案dp(j, k)”）的辩控和。
vector<int> path[21][801];

int main()
{
    int times = 1;
    //    freopen("input.txt","r",stdin);
    //    freopen("output.txt","w",stdout);
    int subtraction[201], _plus[201];
    int n, m, i, j, k;
    while (~scanf("%d%d", &n, &m) && n && m)
    {//一共有n个候选人，要选m个
        for (i = 0; i<m; ++i)//清空vector
            for (j = 0; j<801; ++j)
                path[i][j].clear();
        memset(dp, -1, sizeof(dp));
        int d, p;
        for (i = 0; i < n; i++)
        {
            cin >> d >> p;//输入辩护方和控诉方的打分
            subtraction[i] = d - p;//得到每个人的辩护方的分数-控诉方的分数
            _plus[i] = d + p;//得到和
        }
        int fix = 20 * m;//由于题目中辩控差的值k 可以为负数，而程序中数租下标不能为负数，所以，在程序中不妨将辩控差的值都加上修正值fix=400，以免下标为负数导致出错。
        //为什么fix = 400？这是很显然的，m上限为20人，当20人的d均为0，p均为20时，会出现辨控差为 - 400。修正后回避下标负数问题，区间整体平移，从[-400, 400]映射到[0, 800]。
        dp[0][fix] = 0;
        for (k = 0; k < n; k++)//顺序选择一个候选人
            for (i = m - 1; i >= 0; i--)//进行逆推
            {
                for (j = 0; j < 2 * fix; j++)
                {
                    if (dp[i][j] >= 0)
                    {
                        if (dp[i + 1][j + subtraction[k]] <= dp[i][j] + _plus[k])
                        {//可行方案dp(j-1, x)能演化成方案dp(j, k)的必要条件是：存在某个候选人i，i 在方案dp(j-1, x)中没有被选上，且x+V(i) = k。在所有满足该必要条件的dp(j-1, x)中，选出 dp(j-1, x) + S(i) 的值最大的那个，那么方案dp(j-1, x)再加上候选人i，就演变成了方案 dp(j, k)。
                            //dp[i][j + d[k]] = max(dp[i][j + d[k]], dp[i-1][j] + s[k])
                            dp[i + 1][j + subtraction[k]] = dp[i][j] + _plus[k];
                            path[i + 1][j + subtraction[k]] = path[i][j];//每次更新都要把path全部复制过来，就是因为这个才用的vector
                            path[i + 1][j + subtraction[k]].push_back(k);
                        }
                    }
                }
            }
        //DP后，从第m行的dp(m, fix)开始往两边搜索最小|D-P| 即可，第一个不为dp[m][k]!=-1的位置k就是最小|D-P|的所在。
        //D+P = dp(m, |D-P| ) ，|D-P|已知。
        //那么D = (D + P + | D - P | ) / 2, P = (D + P - | D - P | ) / 2，计算D和P时注意修正值fix
        for (i = 0; dp[m][fix + i] == -1 && dp[m][fix - i] == -1; i++);
        int temp = (dp[m][fix + i] > dp[m][fix - i]) ? i : -i;
        int sumD = (dp[m][fix + temp] + temp) / 2;
        int sumP = (dp[m][fix + temp] - temp) / 2;
        printf("Jury #%d\n", times++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", sumD, sumP);
        for (i = 0; i < m; i++)
            printf(" %d", path[m][fix + temp][i] + 1);
        printf("\n\n");

    }
    return 0;
}