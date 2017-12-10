#include<iostream>
using namespace std;
int main()
{
    int Case = 1;
    long long n;
    long long k;
    while (~scanf("%lld%lld", &n,&k))
    {
        if (k <= n - 1) printf("Case #%d: %lld\n", Case, k);
        else
        {
            long long ans = (k-(n-1)) % (2 * (n - 1));
            if (ans == 0) ans = 2 * (n - 1);
            if (ans <= n-1)
            {
                if(ans==1) printf("Case #%d: %lld\n", Case,n);
                else printf("Case #%d: %lld\n", Case, ans-1);
            }
            else
            {
                if(ans==n) printf("Case #%d: %lld\n", Case, n-1);
                else printf("Case #%d: %lld\n", Case,ans-n);
            }
        }
        Case++;
    }
    return 0;
}