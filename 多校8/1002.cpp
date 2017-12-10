#include<iostream>
#include<cmath>
using namespace std;
const int MOD = 1e9 + 7;
int GCD(int a, int b)
{
    if (a < b) a = a^b, b = a^b, a = a^b;
    while (a%b)
    {
        int t = a%b;
        a = b;
        b = t;
    }
    return b;
}
int main()
{
    freopen("out.txt", "w", stdout);
    for (int n = 1; n <= 1000; n++)
    {
    
        long long sum = 0;
        for (int i = 1; i <=n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                if (GCD(j, i) == 1) sum = (sum + (int)ceil(1.0*i / j)) % MOD;;
            }
            
        }
        printf("%lld, ", sum);
    }
    return 0;
}