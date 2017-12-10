#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
const int maxn = 1000010;
const int INF = 0x7fffffff;

int num[maxn];
int dp_now[maxn];
int max_pre[maxn];
//dp[i][j]��ʾǰj������ѡȡ��j������ǰ���·ֳ�i�ε����ֵ��
//dp[i][j]=max(dp[i][j-1]+num[j],max(dp[i-1][k]|(0<k<j))+num[j]);
//dp[i][j-1]+num[j]��ʾǰj-1���ֳ�i�飬j������������
//max(dp[i-1][k]|(0<k<j))+num[j]��ʾǰk���ֳ�i-1������ֵ���ϵ�j����������Ĵ�С
int main()
{
    while (~scanf("%d%d", &m, &n))
    {
        for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
        memset(dp_now, 0, sizeof(dp_now));
        memset(max_pre, 0, sizeof(max_pre));
        int tmax;
        for (int i = 1; i <= m; i++)
        {
            tmax = -INF;
            for (int j = i; j <= n; j++)
            {
                dp_now[j] = max(dp_now[j - 1]+num[j], max_pre[j - 1] + num[j]);
                max_pre[j - 1] = tmax;
                tmax = max(tmax, dp_now[j]);
            }
        }
        printf("%d\n", tmax);
    }
    return 0;
}