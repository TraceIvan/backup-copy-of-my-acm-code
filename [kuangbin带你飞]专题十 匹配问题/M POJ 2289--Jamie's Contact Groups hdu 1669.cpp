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

int n, m;
vector<int>pp[1010];

const int INF = 250000;
/**oo 表示无穷大*/
const int maxe = 1000010;
/**mm 表示边的最大数量，记住要是原图的两倍，在加边的时候都是双向的*/
const int maxn = 1600;
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

int head[maxn], work[maxn], level[maxn];
/**head 节点的链表头，work 用于算法中的临时链表头，level 计算层次距离*/
bool vis[maxn];

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
    Init(n + m + 2, 0, n + m + 1);
    for (int i = 1; i <= n; i++) addedge(st, i, 1);
    for (int i = n + 1; i <= n + m; i++) addedge(i, ed, mid);
    for (int i = 1; i <= n; i++)
    {
        int sz = pp[i].size();
        for (int j = 0; j < sz; j++)
        {
            addedge(i, pp[i][j], 1);
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
        q.pop();
        for (i = head[u]; i != -1; i = Eg[i].next)
        {
            v = Eg[i].to;
            if (Eg[i].cap>Eg[i].flow && !vis[v])
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
    if (u == ed || maxf == 0)return maxf;
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
    int l = 0, r = 1010,ans,ret;
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
        if (ret == n)
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
    char name[20];
    string s;
    while (~scanf("%d%d", &n, &m))
    {
        if (n == 0 && m == 0)break;
        for (int i = 1; i <= n; i++) pp[i].clear();
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", name);
            getline(cin, s);
            stringstream sin(s);
            int x;
            while (sin >> x)
            {
                pp[i].push_back(x + 1 + n);
            }
        }
        int ans = Dinic_flow();
        printf("%d\n", ans);
    }
    return 0;
}