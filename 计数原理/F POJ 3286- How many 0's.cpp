#include<iostream>
using namespace std;
long long m, n;
int num[15];
long long Solve(long long v)
{
    if (v < 0) return 0;
    long long spre = v / 10, stail = 0;
    int cnt = 0;
    while (v)
    {
        num[cnt++] = v % 10;
        v /= 10;
    }
    if (cnt == 1||cnt==0) return 1;
    long long base = 1;
    long long sum = 1;

    for (int i = 0; i<cnt-1; ++i)
    {
        if (num[i]==0)
        {
            sum += (spre - 1)*base + stail + 1;
        }
        else
        {
            sum += spre*base;
        }
        spre /= 10;
        stail += num[i] * base;
        base *= 10;
    }
    return sum;
}
int main()
{
    while (~scanf("%lld%lld", &m, &n))
    {
        if (m < 0)break;
        printf("%lld\n", Solve(n) - Solve(m - 1));
    }
    return 0;
}