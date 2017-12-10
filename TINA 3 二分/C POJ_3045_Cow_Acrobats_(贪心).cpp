#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 50005;
struct Cow
{
    int w;
    int s;
}cows[maxn];

bool Cmp(const Cow&a, const Cow&b)
{
    if (a.s + a.w > b.s + b.w)  return true;
    else if (a.s + a.w == b.s + b.w) return a.s > b.s;
    else return false;
}

int n;
int main()
{
    while (cin >> n)
    {
        for (int i = 0; i < n; i++) cin >> cows[i].w >> cows[i].s;
        sort(cows, cows + n, Cmp);
        long long risk = 0 - cows[n - 1].s;
        long long ans = risk;
        for (int i = n - 2; i >= 0; i--)
        {
            risk = risk + cows[i + 1].w + cows[i + 1].s - cows[i].s;
            ans = max(ans, risk);
        }
        printf("%lld\n", ans);
    }
    return 0;
}