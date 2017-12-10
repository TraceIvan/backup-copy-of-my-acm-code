#include<iostream>
#include<queue>
#include<memory.h>
#include<algorithm>
#include<cmath>
using namespace std;
int n,t,m,Nx,Ny,dis;
const int maxn = 3100;//�������
const int maxm = 3100;//�������
const int maxk = 3100;
const int INF = 0x7fffffff;
bool mp[maxn][maxm];//1��ʾ��ij����ƥ��
int cx[maxm];//��¼x������ƥ���yԪ������һ��
int dx[maxm];
int cy[maxn];//��¼y������ƥ���xԪ������һ��
int dy[maxn];
int vis[maxm];//��Ǹö����Ƿ���ʹ�
struct point
{
    int x;
    int y;
    int v;
}customer[maxk];
struct point2
{
    int x;
    int y;
}unbrella[maxk];
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
        if (dx[u] > dis) break;        //˵��������·�����ȴ���dis��û�н������ȴ���һ��BFS������  
        for (int v = 1; v <= Ny; v++)
            if (mp[u][v] && dy[v] == -1)
            {        //v��δƥ���  
                dy[v] = dx[u] + 1;
                if (cy[v] == -1) dis = dy[v];    //�õ�����BFS�����������  
                else
                {
                    dx[cy[v]] = dy[v] + 1;         //v��ƥ��㣬��������  
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
            if (cy[v] != -1 && dy[v] == dis) continue;   //��Σ�Ҳ��������·���ĳ��ȣ����ڱ��β��ҵ�dis����searchP��break�������Ҳ���ǻ���ȷ���Ƿ�������·����ֻ�е��ٴε���searchP()���жϡ�  
            if (cy[v] == -1 || DFS(cy[v]))
            {     //������·��������ƥ�伯  
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
            if (cx[i] == -1 && DFS(i)) res++;   //���ҵ�һ������·����ƥ����res++  
    }
    return res;
}

int main()
{
    int C;
    scanf("%d", &C);
    int Case = 1;
    while (C--)
    {
        scanf("%d", &t);
        memset(mp, 0, sizeof(mp));
        scanf("%d", &m);
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &customer[i].x, &customer[i].y, &customer[i].v);
        }
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &unbrella[i].x, &unbrella[i].y);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                double dis = sqrt((unbrella[i].x - customer[j].x)*(unbrella[i].x - customer[j].x) + (unbrella[i].y - customer[j].y)*(unbrella[i].y - customer[j].y));
                if (dis <= t*customer[j].v) mp[i][j] = true;
            }
        }
        Nx = n, Ny = m;
        int ans = MaxMatch();
        printf("Scenario #%d:\n", Case++);
        printf("%d\n\n", ans);
    }
    return 0;
}