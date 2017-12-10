#include<iostream>
using namespace std;
long long Cal(long long a)
{
    return a*(a - 1) / 2;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        long long n, m;
        scanf("%lld%lld", &n, &m);
        if (m >= n*(n - 1) / 2) printf("%lld\n", n*(n - 1));
        else if(m>=n-1)
        {
            long long sum = n-1 + 2*Cal(n-1);
            sum -= m - n+1;
            printf("%lld\n", sum * 2);
        }
        else
        {
            long long t = Cal(m);
            long long t0 = Cal(n);
            long long sum = m + t * 2 + n*(t0 - m - t);
            printf("%lld\n", sum * 2);
        }
    }
    return 0;
}