//先对答案进行二分，求满足小于等于该答案的个数（求法：由于每列从上到下的值递增，对每一列找到第一个大于答案的值，然后累加个数），若个数太多，则说明答案太大，否则太小。
#include<iostream>
#include<cstdio>
using namespace std;
const long long INF = 1LL << 50;
long long f(long long i, long long j)
{
    return i*i + 100000 * i + j*j - 100000 * j + i*j;
}
long long n, m;
bool Judge(long long tans)
{
    long long num = 0;
    for (int j = 1; j <= n; j++)
    {
        int l = 1, r = n;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (f(mid, j) > tans)
            {
                r = mid - 1;
            }
            else l = mid + 1;
        }
        num += l - 1;
    }
    if (num >= m) return true;
    else return false;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        scanf("%lld%lld", &n, &m);
        long long R = INF, L = -INF;
        while (L <= R)
        {
            long long mid = (L + R) >> 1;
            if (Judge(mid))
            {
                R = mid - 1;
            }
            else L = mid + 1;
        }
        printf("%lld\n", L);
    }
    return 0;
}