#include<iostream>
#include<memory.h>
#include<vector>
#include<map>
#include<string>
using namespace std;
int n, m, c;
map<string, int>mp;
const int maxn = 100005;
const int maxe = 100005;
const int maxq = 100005;
int in[maxn];
//用边表来存各条边
int Head[maxn];
struct edge
{
    int to;
    int len;
    int next;
}eg[maxe];
//用边表来存每次询问
int qhead[maxn];
struct qry
{
    int to;
    int next;
}qy[2 * maxq];
int ans[maxq];//存第i个询问的结果
int dis[maxn];//存结点到根的距离
int vis[maxn];//是否访问标记
int pre[maxn];//并查集
int f[maxn];//存祖先
void Init()
{
    for (int i = 0; i <= n; i++)
    {
        pre[i] = i;
    }
    mp.clear();
    memset(in, 0, sizeof(in));
    memset(qhead, 0, sizeof(qhead));
    memset(qy, 0, sizeof(qy));
    memset(eg, 0, sizeof(eg));
    memset(Head, 0, sizeof(Head));
    memset(ans, 0, sizeof(ans));
    memset(dis, 0, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(f, 0, sizeof(f));
}
int Findf(int x)
{
    int r = x;
    while (r != pre[r])
    {
        r = pre[r];
    }
    int i = x, j;
    while (i != r)
    {
        j = pre[i];
        pre[i] = r;
        i = j;
    }
    return r;
}
void Join(int x, int y)
{
    int rx = Findf(x), ry = Findf(y);
    if (rx != ry) pre[x] = y;
}
void LCA(int rt)
{
    vis[rt] = 1;
    f[rt] = rt;
    for (int i = Head[rt]; i != 0; i = eg[i].next)
    {
        int u = eg[i].to;
        if (!vis[u])
        {
            dis[u] = dis[rt] + eg[i].len;
            LCA(u);
            Join(u, rt);
            f[Findf(rt)] = rt;
        }
    }
    for (int i = qhead[rt]; i != 0; i = qy[i].next)
    {
        int v = qy[i].to;
        if (vis[v])
        {
            int rf = Findf(v);
            if(i%2==1)ans[(i+1)/2] = dis[rt] - dis[rf] + (v== rf ? 0 : 1);
            else ans[(i+1)/2] = dis[v] - dis[rf] + (rt == rf ? 0 : 1);
        }
    }

}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        Init();
        string a, b;
        int k = 0;
        for (int i = 1; i <= n-1; i++)
        {
            int u, v;
            cin >> a >> b;
            if (!mp[a]) mp[a] = ++k;
            if (!mp[b]) mp[b] = ++k;
            u = mp[b], v = mp[a];//从b到a
            in[v]++;
            eg[i].to = v, eg[i].len = 1, eg[i].next = Head[u], Head[u] = i;
        }
        int cnt = 1;
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            cin >> a >> b;
            u = mp[a], v = mp[b];//从a到b
            qy[cnt].to = v, qy[cnt].next = qhead[u], qhead[u] = cnt;//奇数从a到b
            cnt++;
            qy[cnt].to = u, qy[cnt].next = qhead[v], qhead[v] = cnt;//偶数从b到a
            cnt++;

        }
        for (int i = 1; i <= k; i++)
        {
            if (!in[i])
            {
                LCA(i);
                break;
            }
        }
        for (int i = 1; i <=m; i++)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}