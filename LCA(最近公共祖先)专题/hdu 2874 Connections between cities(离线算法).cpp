#include<iostream>
#include<memory.h>
#include<vector>
using namespace std;
int n, m, c;
const int maxn = 10005;
const int maxe = 10005;
const int maxq = 1000005;
//用边表来存各条边，邻接表MLE
int Head[maxn];
struct edge
{
    int to;
    int len;
    int next;
}eg[2*maxe];
//用边表来存每次询问，邻接表MLE
int qhead[maxn];
struct qry
{
    int to;
    int next;
}qy[2*maxq];
int ans[maxq];//存第i个询问的结果
int dis[maxn];//存各棵树下结点到根的距离
int vis[maxn];//是否访问标记，不为0时其值代表结点所在的树编号
int pre[maxn];//并查集
int f[maxn];//存祖先
void Init()
{
    for (int i = 0; i <= n; i++)
    {
        pre[i] = i;
    }
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
void LCA(int rt, int k)
{
    vis[rt] = k;
    f[rt] = rt;
    for (int i = Head[rt]; i!=0; i=eg[i].next)
    {
        int u = eg[i].to;
        if (!vis[u])
        {
            dis[u] = dis[rt] + eg[i].len;
            LCA(u, k);
            Join(u, rt);
            f[Findf(rt)] = rt;
        }
    }
    for (int i = qhead[rt]; i != 0; i = qy[i].next)
    {
        int v = qy[i].to;
        if (vis[v] && vis[v] == vis[rt])
        {
            ans[(i+1) / 2] = dis[rt] + dis[v] - 2 * dis[Findf(v)];
        }
        else ans[(i+1) / 2] = -1;
    }

}
int main()
{
    while (~scanf("%d%d%d", &n, &m, &c))
    {
        Init();
        int cnt = 1;
        for (int i = 1; i <= m; i++)
        {
            int u, v, len;
            scanf("%d%d%d", &u, &v, &len);
            eg[cnt].to = v, eg[cnt].len = len,eg[cnt].next=Head[u],Head[u]=cnt;
            cnt++;
            eg[cnt].to = u, eg[cnt].len = len, eg[cnt].next = Head[v], Head[v] = cnt;
            cnt++;
        }
        cnt = 1;
        for (int i = 1; i <= c; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            qy[cnt].to = v, qy[cnt].next = qhead[u], qhead[u] = cnt;
            cnt++;
            qy[cnt].to = u, qy[cnt].next = qhead[v], qhead[v] = cnt;
            cnt++;//这样保存(cnt+1)/2则为其询问编号
        }
        int k = 1;
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                LCA(i, k);
                k++;
            }
        }
        for (int i = 1; i <= c; i++)
        {
            if (ans[i] == -1) printf("Not connected\n");
            else printf("%d\n", ans[i]);
        }
    }
    return 0;
}