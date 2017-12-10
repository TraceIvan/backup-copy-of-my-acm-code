#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 1010;
bool mp[maxn][maxn];
int L_match[maxn], R_match[maxn], visL[maxn], visR[maxn];
int n, nl, nr;
bool dfs(int lx)
{
    visL[lx] = true;
    for (int ly = 1; ly <= nr; ly++)
    {
        if (mp[lx][ly] && !visR[ly])
        {
            visR[ly] = true;
            if (!R_match[ly] || dfs(R_match[ly]))
            {//如果当前的ly没有被匹配，或者已经匹配但是和ly匹配的lx'能够和其他ly'匹配，那么当前ly和lx就可以匹配
                L_match[lx] = ly;
                R_match[ly] = lx;
                return true;
            }
        }
    }
    return false;
}

int maxmatch_XYL()
{
    int ans = 0;
    memset(L_match, 0, sizeof(L_match));
    memset(R_match, 0, sizeof(R_match));
    for (int i = 1; i <= nl; i++)
    {
        memset(visL, 0, sizeof(visL));
        memset(visR, 0, sizeof(visR));
        if (dfs(i)) ans++;
    }
    return ans;
}
int main()
{
    while (~scanf("%d%d%d", &nl, &nr, &n))
    {
        if (nl == 0 && nr == 0 && n == 0) break;
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= n; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            mp[x][y] = true;
        }
        int ans = maxmatch_XYL();
        printf("%d", ans);
        //寻找最小点覆盖集并输出
        memset(visL, 0, sizeof(visL));
        memset(visR, 0, sizeof(visR));
        //从当前未匹配的lx开始dfs,如果有边a（说明原本假设的最小点覆盖集<即已匹配的lx>不能覆盖到当前dfs到的这一条边），那么原本和边a连接的lx'需更改为a所连接的ly'
        for (int i = 1; i <= nl; i++) if (!L_match[i]) dfs(i);
        for (int i = 1; i <= nl; i++) if (!visL[i]) printf(" r%d", i);//在初期假设的最小点覆盖集中无需删的点
        for (int i = 1; i <= nr; i++) if (visR[i]) printf(" c%d", i);//在dfs过程中lx'更换成的ly'
        printf("\n");
    }
    return 0;
}