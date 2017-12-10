#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn = 510;
const int INF = 0x3f3f3f3f;
int mp[maxn][maxn], match[maxn], lx[maxn], ly[maxn], visx[maxn], visy[maxn], slack[maxn];
int n, nx, ny;
//lx,ly为顶标，nx,ny分别为x点集y点集的个数
//match数组记录右边y端点所连的左端点x，visx，visy数组记录是否曾访问过，也是判断是否在增广路上
//KM求二分图最小匹配模板：只需把权值都变成负的，再用KM算出最大权匹配，然后取反就是答案

bool dfs(int x)
{
    visx[x] = 1;
    for (int y = 1; y <= ny; y++)
    {
        if (visy[y]) continue;
        int t = lx[x] + ly[y] - mp[x][y];
        if (t == 0)
        {
            visy[y] = 1;
            if (match[y] == -1 || dfs(match[y]))
            {
                match[y] = x;
                return true;
            }
        }
        else if (slack[y] > t) slack[y] = t;
    }
    return false;
}
int KM()
{
    //初始化
    memset(match, -1, sizeof(match));
    memset(lx, - INF, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for (int i = 1; i <= nx; i++)
    {
        for (int j = 1; j <= ny; j++)
        {
            if (mp[i][j] > lx[i]) lx[i] = mp[i][j];
        }
    }
    for (int x = 1; x <= nx; x++)
    {
        for (int y = 1; y <= ny; y++) slack[y] = INF;
        while (1)
        {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if (dfs(x)) break;
            int d = INF;
            for (int y = 1; y <= ny; y++)
            {
                if (!visy[y] && d > slack[y]) d = slack[y];
            }
            for (int x = 1; x <= nx; x++)
            {
                if (visx[x]) lx[x] -= d;
            }
            for (int y = 1; y <= ny; y++)
            {
                if (visy[y]) ly[y] += d;
                else slack[y] -= d;
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= ny; i++)
    {
        if (match[i] > -1) res += mp[match[i]][i];
    }
    return res;
}
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &mp[i][j]);
                mp[i][j] = mp[i][j];
            }
        }
        nx = ny = n;
        int ans = KM();
        for (int i = 1; i <= n; i++)
        {
            if (i > 1) printf(" %d", lx[i]);
            else printf("%d", lx[i]);
        }
        printf("\n");
        for (int i = 1; i <= n; i++)
        {
            if (i > 1) printf(" %d", ly[i]);
            else printf("%d", ly[i]);
        }
        printf("\n");
        printf("%d\n",ans);
    }
    return 0;
}