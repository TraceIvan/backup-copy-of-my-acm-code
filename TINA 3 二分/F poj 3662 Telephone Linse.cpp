//题意：有N个电线杆，给出P条可以连接的电线，其中K条可以免费，求存在1到N的一条路径，若连接的电线数目小于K条，则为0；若大于，则求其除去K条电线后剩余的电线长度最大值的最小值；若不存在路径，为-1.
//思路：最优情况下免费的K条肯定取需要连接的电线从大到小前K条。那么我们二分这个最大长度mid，把大于该长度的电线的权值记为1，小于等于该长度的电线的权值记为0，求一次从1开始的最短路径，dis[N]即为大于mid长度的电线条数，如果该条数小于等于K，说明我们至多需要支付mid的价格，接下来看能不能再缩小mid；否则，只能增大mid；如果不存在路径，直接输出-1；如果mid为0时dis[N]小于等于K，则可直接输出0.
#include<iostream>
#include<memory.h>
#include<vector>
#include<queue>
using namespace std;
struct node
{
    int to;
    int length;
    int weight;
    node(int t= 0, int l = 0,int wt=0):to(t),length(l),weight(wt){ }
};
vector<vector<node> >m;
int dis[1005];
int path[1005];
bool vis[1005];
int cnt[1005];
int n, p, k;
const int INF = 0x7fffffff;
bool flag = true;
bool SPFA(int src)
{
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++)
    {
        dis[i] = INF;
        path[i] = src;
    }
    queue<int>q;
    q.push(src);
    dis[src] = 0, vis[src] = true;
    cnt[src]++;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        vis[v] = false;
        int sz = m[v].size();
        for (int i = 0; i < sz; i++)
        {
            int u = m[v][i].to;
            if (dis[v] + m[v][i].weight < dis[u])
            {
                dis[u] = dis[v] + m[v][i].weight;
                path[u] = v;
                if (!vis[u])
                {
                    q.push(u);
                    vis[u] = true;
                    cnt[u]++;
                    if (cnt[u] > n) return false;
                }
            }
        }
    }
    return true;
}
void Dij(int src)
{
    memset(dis, -1, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(path, 0, sizeof(path));
    int sz = m[src].size();
    for (int i = 0; i < sz; i++) dis[m[src][i].to] = m[src][i].weight,path[m[src][i].to]=src;
    for (int i = 1; i <= n; i++) if (dis[i] == -1) dis[i] = INF;
    vis[src] = true, dis[src] = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        int u = src, min = INF;
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i] && dis[i] < min) u = i, min = dis[i];
        }
        vis[u] = true;
        sz = m[u].size();
        for (int i = 0; i < sz; i++)
        {
            int v = m[u][i].to;
            if (!vis[v] && dis[u] + m[u][i].weight < dis[v])
            {
                dis[v] = dis[u] + m[u][i].weight;
                path[v] = u;
            }
        }
    }
}
bool Judge(int mid)
{
    for (int i = 1; i <= n; i++)
    {
        int sz = m[i].size();
        for (int j = 0; j < sz; j++)
        {
            if (m[i][j].length > mid) m[i][j].weight = 1;
            else m[i][j].weight = 0;
        }
    }
    //SPFA(1);
    Dij(1);
    if (dis[n] == INF) flag = false;
    if (dis[n] <= k) return true;
    else return false;
}
int main()
{
    while (~scanf("%d%d%d", &n, &p, &k))
    {
        m.clear();
        for (int i = 0; i <= n; i++) m.push_back(vector<node>());
        int L = 0, R = 0;
        for (int i = 1; i <= p; i++)
        {
            int v, u, l;
            scanf("%d%d%d", &v, &u, &l);
            m[v].push_back(node(u, l));
            m[u].push_back(node(v, l));
            if (l > R) R = l;
        }
        flag = true;
        if (Judge(0))
        {
            printf("0\n");
        }
        else if (!flag)
        {
            printf("-1\n");
        }
        else
        {
            while (L <= R)
            {
                int mid = (L + R) / 2;
                if (Judge(mid)) R = mid - 1;
                else L = mid + 1;
            }
            printf("%d\n", L);
        }
    }
    return 0;
}