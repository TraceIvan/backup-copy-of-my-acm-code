#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
const int maxn = 510;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cost, next;
    edge(int ff=0,int tt=0,int cc=0,int nn=0):from(ff),to(tt),cost(cc),next(nn){ }
};
vector<edge>Edge;
int Head[maxn], totedge;
struct SPFA
{
    int n, st, ed;
    int cnt[maxn];
    bool vis[maxn];
    int dis[maxn];

    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
        Edge.clear();
    }
    void addedge(int from, int to, int cost)
    {
        Edge.push_back(edge(from, to, cost, Head[from]));
        Head[from] = totedge++;
    }
    bool cal_spfa(int mid)
    {
        memset(cnt, 0, sizeof(cnt));
        queue<int>q;
        for (int i = 1; i <= n; i++) q.push(i), dis[i] = 0, vis[i] = true,cnt[i]=1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                int v = Edge[i].to;
                if (dis[v] > dis[u] + Edge[i].cost - mid)
                {
                    dis[v] = dis[u] + Edge[i].cost - mid;
                    if (!vis[v])
                    {
                        vis[v] = true;
                        q.push(v);
                        cnt[v]++;
                        if (cnt[v] >= n) return false;
                    }
                }
            }
        }
        return true;
    }
}spfa;
int main()
{
    int N,E;
    while (~scanf("%d%d", &N, &E))
    {
        spfa.Init();
        int l=1, r = -1;
        for (int i = 1; i <= E; i++)
        {
            int from, to, cost;
            scanf("%d%d%d", &from, &to, &cost);
            spfa.addedge(from, to, cost);
            r = max(r, cost);
        }
        spfa.n = N;
        if (spfa.cal_spfa(r))
        {
            printf("Infinite\n");
        }
        else if (!spfa.cal_spfa(1))
        {
            printf("No Solution\n");
        }
        else
        {
            while (l <= r)
            {
                int mid = (l + r) / 2;
                if (spfa.cal_spfa(mid)) l = mid+1;
                else r = mid - 1;
            }
            printf("%d\n", r);
        }
    }



    return 0;
}