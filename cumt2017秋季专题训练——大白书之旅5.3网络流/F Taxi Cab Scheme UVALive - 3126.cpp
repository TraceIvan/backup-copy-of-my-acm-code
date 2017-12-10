#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int n, nl, nr;
const int maxn = 510;
bool mp[maxn][maxn];
int l_match[maxn], r_match[maxn], visl[maxn], visr[maxn];
bool dfs(int lx)
{
    visl[lx] = true;
    for (int ly = 1; ly <= nr; ly++)
    {
        if (mp[lx][ly] && !visr[ly])
        {
            visr[ly] = true;
            if (!r_match[ly] || dfs(r_match[ly]))
            {
                l_match[lx] = ly;
                r_match[ly] = lx;
                return true;
            }
        }
    }
    return false;
}

int maxmatch()
{
    int ans = 0;
    memset(l_match, 0, sizeof(l_match));
    memset(r_match, 0, sizeof(r_match));
    for (int i = 1; i <= nl; i++)
    {
        memset(visl, 0, sizeof(visl));
        memset(visr, 0, sizeof(visr));
        if (dfs(i)) ans++;
    }
    return ans;
}

struct node
{
    int time;
    int start[2];
    int end[2];
    int cost;
}ps[maxn];

bool check(int from, int to)
{
    if (ps[from].time + ps[from].cost + abs(ps[to].start[0] - ps[from].end[0]) + abs(ps[to].start[1] - ps[from].end[1]) + 1 <= ps[to].time) return true;
    else return false;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(mp, 0, sizeof(mp));
        scanf("%d",&n);
        nl = nr = n;
        for (int i = 1; i <= n; i++)
        {
            int hh, mm;
            char c;
            scanf("%d%c%d", &hh, &c, &mm);
            ps[i].time = hh * 60 + mm;
            scanf("%d%d", &ps[i].start[0], &ps[i].start[1]);
            scanf("%d%d", &ps[i].end[0], &ps[i].end[1]);
            ps[i].cost = abs(ps[i].start[0] - ps[i].end[0]) + abs(ps[i].start[1] - ps[i].end[1]);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i!=j&&check(i, j)) mp[i][j]  = true;
            }
        }
        int ans = maxmatch();
        printf("%d\n", n - ans);
    }
    return 0;
}