#include<iostream>
using namespace std;
int n, p1, p2;
const int maxn = 1100;
int pre[maxn];//i的父亲
int r[maxn];//i和pre[i]的关系
//0:同类；1:不同类

bool vis[maxn];

int cntnum[maxn][2];//cntnum[i][j]表示把第i个集合分成两个部分的人数

int dp[maxn][310];//dp[i][j]表示前i个集合中好人为j的种数

int belong[maxn][2];//belong[i][0]表示i属于哪个大类，belong[i][1]表示i属于该大类的哪一个小类（对应cntnum）
int id[maxn];
//根据孩子与父亲，父亲与祖父之间的关系可以推出孩子与祖父的关系
int Find(int x)
{
    if (pre[x] == x) return x;
    else
    {
        int fa = pre[x];
        pre[x] = Find(fa);
        r[x] = r[x] ^ r[fa];
        return pre[x];
    }
}

void Union(int x, int y, int k)
{
    int rx = Find(x), ry = Find(y);
    if (rx != ry)
    {
        pre[rx] = ry;
        r[rx] = (r[x] - r[y] + 2 + k) % 2;
    }
}

void Init()
{
    for (int i = 0; i <= p1 + p2; i++)
    {
        pre[i] = i;
        r[i] = 0;
    }
}
int main()
{
    while (~scanf("%d%d%d", &n, &p1, &p2))
    {
        if (n == 0 && p1 == 0 && p2 == 0) break;
        Init();
        char s[5];
        int a, b, k;
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d%s", &a, &b, s);
            if (s[0] == 'y') k = 0;
            else k = 1;
            Union(a, b, k);
        }
        //处理完后，得到若干个集合，每个集合中两两同类或不同类
        //2：找到有多少个大集合，每个大集合中同类及不同类的个数
        memset(vis, 0, sizeof(vis));
        memset(cntnum, 0, sizeof(cntnum));
        memset(belong, 0, sizeof(belong));

        int cnt = 0;
        for (int i = 1; i <= p1 + p2; i++)
        {
            if (!vis[i])
            {
                cnt++;
                int f = Find(i);
                id[f] = cnt;//对每个大集合的根进行分类
                for (int j = i; j <= p1 + p2; j++)
                {
                    if (Find(j) == f)
                    {
                        vis[j] = true;
                        cntnum[cnt][r[j]]++;
                        belong[j][0] = cnt;
                        belong[j][1] = r[j];
                    }
                }
            }
        }
        //DP
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i <= cnt; i++)
        {
            for (int j = p1; j >= 0; j--)
            {
                if (j - cntnum[i][0] >= 0 && dp[i - 1][j - cntnum[i][0]] > 0)
                {
                    dp[i][j] += dp[i - 1][j - cntnum[i][0]];
                }
                if (j - cntnum[i][1] >= 0 && dp[i - 1][j - cntnum[i][1]] > 0)
                {
                    dp[i][j] += dp[i - 1][j - cntnum[i][1]];
                }
            }
        }

        //输出
        if (dp[cnt][p1] != 1) printf("no\n");
        else
        {
            int choose[maxn];//倒推找出选择的大集合的两类中是哪一类
            int totalpeople = p1;
            for (int i = cnt; i >= 1; --i)
            {
                if (dp[i][totalpeople] == dp[i - 1][totalpeople - cntnum[i][0]])
                {
                    choose[i] = 0;
                    totalpeople -= cntnum[i][0];
                }
                else if (dp[i][totalpeople] == dp[i - 1][totalpeople - cntnum[i][1]])
                {
                    choose[i] = 1;
                    totalpeople -= cntnum[i][1];
                }
            }

            for (int i = 1; i <= p1 + p2; i++)
            {
                int fa = Find(i);
                int set_id = id[fa];
                if (belong[i][0] == set_id&&belong[i][1] == choose[set_id])
                {
                    printf("%d\n", i);
                }
            }
            printf("end\n");
        }
    }
    return 0;
}