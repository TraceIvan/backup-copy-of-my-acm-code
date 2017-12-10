//��N�������γ�1~K�����ж����ֿ��ܣ�Ȼ������ܵķ��䷽������Ϊ��ĿҪ������ĸ���
//��һ��˹������S(N, K) = S(N - 1, K - 1) + (N - 1)*S(N - 1, k)ǡǡ������N��Ԫ���γ�K���ǿ�ѭ�����еķ�����
//S(N,M)-S(N-1,M-1)����ʾN��Ԫ���γ�M��������ȥ1���Գɻ�����ʣ�µ�N-1��Ԫ���γ�M-1��������õĽ����������ֵ
#include<iostream>
using namespace std;
long long stl[25][25], cal[25];
void Init()
{
    cal[0] = cal[1] = 1;
    for (int i = 2; i <= 20; i++) cal[i] = cal[i - 1] * i;
    for (int i = 1; i <= 20; i++)
    {
        stl[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            stl[i][j] = stl[i - 1][j - 1] + (i - 1)*stl[i - 1][j];
        }
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    Init();
    while (t--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        long long ans = 0;
        for (int i = 1; i <= k; i++)
        {
            ans += stl[n][i] - stl[n - 1][i - 1];
        }
        printf("%.4lf\n", 1.0*ans / cal[n]);
    }
    return 0;
}