#include<iostream>
using namespace std;
int main()
{
    long long n;
    while (~scanf("%lld", &n))
    {
        long long ans = 1;
        long long m = n;
        while (m)
        {
            if (m & 1) ans = (ans*n) % 100;
            m = (m >> 1);
            n = (n*n) % 100;
        }
        printf("%lld\n", ans % 10);
    }
    return 0;
}