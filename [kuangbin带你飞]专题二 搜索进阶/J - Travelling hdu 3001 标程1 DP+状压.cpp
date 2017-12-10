#include<stdio.h>
#include<math.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 12
#define M 59050
#define LL long long
const int inf = 0x1f1f1f1f;  //ע���ʼ��ֵ
int tri[N] = { 0,1,3,9,27,81,243,729,2187,6561,19683,59049 };//3^i��
int g[N][N];//��ͼ
int dig[M][N]; //dig[i][j]��¼I״̬��J���Ƿ���֣����ּ���
int dp[M][N]; //dp[s][j] ��״̬s�£���jΪ�յ����̾���
void inti()     //���ÿ��״̬s��Ӧ��3����λ����Ϣ
{
    int i, j, t;
    for (i = 1; i<M; i++)//����״̬��
    {
        for (t = i, j = 1; j <= 10; j++)
        {
            dig[i][j] = t % 3;//�����״̬�µ���ÿ���ĳ��д���
            t /= 3;
            if (!t) break;
        }
    }
}
int main()
{
    int i, j, a, b, c;
    int n, m, s;
    inti();
    while (scanf("%d%d", &n, &m) != -1)
    {
        memset(g, inf, sizeof(g));
        memset(dp, inf, sizeof(dp));
        for (i = 0; i<m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            g[a][b] = g[b][a] = min(c, g[a][b]);
        }
        for (i = 1; i <= n; i++)      //��ʼ״̬��������һ����Ϊ��㣬
            dp[tri[i]][i] = 0;   //������Ȼ��ʼ��Ϊ0
        int ans = inf;
        for (s = 1; s<tri[n + 1]; s++)  //��s״̬��iΪ�յ�ʱ��������״̬��ֵ
        {
            int f = 1;
            for (i = 1; i <= n; i++)
            {
                if (dig[s][i] == 0)     //�жϵ�ǰ״̬S�£�ÿ�������Ƿ��ѵ���
                    f = 0;
                if (dp[s][i] == inf)
                    continue;
                for (j = 1; j <= n; j++) //dp[s][i]״̬��dp[s+tri[j]][j]״̬
                {
                    if (g[i][j] == inf || i == j || dig[s][j] >= 2)
                        continue;
                    int news = s + tri[j];
                    dp[news][j] = min(dp[news][j], dp[s][i] + g[i][j]);
                }
            }
            if (f)//�жϵ�ǰ״̬S�£�ÿ�����ж��ѵ���
                for (i = 1; i <= n; i++)
                    ans = min(ans, dp[s][i]);
        }
        if (ans == inf)
            ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}
