#include<iostream>
#include<algorithm>
using namespace std;
int num[50010];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        long long ans = 0;
        long long s = 0;
        for (int i = 1; i <= n; i++)
        {
            int num;
            scanf("%d", &num);
            s += num;
            if (s < 0 && -s>ans) ans = -s;
        }
        printf("%lld\n", ans);
    }
    return 0;
}