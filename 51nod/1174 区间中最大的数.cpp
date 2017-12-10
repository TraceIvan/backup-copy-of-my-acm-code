//例如数列3 2 4 5 6 8 1 2 9 7，F[1，0]表示第1个数起，长度为2^0=1的最大值，其实就是3这个数。 F[1，2]=5，F[1，3]=8，F[2，0]=2，F[2，1]=4……从这里可以看出F[i,0]其实就等于A[i]。这样，DP的状态、初值都已经有了，剩下的就是状态转移方程。
//我们把F[i，j]平均分成两段（因为f[i，j]一定是偶数个数字），从i到i+2^(j-1)-1为一段，i+2^(j-1)到i+2^j-1为一段(长度都为2^（j-1）)。
//用上例说明，当i=1，j=3时就是3,2,4,5 和 6,8,1,2这两段。F[i，j]就是这两段的最大值中的最大值。于是我们得到了动态规划方程F[i, j]=max（F[i，j-1], F[i + 2^(j-1)，j-1]）。
//然后是查询，由于给出的区间不一定是2的次幂，所以需要取一个最小幂覆盖区间。取k=[log2(j-i+1)]，向上取整，则有：RMQ(A, i, j)=min{F[i,k],F[j-2^k+1,k]}，即将区间分为[i,i+(2^k)-1] [j-(2^k)+1,j]，容易证明这两个区间是有重合地方的。
//举例说明，要求区间[2，8]的最大值，就要把它分成[2,5]和[5,8]两个区间，因为这两个区间的最大值我们可以直接由f[2，2]和f[5，2]得到。
#include<iostream>
#include<memory.h>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn = 10005;
int Fmax[maxn][20], Fmin[maxn][20];
//[i][j]表示[i,2^j-1]区间内的最值
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