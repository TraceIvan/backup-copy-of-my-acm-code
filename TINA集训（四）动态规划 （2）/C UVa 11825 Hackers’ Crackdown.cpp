//״ѹDP
#include<iostream>
#include<algorithm>
using namespace std;
const int maxst = (1 << 17);
int ini[20];
int cover[maxst];
int dp[maxst];
int main()
{
    int n;
    int Case = 1;
    while (~scanf("%d", &n))
    {
        if (n == 0) break;
        for (int i = 0; i < n; i++)
        {
            ini[i] = 0|(1<<i);//��������
            int m;
            scanf("%d", &m);
            for (int j = 0; j < m; j++)
            {
                int k;
                scanf("%d", &k);
                ini[i] |= (1 << k);//�����ھ�
            }
        }
        int total = (1 << n) - 1;//��״̬��
        for (int i = 0; i <=total; i++)
        {
            cover[i] = 0;
            for (int j = 0; j < n; j++)
            {
                if (i&(1 << j))//�����״̬�ܹ�̱����j̨����
                {
                    cover[i] |= ini[j];//��ôҲ��̱�����ڽӵĵ���
                }
            }
        }
        dp[0] = 0;
        for (int i = 1; i <= total; i++)
        {
            dp[i] = 0;
            //ö���Ӽ�
            for (int j = i; j > 0; j = (j - 1)&i)
            {
                if (cover[j] == total)//����Ӽ���״̬���ܹ��ɵ����еĵ���
                {
                    dp[i] = max(dp[i], dp[i^j] + 1);//��ô��״̬���ܹ��رյķ���Ϊmax{��״̬�������رյķ�����,��״̬i���ܹ��ɵ����еĵ��Ե��Ӽ��Ĳ��������ܹرյķ�����+1�����1�ɸ��Ӽ�j�ṩ��}
                }
            }
        }
        printf("Case %d: %d\n",Case, dp[total]);
        Case++;
    }
    return 0;
}