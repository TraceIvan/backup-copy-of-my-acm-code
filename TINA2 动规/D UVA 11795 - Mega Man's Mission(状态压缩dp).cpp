#include<iostream>
#include<cstdio>
#include<memory.h>
using namespace std;
typedef long long ll;
char s[20];
const int maxn = (1 << 16) + 10;
int N;
int w[maxn];//�洢�����[0]�͵���[1:]������
int atk[maxn];//��������ÿ��״̬����ɱ���Ļ�����
ll dp[maxn];// 2 �� 16 �η��ᱬ int�� // ����ͳ��ÿ��״̬��˳�򷽰�����
int Exchange()
{
    int ans = 0;
    int sz = strlen(s);
    for (int i = 0; i < sz; i++)
    {
        if (s[i] == '1') ans = ans | (1 << i);//��i+1λ����ܱ�ɱ�������i+1λΪ1
    }
    return ans;
}
int main()
{
    int T;
    cin >> T;
    int Case = 1;
    while (T--)
    {
        cin >> N;
        for (int i = 0; i <= N; i++)
        {
            scanf("%s", s);
            w[i] = Exchange();
            //cout << i << ' ' << w[i] << endl;
        }
        int total = (1 << N) - 1;//����N�����ˣ�һ�������2^N-1��״̬��ÿ�������ܹ�ɱ������ɱ����
        for (int st = 0; st <= total; st++)
        {//st��Ϊ�����ƴ洢��״̬
            atk[st] = w[0];//��ʼΪ��������õ������ܹ�ɱ������
            for (int i = 1; i <= N; i++)//����ÿ������
            {
                int j = i - 1;//i����������������λ��
                if (st&(1 << j))
                {//�����״̬����ɱ�� i����ô��״̬Ҳ����ɱ��i���ܸɵ���
                    atk[st] = atk[st] | w[i];
                }
            }
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;//һ������ɱ���ķ�����Ϊ1
        for (int st = 1; st <= total; st++)
        {
            for (int i = 0; i < N; i++)
            {//����N������
                if (st & 1 << i)
                {//�����״̬�ܹ�ɱ����i+1������(���˴�1��ʼ��ţ������ڶ����ƴ洢��ɱ��״̬�д洢��λ��Ϊi),��ô st �ɲ���ɱ�� i ��״̬ת�ƹ���, ��st^(1<<i)�����
                    if (atk[st ^ (1 << i)] & 1 << i)//����st^(1<<i)����״̬�ܹ�ɱ���õ���
                    {
                        dp[st] += dp[st ^ (1 << i)];
                    }
                }
            }
        }
        printf("Case %d: %lld\n", Case++, dp[total]);
    }
    return 0;
}