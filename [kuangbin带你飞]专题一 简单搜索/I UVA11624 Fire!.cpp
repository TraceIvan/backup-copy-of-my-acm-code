#include<iostream>
#include<memory.h>
#include<queue>
using namespace std;
const int INF = 0x7fffffff;
const int maxn = 1005;
int firetime[maxn][maxn];
char mp[maxn][maxn];
int xj, yj;
int n, m;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
struct point
{
    int r;
    int c;
    int t;
    point(int rr=0,int cc=0,int tt=0):r(rr),c(cc),t(tt){ }
};
bool vis[maxn][maxn];
void BFSf()
{
    queue<point>q;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mp[i][j] == 'F') q.push(point(i, j, 0)),vis[i][j]=true;
        }
    }
    while (!q.empty())
    {
        point t = q.front();
        q.pop();
        firetime[t.r][t.c] = t.t;
        for (int i = 0; i < 4; i++)
        {
            int dr = t.r + dx[i];
            int dc = t.c + dy[i];
            if (dr < n&&dr >= 0 && dc < m&&dc >= 0)
            {
                if (mp[dr][dc] != '#'&&!vis[dr][dc])
                {
                    vis[dr][dc] = true;
                    q.push(point(dr, dc, t.t + 1));
                }
            }
        }
    }
}
int ans = INF;

void BFSj()
{
    queue<point>q;
    q.push(point(xj, yj, 0));
    vis[xj][yj] = true;
    while (!q.empty())
    {
        point t = q.front();
        q.pop();
        if (t.r == n - 1 || t.r == 0 || t.c == m - 1 || t.c == 0)
        {
            ans = t.t;
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int dr = t.r + dx[i];
            int dc = t.c + dy[i];
            if (dr <= n - 1 && dr >= 0 && dc <= m - 1 && dc >= 0)
            {
                if (mp[dr][dc] != '#' && !vis[dr][dc] && t.t + 1 < firetime[dr][dc])
                {
                    vis[dr][dc] = true;
                    q.push(point(dr, dc, t.t + 1));
                }
            }
        }
    }
    ans = INF;
}
int main()
{
    //std::ios::sync_with_stdio(false);
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> mp[i][j];
                if (mp[i][j] == 'J') xj = i, yj = j;
                firetime[i][j] = INF;
            }
        }
        memset(vis, 0, sizeof(vis));
        BFSf();
        memset(vis, 0, sizeof(vis));
        ans = INF;
        BFSj();
        if (ans == INF)
        {
            printf("IMPOSSIBLE\n");
        }
        else
        {
            printf("%d\n", ans+1);
        }
    }
    return 0;
}