#include<iostream>
#include<queue>
using namespace std;
char mz[2][15][15];
bool vis[2][15][15];
int n, m, T;
int edz, edx, edy;
struct node
{
    int z;
    int x;
    int y;
    int t;
    node(int zz = 0,int xx=0,int yy=0,int tt=0):z(zz),x(xx),y(yy),t(tt){ }
};
int dr[] = { 1,-1,0,0 };
int dc[] = {0, 0, 1, -1};
bool BFS()
{
    memset(vis, 0, sizeof(vis));
    queue<node>q;
    q.push(node(0, 0, 0, 0));
    vis[0][0][0] = true;
    while (!q.empty())
    {
        node u = q.front();
        q.pop();
        if (u.z == edz&&u.x == edx&&u.y == edy&&u.t <= T)
        {
            return true;
        }
        if (u.t > T) return false;
        for (int i = 0; i < 4; i++)
        {
            int tr = u.x + dr[i];
            int tc = u.y + dc[i];
            if (tr < n&&tr >= 0 && tc < m&&tc >= 0 && mz[u.z][tr][tc] != '*' && !vis[u.z][tr][tc])
            {
                if (mz[u.z][tr][tc] != '#')
                {
                    vis[u.z][tr][tc] = true;
                    q.push(node(u.z, tr, tc, u.t + 1));
                }
                else
                {
                    vis[!u.z][tr][tc] = vis[u.z][tr][tc] = true;
                    if (mz[!u.z][tr][tc] != '*'&&mz[!u.z][tr][tc] != '#')
                    {
                        q.push(node(!u.z, tr, tc, u.t + 1));
                    }
                }
            }
        }

    }
    return false;
}
int main()
{
    int C;
    scanf("%d", &C);
    while (C--)
    {
        scanf("%d%d%d", &n, &m,&T);
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < m; k++)
                {
                    cin >> mz[i][j][k];
                    if (mz[i][j][k] == 'P')
                    {
                        edz = i;
                        edx = j;
                        edy = k;
                    }
                }
            }
        }
        if (BFS()) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}