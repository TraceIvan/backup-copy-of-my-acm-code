#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
#include<queue>
#include<memory.h>
using namespace std;
int n,totalnum,rows,cols;
const int maxn = 210;
const int maxnum = 210;
int pre[maxnum];
char mp[maxn][maxn];
bool vis[maxn][maxn];
int id[maxn][maxn];
struct side
{
    int v1;
    int v2;
    int len;
    side(int vv1 = 0, int vv2 = 0, int ll = 0) :v1(vv1), v2(vv2), len(ll)
    {
    }
    friend bool operator <(const side&a, const side&b)
    {
        return a.len > b.len;
    }
};
vector<side>minHeap;
struct node
{
    int x;
    int y;
    int stps;
    node(int xx = 0, int yy = 0,int stp=0) :x(xx), y(yy),stps(stp)
    {
    }
};
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
int Find(int x)
{
    int r = x;
    while (r != pre[r])
    {
        r = pre[r];
    }
    int c = x, p;
    while (c != r)
    {
        p = pre[c];
        pre[c] = r;
        c = p;
    }
    return r;
}
bool Join(int x, int y)
{
    int f1 = Find(x), f2 = Find(y);
    if (f1 != f2)
    {
        pre[f1] = f2;
        return false;
    }
    else return true;
}
void BFS(int rx,int ry)
{
    memset(vis, 0, sizeof(vis));
    queue<node>q;
    q.push(node(rx, ry, 0));
    vis[rx][ry] = true;
    while (!q.empty())
    {
        node u = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int tx = u.x + dx[i];
            int ty = u.y + dy[i];
            if (tx >= 0 && tx < rows&&ty >= 0 && ty < cols)
            {
                if (mp[tx][ty] != '#' && !vis[tx][ty])
                {
                    q.push(node(tx, ty, u.stps + 1));
                    vis[tx][ty] = true;
                    if (mp[tx][ty] == 'A' || mp[tx][ty] == 'S')
                    {
                        minHeap.push_back(side(id[rx][ry], id[tx][ty], u.stps + 1));
                    }
                }
            }
        }
    }
}
int Kruskal(int cnt0)
{
    side tmp;
    int ans = 0;
    int cnt = cnt0;

    while (cnt < totalnum)
    {
        pop_heap(minHeap.begin(), minHeap.end());
        tmp = minHeap.back();
        minHeap.pop_back();
        int u = Find(tmp.v1);
        int v = Find(tmp.v2);
        if (u != v)
        {
            Join(tmp.v1, tmp.v2);
            ans += tmp.len;
            cnt++;
        }
    }
    return ans;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &cols, &rows);
        minHeap.clear();
        memset(id, 0, sizeof(id));
        int idorder = 1;
        while ((cin.get()) == ' ');
        for (int i = 0; i<rows; i++)
        {
            for (int j = 0; j <cols; j++)
            {
                scanf("%c",&mp[i][j]);
                if (mp[i][j] == 'S' || mp[i][j] == 'A')
                {
                    id[i][j] = idorder++;
                }
            }
            cin.get();
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (id[i][j])
                {
                    BFS(i, j);
                }
            }
        }
        for (int i = 0; i <= idorder; i++) pre[i] = i;
        int cnt = 1;
        totalnum = idorder - 1;
        make_heap(minHeap.begin(), minHeap.end());
        int ans = Kruskal(cnt);
        printf("%d\n", ans);
    }
    return 0;
}