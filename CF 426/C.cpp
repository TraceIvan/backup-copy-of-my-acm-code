#include<iostream>
#include<set>
#include<cmath>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        long long a, b;
        scanf("%I64d%I64d", &a, &b);
        bool flag = false;
        int v = (int)pow(1.0*a*b, 1.0 / 3);
        for (long long i = v - 10; i <= v + 10; i++)
        {
            if (i*i*i == 1ll * a*b&&a%i==0&&b%i==0)
            {
                flag = true;
                break;
            }
        }
        if (flag)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}