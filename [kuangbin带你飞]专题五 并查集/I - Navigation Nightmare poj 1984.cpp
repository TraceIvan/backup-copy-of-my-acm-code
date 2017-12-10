#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int n, m,k;
const int maxn = 40050;
const int maxm = 40050;
const int maxk = 10050;
struct qry
{
    int t;
    int f1;
    int f2;
    int id;
}qrys[maxk];
int ans[maxk];

struct stp
{
    int f1;
    int f2;
    stp(int ff1 = 0, int ff2 = 0) :f1(ff1), f2(ff2)
    {
    }
};
vector<stp>stps;
struct pt
{
    int x;
    int y;
}points[maxn];
bool Cmp1(const qry&a, const qry&b)
{
    return a.t < b.t;
}

int pre[maxn];
int Find(int x)
{
    if (pre[x] == x) return x;
    else
    {
        int fa = pre[x];
        pre[x] = Find(fa);
        return pre[x];
    }
}
bool Union(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx == fy) return true;
    else
    {
        pre[fx] = fy;
        return false;
    }
}
struct node
{
    int to;
    char dir;
    int len;
    node(int tt=0,char c=0,int ll=0):to(tt),dir(c),len(ll){ }
};
vector<node>mp[maxn];
bool vis[maxn];
void DFS(int r)
{

    int sz = mp[r].size();
    for (int i = 0; i < sz; i++)
    {
        int tx = points[r].x, ty = points[r].y;
        int v = mp[r][i].to, length = mp[r][i].len;
        if (vis[v])continue;
        switch (mp[r][i].dir)
        {
        case 'N':tx -= length;
            break;
        case 'E': ty += length;
            break;
        case 'S':tx += length;
            break;
        case 'W':ty -= length;
            break;
        }
        points[v].x = tx, points[v].y = ty;
        vis[v] = true;
        DFS(v);
    }
}

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 0; i <= n; i++) mp[i].clear();
        stps.clear();
        for (int i = 1; i <= m; i++)
        {
            int u, v, l;
            char op[10];
            scanf("%d%d%d%s", &u, &v, &l,op);
            mp[u].push_back(node(v, op[0], l));
            char nc;
            switch (op[0])
            {
            case 'N':
                nc = 'S';
                break;
            case 'S':
                nc = 'N';
                break;
            case 'E':
                nc = 'W';
                break;
            case 'W':
                nc = 'E';
                break;
            }
            mp[v].push_back(node(u, nc, l));
            stps.push_back(stp(u, v));
        }
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i <= n; i++)
        {
            if (mp[i].size())
            {
                points[i].x = 0, points[i].y = 0;
                vis[i] = true;
                DFS(i);
                break;
            }
        }
        scanf("%d", &k);
        for (int i = 0; i < k; i++)
        {
            scanf("%d%d%d",&qrys[i].f1, &qrys[i].f2, &qrys[i].t);
            qrys[i].id = i + 1;
        }
        sort(qrys, qrys + k, Cmp1);

        for (int i = 0; i <= n; i++) pre[i] = i;
        int nowstep = 0;
        for (int i = 0; i < k; i++)
        {
            int t = qrys[i].t;
            for (; nowstep < t; nowstep++)
            {
                int f1 = stps[nowstep].f1;
                int f2 = stps[nowstep].f2;
                Union(f1, f2);
            }
            int x = qrys[i].f1, y = qrys[i].f2;
            int fx = Find(x), fy = Find(y);
            if (fx != fy)
            {
                ans[qrys[i].id] = -1;
            }
            else ans[qrys[i].id] = abs(points[x].x - points[y].x) + abs(points[x].y - points[y].y);
        }
        for (int i = 1; i <= k; i++)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}