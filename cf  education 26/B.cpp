#include<iostream>
#include<memory.h>
#include<cstdio>
using namespace std;
int n, m;
const int maxn = 110;
char mp[maxn][maxn];
bool vis[maxn][maxn];
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++) cin >> mp[i][j];
        }
        memset(vis, 0, sizeof(vis));
        int rr, rc, gr, gc, br, bc;
        bool flag;
        int cntr = 0,cntg=0,cntb=0;
        int sti = 0, stj = 0;
        if (n % 3 == 0)
        {
            bool fg = true;
            int dis = n / 3;
            if (mp[0][0] == mp[dis][0]||mp[0][0]==mp[2*dis][0]||mp[dis][0]==mp[dis*2][0])
            {
                fg = false;
            }
            else
            {
                for (int i = 0; fg&& i < n; i++)
                {
                    for (int j = 0; fg&&j < m; j++)
                    {
                        if (mp[i][j] != mp[dis*(i / dis)][0]) fg = false;
                    }
                }
            }
            if (fg) flag = true;
            else flag = false;
        }
        if (!flag&&m % 3 == 0)
        {
            bool fg = true;
            int dis = m / 3;
            if (mp[0][0] == mp[0][dis] || mp[0][0] == mp[0][2 * dis] || mp[0][dis] == mp[0][2 * dis])
            {
                fg = false;
            }
            else
            {
                for (int j = 0;fg&& j < m; j++)
                {
                    for (int i = 0;fg&& i < n; i++)
                    {
                        if (mp[i][j] != mp[0][dis*(j / dis)]) fg = false;
                    }
                }
            }
            if (fg) flag = true;
            else flag = false;
        }
        if (n % 3 != 0 && m % 3 != 0) flag = false;
        if (!flag) printf("NO\n");
        else
        {
            printf("YES\n");
        }
    }
    return 0;
}