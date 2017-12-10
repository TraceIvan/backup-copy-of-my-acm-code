//���⣺��N�����߸ˣ�����P���������ӵĵ��ߣ�����K��������ѣ������1��N��һ��·���������ӵĵ�����ĿС��K������Ϊ0�������ڣ��������ȥK�����ߺ�ʣ��ĵ��߳������ֵ����Сֵ����������·����Ϊ-1.
//˼·�������������ѵ�K���϶�ȡ��Ҫ���ӵĵ��ߴӴ�СǰK������ô���Ƕ��������󳤶�mid���Ѵ��ڸó��ȵĵ��ߵ�Ȩֵ��Ϊ1��С�ڵ��ڸó��ȵĵ��ߵ�Ȩֵ��Ϊ0����һ�δ�1��ʼ�����·����dis[N]��Ϊ����mid���ȵĵ������������������С�ڵ���K��˵������������Ҫ֧��mid�ļ۸񣬽��������ܲ�������Сmid������ֻ������mid�����������·����ֱ�����-1�����midΪ0ʱdis[N]С�ڵ���K�����ֱ�����0.
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