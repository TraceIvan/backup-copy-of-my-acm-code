#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn = 10000 + 100;
const int INF = 0x3f3f3f3f;
int R, C, c1, r1, c2, r2,st,ed;
struct edge
{
    int  cost, next;
    int fromid, toid;
    int dir;
    edge(int dd=0,int ffi=0,int tti=0,int cc=0,int nn=0):dir(dd),fromid(ffi),toid(tti),cost(cc),next(nn){ }
};
vector<edge>Edge;
int Head[maxn], totedge;
struct node
{
    int id;
    int fromdir;//来的方向0:起点；1：向上；2：向下；3：向左；4：向右
    int isdouble;//来时是否有制动或加速
    int cost;//来时路的花费
    int tcost;//到达id的总花费
    node(int ii=0,int ff=0,int is=0,int tt=0,int cc=0):id(ii),fromdir(ff),isdouble(is),tcost(tt),cost(cc)
    { }
    friend bool operator<(const node&a, const node&b)
    {
        return a.tcost > b.tcost;
    }
};
struct SPFA
{
    int n, st,ed;
    int dis[maxn][5][2];
    int vis[maxn][5][2];
    int ans;
    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
        Edge.clear();
    }
    void set(int nodes, int source,int dest)
    {
        n = nodes, st = source,ed=dest;
        ans = INF;
    }
    void addedge(int dir,int fromid,int toid, int cap)
    {
        Edge.push_back(edge(dir,fromid,toid, cap, Head[fromid]));
        Head[fromid] = totedge++;
        Edge.push_back(edge(dir-1,toid,fromid, cap, Head[toid]));
        Head[toid] = totedge++;
    }
    bool cal_spfa()
    {
        memset(dis, INF, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        priority_queue<node>q;
        dis[st][0][0] = dis[st][0][1]= 0;
        q.push(node(st,0,0,0,0));
        node u;
        while (!q.empty())
        {
            u = q.top();
            q.pop();
            if (u.id == ed)
            {
                int tmp;
                if (u.isdouble) tmp = u.tcost;
                else tmp = u.tcost + u.cost;
                ans = min(ans, tmp);
            }
            if (vis[u.id][u.fromdir][u.isdouble])continue;
            vis[u.id][u.fromdir][u.isdouble] = true;
            for (int i = Head[u.id]; i != -1; i = Edge[i].next)
            {
                int tmp = dis[u.id][u.fromdir][u.isdouble]+Edge[i].cost;
                int isdb = 0;
                if (!u.isdouble&&u.fromdir != Edge[i].dir) tmp += u.cost;
                if (Edge[i].dir != u.fromdir) tmp += Edge[i].cost, isdb = 1;
                if (dis[Edge[i].toid][Edge[i].dir][isdb] > tmp)
                {
                    dis[Edge[i].toid][Edge[i].dir][isdb] = tmp;
                    q.push(node(Edge[i].toid, Edge[i].dir, isdb, tmp, Edge[i].cost));
                }
            }
        }
        return true;
    }
}spfa;
int main()
{
    int Case = 1;
    while (~scanf("%d%d%d%d%d%d", &R, &C, &r1, &c1, &r2, &c2))
    {
        if (R == 0 && C == 0 && c1 == 0 && r1 == 0 && c2 == 0 && r2 == 0) break;
        spfa.Init();
        st = (r1 - 1)*C + c1, ed = (r2 - 1)*C + c2;
        for (int r = 1; r <= R; r++)
        {
            for (int to = 2; to <= C; to++)
            {
                int cost;
                scanf("%d", &cost);
                if (cost != 0) spfa.addedge(4,(r - 1)*C + to - 1,(r - 1)*C + to, cost);
            }
            if (r == R) continue;
            for (int to = 1; to <= C; to++)
            {
                int cost;
                scanf("%d", &cost);
                if (cost != 0) spfa.addedge(2,(r - 1)*C + to, r*C + to,cost);
            }
        }
        spfa.set(R*C, st, ed);
        spfa.cal_spfa();
        if (spfa.ans == INF) printf("Case %d: Impossible\n",Case++);
        else printf("Case %d: %d\n", Case++, spfa.ans);
    }
    return 0;
}