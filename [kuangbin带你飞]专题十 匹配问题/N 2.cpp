#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
int k, c, m,maxdis;
const int maxn = 300;
const int INF = 0x7fffffff;
int M[maxn][maxn];
int mp[maxn][maxn];
int prepath[maxn];
bool vis[maxn];
int flow[maxn];
int st, ed;
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
        for (int i = 1; i <= ed; i++)
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
void Build(int v)
{
    memset(mp, 0, sizeof(mp));
    st = 0, ed = k + c + 1;
    for (int i = 1; i <= k; i++) mp[i][ed] = m;
    for (int i = k + 1; i <= k + c; i++) mp[st][i] = 1;
    for (int i = k + 1; i <= k + c; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (M[i][j] <= v) mp[i][j] = 1;
        }
    }
}
int main()
{
    while (~scanf("%d%d%d", &k, &c, &m))
    {
        maxdis = 0;
        for (int i = 1; i <= k + c; i++)
        {
            for (int j = 1; j <= k + c; j++)
            {
                scanf("%d", &M[i][j]);
                if (i != j&&M[i][j] == 0)M[i][j] = INF;
                if (i != j&&M[i][j] != INF) maxdis = max(maxdis, M[i][j]);
            }
        }
        for (int z = 1; z <= k + c; z++)
        {
            for (int i = 1; i <= k + c; i++)
            {
                for (int j = 1; j <= k + c; j++)
                {
                    if (i == j)continue;
                    if (M[i][z] != INF&&M[z][j] != INF&&M[i][z] + M[z][j] < M[i][j])
                    {
                        M[i][j] = M[i][z] + M[z][j];
                    }
                }
            }
        }
        int l = 0, r = maxdis, ans;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            Build(mid);
            int re = Edmonds_Karp();
            if (re == c)
            {
                ans = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}