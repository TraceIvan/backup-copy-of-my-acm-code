#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long  LL;
const int maxn = 1e6 + 10;
int prime[maxn];//�洢����
int sprime[maxn];//�洢P-1��������
bool isp[maxn];//���ֻ��0��1���ж��Ƿ�Ϊ����
int k;//��¼Maxn���ڵ���������
int cnt;//��¼�����ӵĸ���
void is_prime()
{
    memset(isp,true,sizeof(isp));//�����еĶ�����������Ϊ1
    for (int i = 2; i<maxn; i++)
    {
        if (isp[i])
        {
            prime[k++] = i;
            for (int j = i + i; j<maxn; j += i)
                isp[j] = false;
        }
    }
}
void Divide(int n)//��n�ֽ�Ϊ������
{
    cnt = 0;
    int t = (int)sqrt(1.0*n);
    for (int i = 0; prime[i] <= t; i++)
    {
        if (n%prime[i] == 0)
        {
            sprime[cnt++] = prime[i];
            while (n%prime[i] == 0)//��Ϊ�п����ж��peime[i]
                n /= prime[i];
        }
    }
    if (n>1)
        sprime[cnt++] = n;//����ֻ���Լ�һ��������
}
//��a^b%mod
LL modexp(LL a, LL b, int mod)//������ȡģ
{
    LL res = 1;
    while (b>0)
    {
        a = a%mod;
        if (b & 1)
            res = res*a%mod;
        b = b >> 1;
        a = a*a%mod;
    }
    return res;
}

int main()
{
    int p;
    is_prime();
    while (~scanf("%d", &p))
    {
        Divide(p - 1);
        for (int g = 2; g<p; g++)
        {
            int flag = 1;
            for (int i = 0; i<cnt; i++)
            {
                int t = (p - 1) / sprime[i];
                if (modexp(g, t, p) == 1)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                int root = g;
                printf("%d\n", root);
                break;//ȥ��break�Ļ��������е�ԭ��������break������С��ԭ����
            }
        }
    }
    return 0;
}