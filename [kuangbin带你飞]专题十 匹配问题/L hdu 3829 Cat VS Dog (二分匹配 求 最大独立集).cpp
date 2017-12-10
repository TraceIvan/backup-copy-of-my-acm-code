//题意：选出最小路径覆盖图中所有点，路径可以交叉，也就是允许路径有重复的点。
#include<iostream>
#include<queue>
#include<memory.h>
#include<algorithm>
#include<cmath>
using namespace std;
int n, t, m,p, Nx, Ny, dis, totalr, totalc;
const int maxn = 110;//最大行数
const int maxm = 110;//最大列数
const int maxp = 550;//x集与y集最多元素
const int INF = 0x7fffffff;
bool mp[maxp][maxp];//1表示该ij可以匹配
int cx[maxp];//记录x集合中匹配的y元素是哪一个
int dx[maxp];
int cy[maxp];//记录y集合中匹配的x元素是哪一个
int dy[maxp];
int vis[maxp];//标记该顶点是否访问过

struct ps
{
    int like;
    int u;
    int dislike;
    int v;
}people[maxp];


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
//最大独立集=节点总个数-最小覆盖集，最小覆盖集=最大匹配，所以最大独立集=节点总个数-最大匹配
//如果A喜欢的动物是B不喜欢的动物，或者A不喜欢的动物是B喜欢的动物，那么A、B之间就产生了矛盾，我们就在A和B之间建立一条边，然后求出最多有多少对孩子之间产生矛盾，用这个结果除以2就是最大匹配数。
int main()
{
    while (~scanf("%d%d%d", &n, &m,&p))
    {
        memset(mp, 0, sizeof(mp));

        for (int i = 1; i <= p; i++)
        {
            int u, v;
            char like, dislike;
            cin >> like >> u >> dislike >> v;
            if (like == 'C')
            {
                people[i].like = 1;
                people[i].u = u;
                people[i].dislike = 2;
                people[i].v = v;
            }
            else
            {
                people[i].like = 2;
                people[i].u = u;
                people[i].dislike = 1;
                people[i].v = v;
            }
            
        }
        for (int i = 1; i <= p; i++)
        {
            for (int j = i + 1; j <= p; j++)
            {
                ps a = people[i], b = people[j];
                if (a.dislike == b.like&&a.v == b.u)
                {
                    mp[i][j] = mp[j][i] = true;
                }
                else if (a.like == b.dislike&&a.u == b.v)
                {
                    mp[i][j] = mp[j][i] = true;
                }
            }
        }
        Nx = p, Ny = p;
        int ans = MaxMatch();
        printf("%d\n",p - ans/2);
    }
    return 0;
}