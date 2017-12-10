#include<cstring>
#include<iostream>
#include<cstdio>
#define MAXN 20
#define ll long long
using namespace std;

ll m[MAXN], p[MAXN];
int n;
//a*x=1(mod b)
void exgcd(ll a, ll b, ll& x, ll& y)
{  //exgcd求乘法取模运算的逆元
    if (!b)
    {
        y = 0, x = 1;
        return;
    }
    else
    {
        exgcd(b, a%b, x, y);
        ll temp = x;
        x = y;
        y = temp - a / b*y;
    }
}

ll crt()
{
    ll P = 1, ans = 0;
    for (int i = 0; i<n; i++)
    {
        P *= p[i];
    }
    for (int i = 0; i<n; i++)
    {
        ll mi = P / p[i], x, y;
        exgcd(mi, p[i], x, y);
        ans = (ans + m[i] * x*mi) % P;
    }
    if (ans<0)
    {
        ans += P;
    }
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i<n; i++)
    {
        scanf("%lld%lld", &p[i], &m[i]);
    }
    printf("%lld\n", crt());
    return 0;
}