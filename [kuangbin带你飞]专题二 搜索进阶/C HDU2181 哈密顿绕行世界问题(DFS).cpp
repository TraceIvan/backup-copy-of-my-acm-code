#include<iostream>
#include<algorithm>
using namespace std;
int mp[25][3];
int line[25];
int vis[25];
int Case;
void DFS(int st,int cur, int len)
{
    if (cur == st&&len == 21)
    {
        printf("%d: ", Case);
        for (int i = 0; i < 21; i++) printf(" %d", line[i]);
        printf("\n");
        Case++;
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        if (!vis[mp[cur][i]]&&(mp[cur][i]!=st||len==20))
        {
            line[len] = mp[cur][i];
            vis[mp[cur][i]] = true;
            DFS(st, mp[cur][i], len + 1);
            vis[mp[cur][i]] = false;
        }
    }
}
int main()
{
    int lct[3];
    for (int i = 1; i <= 20; i++)
    {
        for (int j = 0; j < 3; j++) scanf("%d", &mp[i][j]);
    }
    int m;
    memset(vis, 0, sizeof(vis));
    while (~scanf("%d", &m))
    {
        if (m == 0)break;
        Case = 1;
        line[0] = m;
        DFS(m,m, 1);
    }
    return 0;
}