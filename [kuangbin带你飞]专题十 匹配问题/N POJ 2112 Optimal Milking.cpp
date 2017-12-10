//网络流二分图多重匹配
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

int k, c, m;


const int INF = 0x3f3f3f3f;
/**oo 表示无穷大*/
const int maxe = 200000;
/**mm 表示边的最大数量，记住要是原图的两倍，在加边的时候都是双向的*/
const int maxn = 300;
/**mn 表示点的最大数量*/
int nodes, st, ed, edges;
/**node 表示节点数，src 表示源点，dest 表示汇点，edge 统计边数*/
int mp[500][500];
struct node
{
    int from;
    int to;//边指向的节点
    int next;//链表的下一条边
    int cap;//边的容量
    int flow;//边的流量
}Eg[1000000];

int head[15500], work[15500], level[15500];
/**head 节点的链表头，work 用于算法中的临时链表头，level 计算层次距离*/
bool vis[15500];

/**初始化链表及图的信息*/
void Init(int _node, int _src, int _dest)
{
    nodes = _node, st = _src, ed = _dest;
    memset(head, -1, sizeof(head));
    edges = 0;
}
/**增加一条u 到v 容量为c 的边*/
void addedge(int u, int v, int c)
{
    Eg[edges].flow = u, Eg[edges].to = v, Eg[edges].cap = c, Eg[edges].flow = 0, Eg[edges].next = head[u], head[u] = edges++;
    Eg[edges].from = v, Eg[edges].to = u, Eg[edges].cap = 0, Eg[edges].flow = 0, Eg[edges].next = head[v], head[v] = edges++;
}
/**广搜计算出每个点与源点的最短距离，如果不能到达汇点说明算法结束*/
void BuildGraph(int mid)
{
    Init(k+c+2, 0, k + c + 1);
    for (int i = 1; i <= k; i++) addedge(i, ed, m);
    for (int i = k + 1; i <=k+c; i++) addedge(st,i, 1);
    for (int i =k+1; i <= k+c; i++)
    {
        for (int j = 1; j <=k; j++)
        {
            if(mp[i][j]<=mid)addedge(i,j, 1);
        }
    }
}
bool Dinic_bfs()
{
    queue<int>q;
    int i, u, v;
    memset(level, -1, sizeof(level));
    memset(vis, 0, sizeof(vis));
    q.push(st);
    level[st] = 0;
    vis[st] = true;
    while (!q.empty())
    {
        u = q.front();
        if (u == ed) return true;
        q.pop();
        for (i = head[u]; i != -1; i = Eg[i].next)
        {
            v = Eg[i].to;
            if (Eg[i].cap>Eg[i].flow && !vis[v]&&level[v]==-1)
            {
                vis[v] = true;
                /**这条边必须有剩余容量*/
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return false;
}
/**寻找可行流的增广路算法，按节点的距离来找，加快速度*/
int Dinic_dfs(int u, int maxf)
{
    if (u == ed)return maxf;
    /**work 是临时链表头，这里用i 引用它，这样寻找过的边不再寻找*/
    int flow = 0, f;
    for (int &i = work[u], v; i != -1; i = Eg[i].next)
    {
        v = Eg[i].to;
        if (Eg[i].cap - Eg[i].flow>0&&level[v] == level[u] + 1)
        {
            f = Dinic_dfs(v, min(maxf, Eg[i].cap - Eg[i].flow));
            Eg[i].flow += f;
            Eg[i ^ 1].flow -= f;
            /**正反向边容量改变*/
            flow += f;
            if (flow == maxf) return flow;
        }
    }
    return flow;
}
int Dinic_flow()
{
    int l = 0, r = 10000, ans, ret;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        ret = 0;
        BuildGraph(mid);
        while (Dinic_bfs())
        {
            memcpy(work, head, sizeof(head));
            ret += Dinic_dfs(st, INF);
        }
        if (ret == c)
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return ans;
}
int main()
{
    while (~scanf("%d%d%d", &k, &c, &m))
    {
        for (int i = 1; i <= k + c; i++)
        {
            for (int j = 1; j <= k + c; j++)
            {
                scanf("%d", &mp[i][j]);
                if (i!=j&&mp[i][j] == 0) mp[i][j] = INF;
            }
        }
        for (int z = 1; z <= k + c; z++)
        {
            for (int i = 1; i <= k + c; i++)
            {
                for (int j = 1; j <= k + c; j++)
                {
                    mp[i][j] = min(mp[i][j], mp[i][z] + mp[z][j]);
                }
            }
        }
        int ans = Dinic_flow();
        printf("%d\n", ans);
    }

    return 0;
}