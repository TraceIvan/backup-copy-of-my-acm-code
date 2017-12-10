#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 1010;
int n, k;
struct Score
{
    int a;
    int b;
}tests[maxn];
long long suma, sumb;

double tt;//假设的当前正确率
bool Cmp(const Score&a, const Score&b)
{
    return a.a - tt*a.b > b.a - tt*b.b;//对当前正确率贡献度大的排前面
}

bool Judge(double rt)
{
    tt = rt;
    sort(tests, tests + n, Cmp);
    long long sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; i++)
    {
        if(i<n-k)sum1 += tests[i].a, sum2 += tests[i].b;
        else if (tests[i].a - rt*tests[i].b > 1e-4) sum1 += tests[i].a, sum2 += tests[i].b;
    }
    if (1.0*sum1 / sum2 >= rt) return true;
    else return false;
}

int main()
{
    while (cin >> n >> k, n != 0 || k != 0)
    {
        suma = sumb = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> tests[i].a;
            suma += tests[i].a;
        }
        for (int i = 0; i < n; i++)
        {
            cin >> tests[i].b;
            sumb += tests[i].b;
        }
        double L = 1.0*suma / sumb;
        double R = 1.0;
        while (R - L > 1e-4)
        {
            double mid = (L + R) / 2;
            if (Judge(mid)) L = mid;
            else R = mid;
        }
        printf("%.lf\n", L*100);
    }
    return 0;
}