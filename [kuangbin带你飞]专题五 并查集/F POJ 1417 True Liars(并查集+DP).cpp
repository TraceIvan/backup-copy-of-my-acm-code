#include<iostream>
using namespace std;
int n, p1, p2;
const int maxn = 1100;
int pre[maxn];//i�ĸ���
int r[maxn];//i��pre[i]�Ĺ�ϵ
//0:ͬ�ࣻ1:��ͬ��

bool vis[maxn];

int cntnum[maxn][2];//cntnum[i][j]��ʾ�ѵ�i�����Ϸֳ��������ֵ�����

int dp[maxn][310];//dp[i][j]��ʾǰi�������к���Ϊj������

int belong[maxn][2];//belong[i][0]��ʾi�����ĸ����࣬belong[i][1]��ʾi���ڸô������һ��С�ࣨ��Ӧcntnum��
int id[maxn];
//���ݺ����븸�ף��������游֮��Ĺ�ϵ�����Ƴ��������游�Ĺ�ϵ
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
        //������󣬵õ����ɸ����ϣ�ÿ������������ͬ���ͬ��
        //2���ҵ��ж��ٸ��󼯺ϣ�ÿ���󼯺���ͬ�༰��ͬ��ĸ���
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
                id[f] = cnt;//��ÿ���󼯺ϵĸ����з���
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

        //���
        if (dp[cnt][p1] != 1) printf("no\n");
        else
        {
            int choose[maxn];//�����ҳ�ѡ��Ĵ󼯺ϵ�����������һ��
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