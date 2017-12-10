//��������3 2 4 5 6 8 1 2 9 7��F[1��0]��ʾ��1�����𣬳���Ϊ2^0=1�����ֵ����ʵ����3������� F[1��2]=5��F[1��3]=8��F[2��0]=2��F[2��1]=4������������Կ���F[i,0]��ʵ�͵���A[i]��������DP��״̬����ֵ���Ѿ����ˣ�ʣ�µľ���״̬ת�Ʒ��̡�
//���ǰ�F[i��j]ƽ���ֳ����Σ���Ϊf[i��j]һ����ż�������֣�����i��i+2^(j-1)-1Ϊһ�Σ�i+2^(j-1)��i+2^j-1Ϊһ��(���ȶ�Ϊ2^��j-1��)��
//������˵������i=1��j=3ʱ����3,2,4,5 �� 6,8,1,2�����Ρ�F[i��j]���������ε����ֵ�е����ֵ���������ǵõ��˶�̬�滮����F[i, j]=max��F[i��j-1], F[i + 2^(j-1)��j-1]����
//Ȼ���ǲ�ѯ�����ڸ��������䲻һ����2�Ĵ��ݣ�������Ҫȡһ����С�ݸ������䡣ȡk=[log2(j-i+1)]������ȡ�������У�RMQ(A, i, j)=min{F[i,k],F[j-2^k+1,k]}�����������Ϊ[i,i+(2^k)-1] [j-(2^k)+1,j]������֤�����������������غϵط��ġ�
//����˵����Ҫ������[2��8]�����ֵ����Ҫ�����ֳ�[2,5]��[5,8]�������䣬��Ϊ��������������ֵ���ǿ���ֱ����f[2��2]��f[5��2]�õ���
#include<iostream>
#include<memory.h>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn = 10005;
int Fmax[maxn][20], Fmin[maxn][20];
//[i][j]��ʾ[i,2^j-1]�����ڵ���ֵ
int n, q;
void RMQ()
{
    for (int i = 1; i <= n; i++)
    {
        int num;
        scanf("%d", &num);
        Fmin[i][0] = Fmax[i][0] = num;
    }
    for (int j = 1; j < 20; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (i + (1 << j) - 1 <= n)
            {
                Fmax[i][j] = max(Fmax[i][j - 1], Fmax[i + (1 << (j - 1))][j - 1]);
                Fmin[i][j] = min(Fmin[i][j - 1], Fmin[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}
int main()
{
    while (~scanf("%d", &n))
    {
        memset(Fmax, 0, sizeof(Fmax));
        memset(Fmin, 0, sizeof(Fmin));
        RMQ();
        scanf("%d", &q);
        for (int i = 0; i < q; i++)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            l++, r++;
            int k = 0;
            while ((1 << (k + 1)) <= r - l + 1) k++;
            //int k = ceil(log(1.0+r - l) / log(2.0));  
            int maxnum = max(Fmax[l][k], Fmax[r - (1 << k) + 1][k]);
            int minnum = min(Fmin[l][k], Fmin[r - (1 << k) + 1][k]);
            printf("%d\n", maxnum);
        }
    }
    return 0;
}