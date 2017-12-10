//把前缀和(mod n)求出来。
//1.如果这些和中有一个0，那么我们便得到所求。
//2.否则，这些和中必有两个是相等的（抽屉原理），他们相减为0，这便又找到我们想要的。
//利用抽屉原理，因为N的倍数，A[i]中的任意一个数modN 都是在[1, N - 1] 然后把N个数扔到这些个N - 1个格子里，必定会有两个一样，这两个做减法就是一样的了。
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 50010;
int num[maxn];
long long presum[maxn];
int vis[maxn];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        memset(vis, 0, sizeof(vis));
        presum[0] = 0;
        int l=1 ,r = 1;
        bool flag = false;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &num[i]);
            presum[i] = (presum[i - 1] + num[i])%n;
            if (flag) continue;
            if (presum[i] == 0)
            {
                flag = true;
                l = 1, r = i;
            }
            else if (vis[presum[i]])
            {
                l = vis[presum[i]] + 1;
                r = i;
                flag = true;
            }
            vis[presum[i]] = i;
        }
        printf("%d\n", r - l + 1);
        for (int i = l; i <= r; i++) printf("%d\n", num[i]);
    }
    return 0;
}