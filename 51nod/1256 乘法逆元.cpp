#include<iostream>
using namespace std;
//返回d = gcd(a, b);x,y对应于等式ax + by = d中的x、y
long long extendGCD(long long a, long long b, long long &x, long long &y)
{
    if (a == 0 && b == 0) return -1;//无最大公约数
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extendGCD(b, a%b, y, x);
    y -= a / b*x;
    return d;
}
//求逆元 ax = 1(mod n)
long long modReverse(long long a, long long n)
{//要求a,n互质
    long long x, y;
    long long d = extendGCD(a, n, x, y);
    if (d == 1)
    {
        return (x%n + n) % n;//防止为负
    }
    else return -1;//无逆元
}
int main()
{
    long long m, n;
    while (~scanf("%I64d%I64d", &m, &n))
    {//k*m%n=1=>k*m+x(-n)=1=>k*m=1(mod n)=>m关于模n的乘法逆元为k
        printf("%I64d\n", modReverse(m, n));
    }

    return 0;
}