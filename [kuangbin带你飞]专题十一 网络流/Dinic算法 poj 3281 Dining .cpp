#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int INF = 250000;
/**oo 表示无穷大*/
const int maxe = 250000;
/**mm 表示边的最大数量，记住要是原图的两倍，在加边的时候都是双向的*/
const int maxn = 450;
/**mn 表示点的最大数量*/
int nodes, st, ed, edges;
/**node 表示节点数，src 表示源点，dest 表示汇点，edge 统计边数*/
struct node
{
    int from;
    int to;//边指向的节点
    int next;//链表的下一条边
    int cap;//边的容量
    int flow;//边的流量
}Eg[maxe];

int head[maxn], work[maxn],level[maxn];
/**head 节点的链表头，work 用于算法中的临时链表头，level 计算层次距离*/
bool vis[maxn];

/**初始化链表及图的信息*/
void Init(int _node, int _src, int _dest)
{
    nodes = _node, st = _src, ed = _dest;
    memset(head,-1,sizeof(head));
    edges = 0;
}
/**增加一条u 到v 容量为c 的边*/
void addedge(int u, int v, int c)
{
    Eg[edges].flow=u,Eg[edges].to = v, Eg[edges].cap = c,Eg[edges].flow=0,Eg[edges].next= head[u], head[u] = edges++;
    Eg[edges].from=v,Eg[edges].to = u, Eg[edges].cap = 0,Eg[edges].flow=0,Eg[edges].next = head[v], head[v] = edges++;
}
/**广搜计算出每个点与源点的最短距离，如果不能到达汇点说明算法结束*/
bool Dinic_bfs()
{
    queue<int>q;
    int i, u, v;
    memset(level, -1, sizeof(level));
    memset(vis, 0, sizeof(vis));
    q.push(st);
    level[st] = 0;
    vis[st] = true;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        for (i = head[u]; i !=-1; i = Eg[i].next)
        {
            v = Eg[i].to;
            if (Eg[i].cap>Eg[i].flow &&!vis[v])
            {
                vis[v] = true;
                /**这条边必须有剩余容量*/
                level[v] = level[u] + 1;
                if (v == ed)return true;
                q.push(v);
            }
        }
    }
    return false;
}
/**寻找可行流的增广路算法，按节点的距离来找，加快速度*/
int Dinic_dfs(int u, int maxf)
{
    if (u == ed||maxf==0)return maxf;
    /**work 是临时链表头，这里用i 引用它，这样寻找过的边不再寻找*/
    int flow = 0, f;
    for (int &i = work[u], v; i != -1; i = Eg[i].next)
    {
        v = Eg[i].to;
        if (level[v] == level[u] + 1 && (f = Dinic_dfs(v, min(maxf, Eg[i].cap - Eg[i].flow))) > 0)
        {
            Eg[i].flow += f;
            Eg[i ^ 1].flow -= f;
            /**正反向边容量改变*/
            flow += f;
            maxf -= f;
            if (maxf == 0) break;
        }
    }
    return flow;
}
int Dinic_flow()
{
    int ret = 0;
    while (Dinic_bfs())
    {
        memcpy(work, head, sizeof(head));
        ret += Dinic_dfs(st, INF);
    }
    return ret;
}

int main()
{
    int n, f, d;
    while (~scanf("%d%d%d", &n, &f, &d))
    {
        //建图
        Init(2 * n + f + d + 1, 0, 2 * n + f + d + 1);
        for (int i = 1; i <= n; i++)
        {
            addedge(i,i+n,1);//每头牛拆点，左牛到右牛
            int fi, di;
            scanf("%d%d", &fi, &di);
            for (int j = 1; j <= fi; j++)
            {
                int ff;
                scanf("%d", &ff);
                addedge(2 * n + ff,i,1);//食物到左牛
            }
            for (int j = 1; j <= di; j++)
            {
                int dd;
                scanf("%d", &dd);
                addedge(i + n,2 * n + f + dd,1);//右牛到饮料
            }

        }
        for (int i = 1; i <= f; i++) addedge(0,2 * n + i,1);//源点到食物
        for (int j = 1; j <= d; j++) addedge(2 * n + f + j,2 * n + f + d + 1,1);//饮料到汇点

        int ans = Dinic_flow();

        printf("%d\n", ans);
    }
    return 0;
}