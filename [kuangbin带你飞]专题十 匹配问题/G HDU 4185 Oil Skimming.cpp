#include<iostream>
#include<queue>
#include<memory.h>
#include<algorithm>
#include<cmath>
using namespace std;
int n, t, m, Nx, Ny, dis;
const int maxn = 650;//最大行数
const int maxm = 650;//最大列数
const int maxk = 360005;
const int INF = 0x7fffffff;
char M[maxn][maxm];
bool mp[maxn][maxn];//1表示该ij可以匹配
int cx[maxk];//记录x集合中匹配的y元素是哪一个
int dx[maxk];
int cy[maxk];//记录y集合中匹配的x元素是哪一个
int dy[maxk];
int vis[maxk];//标记该顶点是否访问过
struct point
{
    int x;
    int y;
}oils[maxk];
bool searchP(void)    //BFS   
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

int MaxMatch(void)
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
    int C,N;
    scanf("%d", &C);
    int Case = 1;
    while (C--)
    {
        scanf("%d", &N);
        memset(mp, 0, sizeof(mp));
        int cnt = 0;
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                cin >> M[i][j];
                if (M[i][j] == '#')
                {
                    oils[cnt].x = i;
                    oils[cnt].y = j;
                    cnt++;
                }
            }
        }
        for (int i = 0; i < cnt; i++)
        {
            for (int j = 0; j < cnt; j++)
            {
                if (abs(oils[i].x - oils[j].x) + abs(oils[i].y - oils[j].y) == 1)
                {
                    mp[i+1][j+1] = 1;
                }
            }
        }
        Nx = cnt, Ny = cnt;
        int ans = MaxMatch();
        printf("Case %d: %d\n", Case++,ans/2);
    }
    return 0;
}