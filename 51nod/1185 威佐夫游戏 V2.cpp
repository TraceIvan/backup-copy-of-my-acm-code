#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define LL long long
LL a, b, c, qian, hou, pp, mod = 1000000000;
LL gold[3] = { 618033988,749894848,204586834 }; //将 0.618033988749894848204586834... 拆成整数放进数组里
//ak =[k（1+√5）/2]，bk= ak + k （k=0，1，2，...n 方括号表示取整函数)
int main()
{
    int t; scanf("%d", &t);
    while (t--)
    {
        scanf("%lld%lld", &a, &b);
        if (a>b)
            swap(a, b);
        c = b - a;
        qian = c / mod; hou = c%mod; //把10 ^ 18分成两部分10 ^ 9
        LL lll = hou*gold[2];//乘法模拟
        lll = qian*gold[2] + hou*gold[1] + lll / mod;
        lll = qian*gold[1] + hou*gold[0] + lll / mod;
        lll = c + qian*gold[0] + lll / mod;
        if (a == lll)
            printf("B\n");
        else
            printf("A\n");
    }
    return 0;
}