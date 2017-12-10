#include<iostream>
#include<cstdio>
using namespace std;
int dig1[20];
int dig2[20];
long long x[12];
long long y[12];
long long Cal(long long n, int x,int len,int *dig)
{
    long long front = n / 10, rear = 0, base = 1;
    long long sum = 0;
    for (int i = 1; i <= len; i++)
    {
        if (dig[i] > x)
        {
            sum += 1ll * (front + 1)*base;
        }
        else if (dig[i] == x)
        {
            sum += 1ll * front*base + rear + 1;
        }
        else sum += 1ll * front*base;
        front /= 10;
        rear = dig[i] * base + rear;
        base *= 10;
    }
    if (x == 0)//0被重复计算了，一位数多算了一个0，两位数多算了10个零，如此我们减去多算的就好了   
    {
        long long m = 1;
        while (n)
        {
            sum -= m;
            m *= 10;
            n /= 10;
        }
    }
    return sum;
}
int main()
{
    long long a,b;
    while (~scanf("%I64d%I64d", &a,&b))
    {
        long long t = a-1;
        int lena = 0;
        while (t)
        {
            dig1[++lena] = t % 10;
            t /= 10;
        }
        t = b;
        int lenb = 0;
        while (t)
        {
            dig2[++lenb] = t % 10;
            t /= 10;
        }
        for (int i = 0; i <= 9; i++) x[i] = Cal(a-1, i, lena,dig1);
        for (int i = 0; i <= 9; i++) y[i] = Cal(b, i, lenb, dig2);
        for (int i = 0; i <= 9; i++) printf("%I64d\n", y[i] - x[i]);
    }
    return 0;
}