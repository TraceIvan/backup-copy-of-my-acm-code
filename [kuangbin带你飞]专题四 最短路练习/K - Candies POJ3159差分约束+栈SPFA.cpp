#include<iostream>
using namespace std;
int n, m;
const int maxn = 30100;
const int INF = 0x7ffffff;
struct eg
{
    int to,next;
    int v;
}Edge[150100];
int head[maxn];

bool vis[maxn];
int cnt[maxn];
int dis[maxn];

int stk[maxn], top;//模拟栈
bool SPFA(int root)
{
    for (int i = 0; i <= n; i++) dis[i] = INF;
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    dis[root] = 0, vis[root] = true, cnt[root]++;
    top = 0;
    stk[top++] = root;
    while (top)
    {
        int u = stk[--top];
        vis[u] = false;
        for (int i = head[u]; i!=-1; i=Edge[i].next)
        {
            int v = Edge[i].to;
            int vv = Edge[i].v;
            if (dis[u] + vv < dis[v])
            {
                dis[v] = dis[u] + vv;
                if (!vis[v])
                {
                    vis[v] = true;
                    cnt[v]++;
                    stk[top++] = v;
                    if (cnt[v] > n)return false;
                }
            }
        }
    }
    return true;
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        memset(head, -1, sizeof(head));
        for (int i = 0; i < m; i++)
        {
            int u, v, f;
            scanf("%d%d%d", &u, &v, &f);
            //v不能比u超过f个糖果：v-u<=f
            Edge[i].to =v, Edge[i].v = f,Edge[i].next=head[u];
            head[u] = i;
        }
        SPFA(1);//求v(n)-v(1)<=?
        printf("%d\n", dis[n]);
    }
    return 0;
}