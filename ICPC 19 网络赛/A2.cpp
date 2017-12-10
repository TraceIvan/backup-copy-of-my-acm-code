#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n, m;
int Nx, Ny, dis;
const int maxn = 1100;//最大行数
const int maxm = 1100;//最大列数
const int maxk = 1100;
const int INF = 0x7fffffff;
bool mp[maxn][maxm];//1表示该ij可以匹配
int cx[maxm];//记录x集合中匹配的y元素是哪一个
int dx[maxm];
int cy[maxn];//记录y集合中匹配的x元素是哪一个
int dy[maxn];
int vis[maxm];//标记该顶点是否访问过
bool searchP()    //BFS   
{
    queue <int> Q;
    dis = INF;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for (int i = 1; i <= Nx; i++)
        if (cx[i] == -1)
        {
            Q.push(i); dx[i] = 0;
        }
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        if (dx[u] > dis) break;        //说明该增广路径长度大于dis还没有结束，等待下一次BFS在扩充  
        for (int v = 1; v <= Ny; v++)
            if (mp[u][v] && dy[v] == -1)
            {        //v是未匹配点  
                dy[v] = dx[u] + 1;
                if (cy[v] == -1) dis = dy[v];    //得到本次BFS的最大遍历层次  
                else
                {
                    dx[cy[v]] = dy[v] + 1;         //v是匹配点，继续延伸  
                    Q.push(cy[v]);
                }
            }
    }
    return dis != INF;
}

bool DFS(int u)
{
    for (int v = 1; v <= Ny; v++)
        if (!vis[v] && mp[u][v] && dy[v] == dx[u] + 1)
        {
            vis[v] = 1;
            if (cy[v] != -1 && dy[v] == dis) continue;   //层次（也就是增广路径的长度）大于本次查找的dis，是searchP被break的情况，也就是还不确定是否是增广路径，只有等再次调用searchP()在判断。  
            if (cy[v] == -1 || DFS(cy[v]))
            {     //是增广路径，更新匹配集  
                cy[v] = u; cx[u] = v;
                return 1;
            }
        }
    return 0;
}

int MaxMatch()
{
    int res = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    while (searchP())
    {
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= Nx; i++)
            if (cx[i] == -1 && DFS(i)) res++;   //查找到一个增广路径，匹配数res++  
    }
    return res;
}
int main()
{
    //freopen("in.txt", "r", stdin);
    while (~scanf("%d%d", &n, &m))
    {
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            mp[u][v] = mp[v][u] = 1;
        }
        Nx = n, Ny = n;
        printf("%d\n", MaxMatch() / 2);
        for (int i = 0; i <= n; i++)
        {
            if (cx[i] == -1) continue;
            else printf("%d\n", i);
        }

    }
    return 0;
}