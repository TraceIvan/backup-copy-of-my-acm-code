#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
const int maxn = 60;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, next;
    double cost;
    edge(int ff=0,int tt=0,int cc=0,int nn=0):from(ff),to(tt),cost(cc),next(nn){ }
};
vector<edge>Edge;
int Head[maxn], totedge;
int N, M;


struct SPFA
{
    int n, st;
    bool vis[maxn];
    double dis[maxn];
    int cnt[maxn];
    bool visn[maxn];
    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
        Edge.clear();
    }
    void set(int nodes, int source)
    {
        n = nodes, st = source;
    }
    void addedge(int from, int to, double cap)
    {
        Edge.push_back(edge(from, to, cap, Head[from]));
        Head[from] = totedge++;
    }
    bool cal_spfa()
    {
        memset(vis, 0, sizeof(vis));
        memset(dis, INF, sizeof(dis));
        memset(cnt, 0, sizeof(cnt));

        queue<int>q;
        q.push(st);
        vis[st] = true;
        cnt[st]++;
        dis[st] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            visn[u] = true;
            vis[u] = false;
            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                int v = Edge[i].to;
                if (dis[v] > dis[u] + Edge[i].cost)
                {
                    dis[v] = dis[u] + Edge[i].cost;
                    if (!vis[v])
                    {
                        vis[v] = true;
                        q.push(v);
                        cnt[v]++;
                        if (cnt[v] > n) return false;
                    }
                }
            }
        }
        return true;
    }
    bool binsolve(double mid)
    {
        for (int i = 0; i < totedge; i++) Edge[i].cost -= mid;
        memset(visn, 0, sizeof(visn));
        bool isok = true;
        for (int i = 1; i <= N; i++)
        {
            if (!visn[i])
            {
                set(N, i);
                isok = cal_spfa();
                if (!isok) break;
            }
        }
        for (int i = 0; i < totedge; i++) Edge[i].cost += mid;
        return isok;
    }
}spfa;

int main()
{
    int t;
    scanf("%d", &t);
    int Case = 1;
    while (t--)
    {
        double L=INF, R=0;
        scanf("%d%d", &N, &M);
        spfa.Init();
        for (int i = 1; i <= M; i++)
        {
            int from, to;
            double cost;
            scanf("%d%d%lf", &from, &to, &cost);
            spfa.addedge(from, to, cost);
            L = min(L, cost);
            R = max(R, cost);
        }
        if (spfa.binsolve(R+1000))
        {
            printf("Case #%d: No cycle found.\n", Case++);
            continue;
        }
        while (R - L > 1e-6)
        {
            double mid = (R + L) / 2;
            if (!spfa.binsolve(mid)) R = mid;
            else L = mid;
        }
        printf("Case #%d: %.2lf\n", Case++, L);
    }
    return 0;
}