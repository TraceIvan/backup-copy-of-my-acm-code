#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1000010;
int cnt[maxn];
//求出n个数所有的因子并记录它们出现的次数,然后找到其中 num >= 2(有两个数有这个因子) 的最大值即可
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
            cnt[1]++, cnt[x]++;
            for (int j = 2; j*j <= x; j++)
            {
                if (x%j == 0)
                {
                    cnt[j]++;
                    cnt[x / j]++;
                }
            }
        }
        int ans;
        for (int i = maxnum; i >= 1; --i)
        {
            if (cnt[i] >= 2)
            {
                ans = i;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}