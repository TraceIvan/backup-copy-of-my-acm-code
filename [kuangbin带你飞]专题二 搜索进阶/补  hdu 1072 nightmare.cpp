#include<iostream>
#include<cstdio>
#include<memory.h>
#include<queue>
using namespace std;
int n, m;
const int maxn = 10;
int mp[maxn][maxn];
int stx, sty, edx, edy;
struct node
{
    int r;
    int c;
    int t;
    int cnt;
    node(int rr=0,int cc=0,int tt=0,int ct=0):r(rr),c(cc),t(tt),cnt(ct){ }
};
int ans;
int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1,0,0 };
void BFS()
{
    queue<node>q;
    q.push(node(stx, sty, 6));
    while (!q.empty())
    {
        node u = q.front();
        q.pop();
        if (u.r == edx&&u.c == edy&&u.t > 0)
        {
            ans = u.cnt;
            return;
        }
        if (mp[u.r][u.c] == 4 && u.t > 0) u.t = 6,mp[u.r][u.c]=1;
        if (u.t == 0)continue;
        for (int i = 0; i < 4; i++)
        {
            int tr = u.r + dr[i];
            int tc = u.c + dc[i];
            if (tr < n&&tr >= 0 && tc < m&&tc >= 0)
            {
                if (mp[tr][tc] != 0)
                {
                    q.push(node(tr, tc, u.t - 1, u.cnt + 1));
                }
            }
        }
    }
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                scanf("%d", &mp[i][j]);
                if (mp[i][j] == 2) stx = i, sty = j;
                if (mp[i][j] == 3) edx = i, edy = j;
            }
        }
        ans = -1;
        BFS();
        printf("%d\n", ans);
    }
    return 0;
}