#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<functional>
#include<memory>
#include<memory.h>
#include<cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 210;
int num[maxn];
int sum[maxn];
int dp[maxn][maxn];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        memset(dp, 0, sizeof(dp));
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &num[i]);
            sum[i] = sum[i - 1] + num[i];
        }
        for (int len = 2; len <= n; len++)
        {
            for (int start = 1; start <= n-len+1; start++)
            {
                int ed = start +len-1;
                dp[start][ed] = INF;
                for (int k = start; k <ed; k++)
                {
                    dp[start][ed] = min(dp[start][k] + dp[k + 1][ed] + sum[ed] - sum[start - 1], dp[start][ed]);
                }
            }
        }
        printf("%d\n", dp[1][n]);
    }
    return 0;
}
/*
dp[start][end]��ʾ�ӵ�start�ѿ�ʼ��end�ѽ��кϲ���dp[1][n]Ϊ�ϲ������ŵ÷֡�����start��Ҫ�ϲ��ĳ���ȷ���ˣ�endҲ��ȷ��������end���е�����
˼�����ڹ����У��κ�һ��ʯ�Ӷ��������Ѻϲ������ģ�������̸տ�ʼʱ���ǽ����������ڵĵ�i�Ѻ͵�i+1�Ѻϲ�����������ǽ����ӵ�1��k�Ѻϲ��ɵ�һ��(1)�����k+1�ѵ�n�Ѻϲ��ɵ�һ��(2)��(1)(2)�����Ѻϲ��ġ�
dp[start][start+len] =
min(dp[start][k]+dp[k+1][start+len]+��a[start~start+len]) ;
(start<=k < start+len), lenΪҪ�ϲ��Ķ�����1��n��
*/