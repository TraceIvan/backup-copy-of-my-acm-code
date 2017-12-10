#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
LL n, k;
int main()
{
    while (~scanf("%I64d%I64d", &n, &k))
    {
        LL ans = n/k;
        if (ans % 2 == 1) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
