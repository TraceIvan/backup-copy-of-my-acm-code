//对于任何正整数x, 其约数的个数记做g(x).例如g(1) = 1, g(6) = 4.如果某个正整数x满足：对于任意i(0<i<x), 都有g(i)<g(x), 则称x为反素数。
//性质一:一个反素数的质因子必然是从2开始连续的质数.
//性质二:p = 2 ^ t1 * 3 ^ t2 * 5 ^ t3 * 7 ^ t4.....必然t1 >= t2 >= t3 >= ....
//一个数k=p1^(a1)*p1^(a1)*......pn^(an) (唯一分解定理)，那么这个数因数的个数等于(a1+1)*(a2+1)*......*(an+1)。
#include <iostream>
#include<algorithm>
typedef long long ll;
using namespace std;
const int MAXP = 16;
const int prime[MAXP] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53 };//连乘质数2~53时已经大于10^18所以我们只需要搜到53就行
ll n, res, ans;
void dfs(ll cur, ll num, int key, ll pre)//当前值/当前约数数量/当前深度/上一个数的个数
{
    if (key >= MAXP)
    {
        return;
    }
    else
    {
        if (num > ans)
        {
            res = cur;
            ans = num;
        }
        else if (num == ans)    //  如果约数数量相同，则取较小的数
        {
            res = min(cur, res);
        }

        ll i;
        for (i = 1; i <= pre; i++)
        {//枚举当前质数的个数
            if (cur <= n / prime[key])  //  cur*prime[key]<=n
            {
                cur *= prime[key];
                dfs(cur, num * (i + 1), key + 1, i);
            }
            else
            {
                break;
            }
        }
    }
}

void solve()
{
    res = 1;
    ans = 1;

    dfs(1, 1, 0, 63);
    cout << res << ' ' << ans << endl;
}
int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        cin >> n;
        solve();
    }
    return 0;
}