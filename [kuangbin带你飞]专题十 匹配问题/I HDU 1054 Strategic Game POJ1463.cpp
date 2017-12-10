#include<iostream>
#include<queue>
#include<memory.h>
#include<algorithm>
#include<cmath>
using namespace std;
int n, t, m, Nx, Ny, dis, totalr, totalc;
const int maxn = 50;//�������
const int maxm = 15;//�������
const int maxk = 1505;
const int INF = 0x7fffffff;
bool mp[maxk][maxk];//1��ʾ��ij����ƥ��
int cx[maxk];//��¼x������ƥ���yԪ������һ��
int dx[maxk];
int cy[maxk];//��¼y������ƥ���xԪ������һ��
int dy[maxk];
int vis[maxk];//��Ǹö����Ƿ���ʹ�
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
    while (~scanf("%d",&n))
    {
        memset(mp, 0, sizeof(mp));
        int cnt = 0,cur,num;
        char c;
        for (int i = 1; i <= n; i++)
        {
            cin >> cur >> c >> c >> num >> c;
            cur = cur + 1;
            for (int j = 1; j <= num; j++)
            {
                int v;
                cin >> v;
                v = v + 1;
                mp[cur][v] = true;
                mp[v][cur] = true;
            }
        }
        

        Nx = n, Ny = n;
        int ans = MaxMatch();
        printf("%d\n", ans / 2);
    }
    return 0;
}