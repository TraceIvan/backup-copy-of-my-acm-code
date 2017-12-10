#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;


const int maxn = 210;
const int maxe = 100 * 100 * 2 + 100 * 4 + 100;
const int INF = 0x3f3f3f3f;
int dindgree[maxn], n;//dindgree[i]存的是i结点入度减去出度的值
vector<int>result;
struct edge
{
    int from, to, cap, flow, next;
    edge(int ff=0,int tt=0,int cc=0,int ww=0,int nn=0):from(ff),to(tt),cap(cc),flow(ww),next(nn){ }
}Edge[maxe];
int Head[maxn], tmp_head[maxn], totedge;
struct dicnic
{
    int n, st, ed;
    int level[maxn];
    bool vis[maxn];

    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
    }
    void set(int nodes, int source, int dest)
    {
        n = nodes, st = source, ed = dest;
    }
    void addedge(int from, int to, int cap)
    {
        Edge[totedge] = edge(from, to, cap, 0, Head[from]);
        Head[from] = totedge++;
        Edge[totedge] = edge(to, from, 0, 0, Head[to]);
        Head[to] = totedge++;
    }
    bool dicnic_bfs()
    {
        memset(level, -1, sizeof(level));
        memset(vis, 0, sizeof(vis));
        queue<int>q;
        q.push(st);
        vis[st] = true;
        level[st] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == ed) return true;
            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                int v = Edge[i].to;
                if (Edge[i].cap > Edge[i].flow && !vis[v])
                {
                    vis[v] = true;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return false;
    }
    int dicnic_dfs(int u, int maxf)
    {
        if (u == ed || maxf == 0) return maxf;

        int flow = 0, f;
        for (int &i = tmp_head[u]; i != -1; i = Edge[i].next)
        {
            int v = Edge[i].to;
            if (Edge[i].cap > Edge[i].flow&&level[v] == level[u] + 1)
            {
                int f = dicnic_dfs(v, min(maxf, Edge[i].cap - Edge[i].flow));
                if (f > 0)
                {
                    Edge[i].flow += f;
                    if(Edge[i].cap>0) dindgree[v] += f;//默认每条边走过一次，流为0.所增加的流表示重复多走过的次数
                    Edge[i ^ 1].flow -= f;
                    flow += f;
                    maxf -= f;
                    if (maxf == 0) break;
                }
            }
        }
        return flow;
    }

    int cal_maxflow()
    {
        int ret = 0;
        while (dicnic_bfs())
        {
            memcpy(tmp_head, Head, sizeof(Head));
            ret += dicnic_dfs(st, INF);
        }
        return ret;
    }
}dnc;



int main()
{
    while (~scanf("%d", &n)&&n)
    {
        dnc.Init();
        dnc.set(n + 2, 0, n + 1);
        memset(dindgree, 0, sizeof(dindgree));
        for (int i = 1; i <= n; i++)
        {
            int k;
            scanf("%d", &k);
            dindgree[i] -= k;
            for (int j = 1; j <= k; j++)
            {
                int to;
                scanf("%d", &to);
                dnc.addedge(i, to, INF);//每条边可以走多次，所以容量为INF
                dindgree[to]++;
            }
        }
        int nowedge = totedge;
        int ans = 0;//ans的值就是正向最大流
        for (int i = 1; i <= n; i++)
        {
            /*逆向建边。原本正向应该是源点连向出度大于入度的点，入度大于出度的点连向汇点。
            逆向则是出度大于入度的点连向汇点，源点连向入度大于出度的点。*/
            if (dindgree[i]<0) dnc.addedge(i,n+1, -dindgree[i]),ans+= - dindgree[i];
            if (dindgree[i] >0) dnc.addedge(0,i, dindgree[i]);
        }
        ans -= dnc.cal_maxflow();//减去逆向最大流
        printf("%d\n", ans);

        
        for (int i = 1; i <= n; i++)
        {
            while (dindgree[i] < 0)
            {//表示还能将点i作为某一条路线的起点（出度大）
                dindgree[i]++;//修改所还能作为起点的次数
                result.clear();//result记录该条路线
                result.push_back(i);
                int u = i;
                while (1)
                {
                    bool ok = false;//表示能否从该点走向其他点
                    for (int i = Head[u]; i != -1; i = Edge[i].next)
                    {
                        ////默认每条边走过一次，流为0.所以如果流为1，表示不能再走这条边。所选择的边应当为正向边，且没有和自设的源点或汇点相连
                        if (Edge[i].flow == -1 || Edge[i].cap == 0 || Edge[i].to == n + 1 || Edge[i].to == 0)continue;
                        
                        ok = true;
                        Edge[i].flow--;
                        u = Edge[i].to;
                        result.push_back(u);
                        break;
                    }
                    if (!ok) break;//不能继续走，退出打印路径
                }
                int sz = result.size();
                for (int i = 0; i < sz; i++)
                {
                    if (i) printf(" ");
                    printf("%d", result[i]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}