#include<iostream>
#include<cstdio>
using namespace std;
int dig[20];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int t = n;
        int len = 0;
        while (t)
        {
            dig[++len] = t % 10;
            t /= 10;
        }
        int front = n/10,rear=0,base=1;
        long long sum = 0;
        for (int i = 1; i <=len; i++)
        {
            if (dig[i] > 1)
            {
                sum += 1ll*(front+1)*base;
            }
            else if(dig[i]==1)
            {
                sum += 1ll * front*base + rear + 1;
            }
            else sum += 1ll*front*base;
            front /= 10;
            rear = dig[i]*base+rear;
            base *= 10;
        }
        printf("%I64d\n", sum);
    }
    return 0;
}
//如果要计算百位上1出现的次数，它要受到3方面的影响：百位上的数字，百位一下（低位）上的数字，百位一上（高位）上的数字。
//如果百位上数字为0，百位上可能出现1的次数由更高位决定。比如：12013，则可以知道百位出现1的情况可能是：100~199，1100~1199, 2100~2199，，.........，11100~11199，一共1200个。可以看出是由更高位数字（12）决定，并且等于更高位数字（12）乘以 当前位数（100）。
//如果百位上数字为1，百位上可能出现1的次数不仅受更高位影响还受低位影响。比如：12113，则可以知道百位受高位影响出现的情况是：100~199，1100~1199, 2100~2199，，.........，11100~11199，一共1200个。和上面情况一样，并且等于更高位数字（12）乘以 当前位数（100）。但同时它还受低位影响，百位出现1的情况是：12100~12113, 一共114个，等于低位数字（113） + 1。
//如果百位上数字大于1（2~9），则百位上出现1的情况仅由更高位决定，比如12213，则百位出现1的情况是：100~199, 1100~1199，2100~2199，...........，11100~11199, 12100~12199, 一共有1300个，并且等于更高位数字 + 1（12 + 1）乘以当前位数（100）。