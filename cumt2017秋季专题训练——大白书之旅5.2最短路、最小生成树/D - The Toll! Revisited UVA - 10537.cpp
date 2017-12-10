#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#include<cctype>
#include<cmath>
using namespace std;
const int maxn = 110;
const long long INF = (long long)1<<61;
struct edge
{
    int from, to, next;
    edge(int ff=0,int tt=0,int nn=0):from(ff),to(tt),next(nn){ }
};
vector<edge>Edge;
int Head[maxn], totedge;

struct SPFA
{
    int n, st, ed;
    long long dis[maxn];
    int cnt[maxn];
    int vis[maxn];
    int pre[maxn];

    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
        Edge.clear();
    }
    void set(int nodes, int source, int dest)
    {
        n = nodes, st = source, ed = dest;
    }
    void addedge(int from, int to)
    {
        Edge.push_back(edge(from, to, Head[from]));
        Head[from] = totedge++;
        Edge.push_back(edge(to, from, Head[to]));
        Head[to] = totedge++;
    }
    bool cal_spfa(int desnum)
    {
        memset(vis, 0, sizeof(vis));
        memset(dis, 0x3f, sizeof(dis));
        memset(pre, -1, sizeof(pre));
        memset(cnt, 0, sizeof(cnt));
        queue<int>q;
        q.push(ed);
        vis[ed] = true, dis[ed] = desnum;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = false;
            long long  c;
            if (u >= 26)
            {
                c = (long long)ceil(dis[u]*1.0/19.0);
                //c = (long long)ceil(double(dis[u])*20.0 / 19.0) - dis[u];
            }
            else c = 1;
            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                int v = Edge[i].to;
                if (dis[v] > dis[u] + c)
                {
                    dis[v] = dis[u] + c;
                    pre[v] = u;
                    if (!vis[v])
                    {
                        q.push(v);
                        vis[v] = true;
                        cnt[v]++;
                    }
                }
                else if (dis[v] == dis[u] + c)
                {
                    if (u > pre[v]&&u>=26&&pre[v]<26) pre[v] = u;
                    else if (u < pre[v]&&pre[v]<26) pre[v] = u;
                    else if(u<pre[v]&&u>=26)pre[v] = u;
                }
            }
        }
        return true;
    }
}spfa;
int n, desnum, st, ed;
int main()
{
    char u[4],v[4];
    int Case = 1;
    while (~scanf("%d", &n) && n != -1)
    {
        spfa.Init();
        for (int i = 1; i <= n; i++)
        {
            scanf("%s%s", u, v);
            int ui, vi;
            if (isupper(u[0])) ui = u[0] - 'A' + 26;
            else ui = u[0] - 'a';
            if (isupper(v[0])) vi = v[0] - 'A' + 26;
            else vi = v[0] - 'a';
            spfa.addedge(ui, vi);
        }
        scanf("%d%s%s", &desnum, u, v);
        
        if (isupper(u[0])) st = u[0] - 'A' + 26;
        else st = u[0] - 'a';
        if (isupper(v[0])) ed = v[0] - 'A' + 26;
        else ed = v[0] - 'a';

        spfa.set(60, st, ed);
        spfa.cal_spfa(desnum);
        printf("Case %d:\n", Case++);
        printf("%lld\n", spfa.dis[st]);
        int tmp =st;
        while (true)
        {
            if (tmp == ed)
            {
                printf("%c\n", v[0]);
                break;
            }
            char p;
            if (tmp < 26) p = 'a' + tmp;
            else p = 'A' + (tmp - 26);
            printf("%c-", p);
            tmp = spfa.pre[tmp];
        }
    }
    return 0;
}