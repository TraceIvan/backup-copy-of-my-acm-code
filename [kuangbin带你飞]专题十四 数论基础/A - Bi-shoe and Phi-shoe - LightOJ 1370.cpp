//ŷ������
//��������n��ŷ��������С��n������������n���ʵ�������Ŀ����(1) = 1��
//���⣺
//��һЩ��Ai���� i ��������Ai��Щ���������ĳ����ŷ��������ֵ������Ҫ����� Ni ��ŷ������ֵ��С��Ai��������Ҫ��ľ�����Щ Ni ��Щ���ֵĺ�sum������������Ҫsum��С�����sum��С���١�
//����˼·��
//Ҫ�����С�����ǿ�����ÿ����������С����ô�������õ��Ŀ϶�����һ����Сֵ������һ������ŷ������ֵ��(N)��������ô�����������С��N ?����֪����һ������P��ŷ������ֵ��(P) = P - 1�������������֪����(N)����ô��С��N������ӽ���(N)�����Ҵ��ڦ�(N)�����������ǰ������������֮�����жϾͿ����ˡ�
#include<iostream>
#include<memory.h>
#include<cstdio>
using namespace std;
const int maxn = 1010000;
bool isp[maxn];
int prime[maxn], cnt;
int v[maxn];//����i��ŷ������ֵ��������ڵ���������С����
void makePrime()
{
    //��������ɸ
    memset(isp, true, sizeof(isp));
    isp[0] = isp[1] = false;
    cnt = 0;
    for (int i = 2; i < maxn; ++i)
    {
        if (isp[i])//������
        {
            prime[cnt++] = i;//���������
        }
        for (int j = 0; j < cnt && i * prime[j] < maxn; ++j)
        {
            isp[i * prime[j]] = false;//��ǰ���������������������������������
            if (i % prime[j] == 0)//���i�ܱ�ĳһ����С���������������˳�
            {
                break;
            }
        }
    }
    memset(v, 0, sizeof(v));
    for (int i = 1,p=0; i <= 1000000; i++)
    {
        if (i < prime[p])v[i] = prime[p];
        else
        {
            p++;
            v[i] = prime[p];
        }
    }
}
int main()
{
    makePrime();
    int t;
    int Case = 1;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        long long sum = 0;
        for (int i = 0; i < n; i++)
        {
            int var;
            scanf("%d", &var);
            sum += v[var];
        }
        printf("Case %d: %lld Xukha\n", Case++, sum);
    }
    return 0;
}
