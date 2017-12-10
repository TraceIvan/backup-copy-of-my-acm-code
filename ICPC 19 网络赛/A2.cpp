#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n, m;
int Nx, Ny, dis;
const int maxn = 1100;//�������
const int maxm = 1100;//�������
const int maxk = 1100;
const int INF = 0x7fffffff;
bool mp[maxn][maxm];//1��ʾ��ij����ƥ��
int cx[maxm];//��¼x������ƥ���yԪ������һ��
int dx[maxm];
int cy[maxn];//��¼y������ƥ���xԪ������һ��
int dy[maxn];
int vis[maxm];//��Ǹö����Ƿ���ʹ�
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

int MaxMatch()
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