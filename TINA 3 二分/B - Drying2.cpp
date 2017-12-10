#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
#define MAXN 100000+10
#define LL long long
int n, k;
int wat[MAXN];

bool Judge(int x)
{
    LL t = 0;
    for (int i = 0; i<n; i++)
    {
        if (wat[i]>x)
        {
            int xx = ceil((wat[i] - x)*1.0 / (k - 1));
            t += xx;
        }
        if (t>x)return false;
    }

    if (t>x)return false;
    else return true;
}
int main()
{
    while (~scanf("%d", &n))
    {
        int l = 1, r = 0;
        for (int i = 0; i<n; i++)
        {
            scanf("%d", &wat[i]);
            r = max(r, wat[i]);
        }
        scanf("%d", &k);

        if (k == 1)
        {
            printf("%d\n", r);
            continue;
        }
        int mid = 0;
        while (l <= r)
        {
            mid = (l + r) / 2;
            if (Judge(mid))
            {
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        printf("%d\n",l);
    }
    return 0;
}