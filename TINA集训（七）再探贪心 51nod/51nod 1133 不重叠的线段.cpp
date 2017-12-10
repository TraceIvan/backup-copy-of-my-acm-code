#include<iostream>
#include<algorithm>
using namespace std;
int n;
const int maxn = 10010;
struct node
{
    int x;
    int y;
}ll[maxn];
bool Cmp(const node&a, const node&b)
{
    if (a.x == b.x) return a.y < b.y;
    else return a.x < b.x;
}
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++) scanf("%d%d", &ll[i].x, &ll[i].y);
        sort(ll, ll + n, Cmp);
        node p = ll[0];
        int ans = 1;
        for (int i = 1; i < n; i++)
        {
            if (ll[i].x >= p.y)
            {
                ans++;
                p = ll[i];
            }
            else if (ll[i].y <= p.y)
            {
                p = ll[i];//选择r较小的
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}