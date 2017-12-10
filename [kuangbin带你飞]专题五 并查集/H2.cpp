#include<iostream>
#include<algorithm>
using namespace std;
int n, m;
const int maxn = 5050;
int pre[maxn];
int val[maxn];
struct node
{
    int ll;
    int rr;
    int d;
}qry[maxn];
int Map[maxn * 2];
int Find(int x)
{
    if (x == pre[x]) return x;
    else
    {
        int fa = pre[x];
        pre[x] = Find(fa);
        val[x] = (val[x] + val[fa]) % 2;
        return pre[x];
    }
}
bool Union(int x, int y, int v)
{//x<y
    int rx = Find(x), ry = Find(y);
    if (rx == ry) return true;
    else
    {
        if (rx < ry)
        {
            pre[ry] = rx;
            val[ry] = (val[x] + v - val[y] + 2) % 2;
        }
        else
        {
            pre[rx] = ry;
            val[rx] = (val[y] - v - val[x] + 2) % 2;
        }
        return false;
    }
}
int main()
{
    while (~scanf("%d", &n))
    {
        scanf("%d", &m);
        int l, r, v;
        char s[6];
        int cnt = 0;
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d%s", &l, &r, s);
            l = l - 1;
            if (s[0] == 'e') v = 0;
            else v = 1;
            qry[i].ll = l, qry[i].rr = r, qry[i].d = v;
            Map[cnt++] = l;
            Map[cnt++] = r;
        }
        //ÀëÉ¢»¯
        sort(Map, Map + cnt);
        cnt = unique(Map, Map + cnt) - Map;
        for (int i = 0; i <= cnt; i++)
        {
            pre[i] = i;
            val[i] = 0;
        }
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            l = lower_bound(Map, Map + cnt, qry[i].ll) - Map;
            r = lower_bound(Map, Map + cnt, qry[i].rr) - Map;
            v = qry[i].d;
            if (Union(l, r, v))
            {
                if ((val[r] - val[l] + 2) % 2 != v)
                {
                    break;
                }

            }
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}