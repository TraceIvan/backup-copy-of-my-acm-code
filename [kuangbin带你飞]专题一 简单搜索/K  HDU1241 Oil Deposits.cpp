#include<iostream>
#include<memory.h>
using namespace std;
char mp[110][110];
int n, m;
bool vis[110][110];
int dr[] = {0,-1,-1,-1,0,1,1,1};
int dc[] = {-1,-1,0,1,1,1,0,-1};
void DFS(int r, int c)
{
    vis[r][c] = true;
    for (int i = 0; i < 8; i++)
    {
        int tr = r + dr[i];
        int tc = c + dc[i];
        if (tr < n&&tr >= 0 && tc < m&&tc >= 0)
        {
            if (mp[tr][tc] == '@' && !vis[tr][tc])
                DFS(tr, tc);
        }
    }
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        if (m == 0) break;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++) cin >> mp[i][j];
        }
        memset(vis, 0, sizeof(vis));
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (mp[i][j] == '@' && !vis[i][j])
                {
                    DFS(i, j);
                    cnt++;
                }
            }
        }
        printf("%d\n", cnt);
    }

    return 0;
}