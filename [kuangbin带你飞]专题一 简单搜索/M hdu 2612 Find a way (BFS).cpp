#include<iostream>
#include<map>
#include<queue>
#include<memory.h>
using namespace std;
char mp[210][210];
map<pair<int, int>, int>kfc;
bool vis[210][210];
const int maxt = 0x7fffffff;
struct node
{
    int r;
    int c;
    int tm;
    node(int rr=0,int cc=0,int tt=0):r(rr),c(cc),tm(tt){ }
};
int Yx, Yy, Mx, My;
int n, m;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
int ans,cntkfc;
void BFS(int inir,int inic)
{
    memset(vis, 0, sizeof(vis));
    cntkfc = kfc.size();
    queue<node>q;
    q.push(node(inir,inic, 0));
    vis[inir][inic] = true;
    pair<int, int>p;
    while (!q.empty())
    {
        node t = q.front();
        p.first = t.r, p.second = t.c;
        q.pop();
        if (kfc[p])
        {
            cntkfc--;
            if (kfc[p] > 11) ans = min(ans, kfc[p] + t.tm - 11);
            kfc[p] += t.tm;
            if (cntkfc == 0)return;
        }
        for (int i = 0; i < 4; i++)
        {
            int tr = t.r + dx[i];
            int tc = t.c + dy[i];
            if (tr >= 0 && tr < n&&tc >= 0 && tc < m)
            {
                if (mp[tr][tc] != '#' && !vis[tr][tc])
                {
                    vis[tr][tc] = true;
                    q.push(node(tr, tc, t.tm + 11));
                }
            }
        }
    }
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        kfc.clear();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> mp[i][j];
                if (mp[i][j] == 'Y') Yx = i, Yy = j;
                if (mp[i][j] == 'M')Mx = i, My = j;
                if (mp[i][j] == '@') kfc[make_pair(i, j)] = 11;
            }
        }
        ans = maxt;
        BFS(Yx, Yy);
        BFS(Mx, My);
        printf("%d\n", ans);
    }
    return 0;
}