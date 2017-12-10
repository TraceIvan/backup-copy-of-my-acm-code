#include<iostream>
#include<memory.h>
#include<queue>
using namespace std;
int p, n,st,ed;
const int maxn = 55;
const int maxp = 15;
const int maxe = 10000;
const int INF = 0x7fffffff;

struct line
{
    int u;
    int v;
    int f;
}lines[maxe];

int in[maxn][maxp];//记录每台机器的输入要求
int out[maxn][maxp];//记录每台机器的输出情况
int k[maxn];//记录每台机器的最大组装效率

int mp[maxn * 2][maxn * 2];//网络图
int mptmp[maxn * 2][maxn * 2];//初始图备份

int prepath[maxn * 2];
int flow[maxn * 2];
bool vis[maxn * 2];
int BFS()
{
    queue<int>q;
    memset(prepath, 0, sizeof(prepath));
    memset(vis, 0, sizeof(vis));
    prepath[st] = st;
    flow[st] = INF;
    q.push(st);
    vis[st] = true;
    while (!q.empty())
    {//可以用优先队列优化
        int t = q.front();
        q.pop();
        if (t == ed)break;
        for (int i = 1; i <= n*2+1; i++)
        {
            if (i != st&&!vis[i]&& mp[t][i])
            {
                vis[i] = true;//防止走反向
                flow[i] = flow[t] < mp[t][i] ? flow[t] : mp[t][i];
                q.push(i);
                prepath[i] = t;
            }
        }
    }
    if (prepath[ed] == 0) return -1;
    else return flow[ed];
}

int Edmonds_Karp()
{
    int maxflow = 0, dflow, cur, pre;
    while (1)
    {
        dflow = BFS();
        if (dflow == -1)break;
        maxflow += dflow;
        cur = ed;
        while (cur != st)
        {
            pre = prepath[cur];
            mp[pre][cur] -= dflow;//更新正向边
            mp[cur][pre] += dflow;//添加反向边
            cur = pre;
        }
    }
    return maxflow;
}

int main()
{
    while (~scanf("%d%d", &p, &n))
    {
        memset(mp, 0, sizeof(mp));
        st = 0, ed = 2 * n + 1;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &k[i]);
            for (int j = 1; j <= p; j++)
            {
                scanf("%d", &in[i][j]);
            }
            for (int j = 1; j <= p; j++)
            {
                scanf("%d", &out[i][j]);
            }
            mp[i][i + n] = k[i];
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j) continue;
                bool flag = true;
                for (int k = 1; k <= p; k++)
                {
                    if (out[i][k] + in[j][k] == 1)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag) mp[i + n][j] = INF;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            bool flag = true;
            for (int j = 1; j <= p; j++)
            {
                if (in[i][j] == 1)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)mp[st][i] = INF;
        }
        for (int i = 1; i <= n; i++)
        {
            bool flag = true;
            for (int j = 1; j <= p; j++)
            {
                if (out[i][j] == 0)
                {
                    flag = false;
                    break;
                }
            }
            if (flag) mp[i + n][ed] = INF;
        }
        memcpy(mptmp, mp, sizeof(mp));
        int ans = Edmonds_Karp();
        int totaline = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (mptmp[i + n][j] > mp[i + n][j])
                {
                    lines[totaline].u = i;
                    lines[totaline].v = j;
                    lines[totaline].f = mptmp[i + n][j] - mp[i + n][j];
                    totaline++;
                }
            }
        }
        printf("%d %d\n", ans, totaline);
        for (int i = 0; i < totaline; i++)
        {
            printf("%d %d %d\n", lines[i].u, lines[i].v, lines[i].f);
        }
    }
    return 0;
}