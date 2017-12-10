#include<iostream>
using namespace std;
int C[410][510];
const int MOD = 1000007;
void Init()
{
    C[0][0] = 1;
    for (int i = 1; i < 410; i++)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

}
int main()
{
    Init();
    int t;
    int Case = 1;
    scanf("%d", &t);
    while (t--)
    {
        int n, m, k;
        scanf("%d%d%d", &m, &n, &k);
        int total = (1 << 4) - 1;
        int sum = 0;
        for (int st = 0; st <= total; st++)
        {//ö�ٲ��ŵ����
            int cnt = 0, r1 = m, c1 = n;
            if (st & 1) r1--, cnt++;//��һ�в���
            if (st & 2) r1--, cnt++;//���һ�в���
            if (st & 4) c1--, cnt++;//��һ�в���
            if (st & 8) c1--, cnt++;//���һ�в���
            if (cnt & 1) sum = (sum - C[r1*c1][k] + MOD) % MOD;//�������
            else sum = (sum + C[r1*c1][k]) % MOD;//ż�����
        }
        printf("Case %d: %d\n", Case++, sum);
    }
    return 0;
}