#include<iostream>
#include<algorithm>
using namespace std;
int A[50010];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        long long v = 0,ans=0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &A[i]);
            v = v + A[i];
            if (v < 0) ans = max(ans, -v);
        }
        printf("%lld\n", ans);
    }
    return 0;
}