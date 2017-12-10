#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int n, f, d,st,ed;
const int maxn = 450;
const int maxe = 250000;
const int INF = 0x7fffffff;

int mp[maxn][maxn];
int level[maxn];//分层
int vis[maxn];
int flow[maxn];
int prepath[maxn];

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
        for (int i = 1; i <=ed; i++)
        {
            if (i != st && !vis[i] && mp[t][i])
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
    while (~scanf("%d%d%d", &n, &f, &d))
    {
        //建图
        st = 0, ed = 2 * n + f + d + 1;
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= n; i++)
        {
            mp[i][i + n] = 1;//每头牛拆点，左牛到右牛
            int fi, di;
            scanf("%d%d", &fi, &di);
            for (int j = 1; j <= fi; j++)
            {
                int ff;
                scanf("%d", &ff);
                mp[2 * n + ff][i] = 1;//食物到左牛
            }
            for (int j = 1; j <= di; j++)
            {
                int dd;
                scanf("%d", &dd);
                mp[i + n][2 * n + f + dd] = 1;//右牛到饮料
            }
            
        }
        for (int i = 1; i <= f; i++) mp[0][2 * n + i] = 1;//源点到食物
        for (int j = 1; j <= d; j++)mp[2 * n + f + j][2 * n + f + d + 1] = 1;//饮料到汇点

        //Edmonds_Karp算法
        int ans = Edmonds_Karp();

        printf("%d\n", ans);
    }
    return 0;
}