#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 50010;
struct line
{
    int x;
    int y;
}ll[maxn];
int n;
bool Cmp(const line&a, const line&b)
{
    if (a.x == b.x)return a.y > b.y;
    else return a.x < b.x;
}
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &ll[i].x, &ll[i].y);
        }
        sort(ll, ll + n, Cmp);
        line t = ll[0];
        int ans = 0;
        for (int i = 1; i < n; i++)
        {
            if (ll[i].y <= t.y)
            {
                ans = max(ans, ll[i].y - ll[i].x);
            }
            else if (ll[i].x <= t.y&&ll[i].y > t.y)
            {
                ans = max(ans, t.y - ll[i].x);
                t = ll[i];
            }
        }
        printf("%d\n", ans);
    }



    return 0;
}