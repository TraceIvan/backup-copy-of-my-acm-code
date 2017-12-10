//f(x)=(1+x/1!+x^2/2!+x^3/3!бн+x^n/n!)^2+(1+x^2/2!+x^4/4!+x^6/6!бн+бн)^2
//e^x=1+x/1!+x^2/2!+x^3/3!бн+x^n/n!;e^(-x)=1-x/1!+x^2/2!-x^3/3!+бн-бн
//e^x+e^(-x)=1+x^2/2!+x^4/4!+x^6/6!бн+бн
// f(x)=e^(2x) * ((e^x+e^(-x))/2)^2
//a(n)=(4^(n-1) + 2^(n-1)) * x^n/n!
//F(n) = (4 ^ (n - 1) + 2 ^ (n - 1)) % 100.
#include<iostream>
using namespace std;
long long quick_pow(long long a, long long b, long long md)
{
    long long sum = 1;
    while (b)
    {
        if (b & 1) sum = (sum*a) % md;
        b >>= 1;
        a = (a*a) % md;
    }
    return sum;
}
int main()
{
    int t;
    long long n;
    while (~scanf("%d", &t) && t)
    {
        int Case = 1;
        while (t--)
        {
            scanf("%lld", &n);
            int sum = (quick_pow(4, n - 1, 100) + quick_pow(2, n - 1, 100)) % 100;
            printf("Case %d: %d\n", Case++, sum);
        }
        printf("\n");
    }
    return 0;
}