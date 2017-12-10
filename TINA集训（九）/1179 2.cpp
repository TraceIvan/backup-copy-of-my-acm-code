#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1000010;
int cnt[maxn];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int x;
        int maxnum = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &x);
            if (x > maxnum) maxnum = x;
            cnt[x]++,cnt[1]++;
        }
        int ans=-1;
        for (int j = maxnum; j >= 1; --j)
        {
            int Count = 0;
            for (int k = j; k <= maxnum; k+=j)
            {
                Count += cnt[k];
                if (Count >= 2)
                {
                    ans = j;
                    break;
                }
            }
            if (ans != -1) break;
        }
        printf("%d\n", ans);
    }
    return 0;
}