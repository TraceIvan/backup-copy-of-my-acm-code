#include<cstdio>
#include<ctype.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
int dp[21][801];//dp(j, k)��ʾ��ȡj ����ѡ�ˣ�ʹ���ز�Ϊk �����з����У���غ������Ǹ��������÷�����Ϊ������dp(j, k)�����ı�غ͡�
vector<int> path[21][801];

int main()
{
    int times = 1;
    //    freopen("input.txt","r",stdin);
    //    freopen("output.txt","w",stdout);
    int subtraction[201], _plus[201];
    int n, m, i, j, k;
    while (~scanf("%d%d", &n, &m) && n && m)
    {//һ����n����ѡ�ˣ�Ҫѡm��
        for (i = 0; i<m; ++i)//���vector
            for (j = 0; j<801; ++j)
                path[i][j].clear();
        memset(dp, -1, sizeof(dp));
        int d, p;
        for (i = 0; i < n; i++)
        {
            cin >> d >> p;//����绤���Ϳ��߷��Ĵ��
            subtraction[i] = d - p;//�õ�ÿ���˵ı绤���ķ���-���߷��ķ���
            _plus[i] = d + p;//�õ���
        }
        int fix = 20 * m;//������Ŀ�б�ز��ֵk ����Ϊ�������������������±겻��Ϊ���������ԣ��ڳ����в�������ز��ֵ����������ֵfix=400�������±�Ϊ�������³���
        //Ϊʲôfix = 400�����Ǻ���Ȼ�ģ�m����Ϊ20�ˣ���20�˵�d��Ϊ0��p��Ϊ20ʱ������ֱ�ز�Ϊ - 400��������ر��±긺�����⣬��������ƽ�ƣ���[-400, 400]ӳ�䵽[0, 800]��
        dp[0][fix] = 0;
        for (k = 0; k < n; k++)//˳��ѡ��һ����ѡ��
            for (i = m - 1; i >= 0; i--)//��������
            {
                for (j = 0; j < 2 * fix; j++)
                {
                    if (dp[i][j] >= 0)
                    {
                        if (dp[i + 1][j + subtraction[k]] <= dp[i][j] + _plus[k])
                        {//���з���dp(j-1, x)���ݻ��ɷ���dp(j, k)�ı�Ҫ�����ǣ�����ĳ����ѡ��i��i �ڷ���dp(j-1, x)��û�б�ѡ�ϣ���x+V(i) = k������������ñ�Ҫ������dp(j-1, x)�У�ѡ�� dp(j-1, x) + S(i) ��ֵ�����Ǹ�����ô����dp(j-1, x)�ټ��Ϻ�ѡ��i�����ݱ���˷��� dp(j, k)��
                            //dp[i][j + d[k]] = max(dp[i][j + d[k]], dp[i-1][j] + s[k])
                            dp[i + 1][j + subtraction[k]] = dp[i][j] + _plus[k];
                            path[i + 1][j + subtraction[k]] = path[i][j];//ÿ�θ��¶�Ҫ��pathȫ�����ƹ�����������Ϊ������õ�vector
                            path[i + 1][j + subtraction[k]].push_back(k);
                        }
                    }
                }
            }
        //DP�󣬴ӵ�m�е�dp(m, fix)��ʼ������������С|D-P| ���ɣ���һ����Ϊdp[m][k]!=-1��λ��k������С|D-P|�����ڡ�
        //D+P = dp(m, |D-P| ) ��|D-P|��֪��
        //��ôD = (D + P + | D - P | ) / 2, P = (D + P - | D - P | ) / 2������D��Pʱע������ֵfix
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