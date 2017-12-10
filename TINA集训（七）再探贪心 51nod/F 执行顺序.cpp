#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int n;
const int maxn = 100010;
struct node
{
    int r;
    int o;
}ll[maxn];
bool Cmp(const node&a, const node&b)
{//�����ͷŵĿռ�Ӵ�С����
    return a.r - a.o > b.r - b.o;
}

int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++) scanf("%d%d", &ll[i].r, &ll[i].o);
        sort(ll, ll + n, Cmp);
        long long ans = 0,sum=0;
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, sum+ll[i].r);
            sum += ll[i].o;
        }
        printf("%lld\n", ans);
    }
    return 0;
}