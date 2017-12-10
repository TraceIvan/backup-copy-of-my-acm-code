#include<iostream>
#include<queue>
#include<map>
#include<string>
using namespace std;
const int INF = 0x3f3f3f3f;
struct node
{
    int from;
    int to;//边指向的节点
    int next;//链表的下一条边
    int cap;//边的容量
    int flow;//边的流量
}Eg[100000];

int head[1000], work[1000], level[1000];
/**head 节点的链表头，work 用于算法中的临时链表头，level 计算层次距离*/
bool vis[15500];
int edges, st, ed,nodes;
int n,m,k;
map<string, int>gid;
int rpt[110];//房间有哪些类型插座
int devices[110];//用电器插头类型
int adp[110][2];//转接器
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
    Eg[edges].from = u, Eg[edges].to = v, Eg[edges].cap = c, Eg[edges].flow = 0, Eg[edges].next = head[u], head[u] = edges++;
    Eg[edges].from = v, Eg[edges].to = u, Eg[edges].cap = 0, Eg[edges].flow = 0, Eg[edges].next = head[v], head[v] = edges++;
}
/**广搜计算出每个点与源点的最短距离，如果不能到达汇点说明算法结束*/
void BuildGraph(int cnt)
{
    //源点为0，房间插座为1~n,用电器为n+1~n+m,转接器为n+m+1~n+m+k,汇点为n+m+k+1.从插座往插头连线
    Init(n+m+k+1, 0,n+m+k+1);
    //源点和插座连接
    for (int i = 1; i <= n; i++) addedge(st, i, 1);
    //用电器到汇点
    for (int i = 1; i <= m; i++) addedge(n+i, ed, 1);
    //插座到用电器（若可以直连）
    for (int i = 1; i <= m; i++)
    {
        if (devices[i] <= n) addedge(devices[i], n + i, 1);
    }
    //插座到转换器插头
    for (int i = 1; i <= k; i++)
    {
        if (adp[i][1] <= n) addedge(adp[i][1], n + m + i, INF);
    }
    //转换器插孔到转换器插头
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (i != j&&adp[i][0] == adp[j][1])
            {
                addedge(n + m + i, n + m + j,INF);
            }
        }
    }
    //转换器插孔到用电器
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (adp[i][0] == devices[j])
            {
                addedge(n + m + i, n + j, INF);
            }
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
            if (Eg[i].cap>Eg[i].flow && !vis[v] && level[v] == -1)
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
        if (Eg[i].cap - Eg[i].flow>0 && level[v] == level[u] + 1)
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
    string s;
    while (~scanf("%d",&n))
    {
        int cnt = 1;
        for (int i = 1; i <= n; i++)
        {
            cin >> s;
            if (!gid[s])
            {
                gid[s] = cnt++;
            }
        }
        n = cnt - 1;
        //房间插座编号1~n
        scanf("%d", &m);
        for (int i = 1; i <= m; i++)
        {
            cin >> s;
            cin >> s;
            if (!gid[s]) gid[s] = cnt++;
            int pos = gid[s];
            devices[i] = pos;
        }//设备编号n+1~n+m
        scanf("%d", &k);
        for (int i = 1; i <= k; i++)
        {
            cin >> s;
            if (!gid[s]) gid[s] = cnt++;
            int ff = gid[s];
            cin >> s;
            if (!gid[s]) gid[s] = cnt++;
            int tt = gid[s];
            adp[i][0] = ff;
            adp[i][1] = tt;
        }
        BuildGraph(cnt);
        printf("%d\n", m-Dinic_flow());
    }
    return 0;
}