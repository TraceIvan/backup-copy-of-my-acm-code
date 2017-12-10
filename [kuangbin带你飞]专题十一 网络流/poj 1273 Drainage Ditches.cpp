#include<iostream>
#include<queue>
using namespace std;
const int maxn = 210;
const int maxm = 210;
const int INF = 0x7fffffff;
int n, m;//点、边
int st, ed;//源点、汇点
int mp[maxn][maxn];//初始网络
int prepath[maxn];//记录每次增广路径的前驱
int flow[maxn];//记录每次BFS求增广路径时的流量
int BFS()
{
    queue<int>q;
    memset(prepath, 0, sizeof(prepath));
    prepath[st] = st;
    flow[st] = INF;
    q.push(st);
    while (!q.empty())
    {//可以用优先队列优化
        int t = q.front();
        q.pop();
        if (t == ed)break;
        for (int i = 1; i <= n; i++)
        {
            if (i != st&&prepath[i] == 0 && mp[t][i])
            {
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
    while (~scanf("%d%d", &m, &n))
    {
        memset(mp, 0, sizeof(mp));
        st = 1, ed = n;
        for (int i = 0; i < m; i++)
        {
            int from, to, cap;
            scanf("%d%d%d", &from, &to, &cap);
            mp[from][to] += cap;
        }
        int maxflow = Edmonds_Karp();
        printf("%d\n", maxflow);
    }
    return 0;
}