//���⣺ѡ����С·������ͼ�����е㣬·�����Խ��棬Ҳ��������·�����ظ��ĵ㡣
#include<iostream>
#include<queue>
#include<memory.h>
#include<algorithm>
#include<cmath>
using namespace std;
int n, t, m,p, Nx, Ny, dis, totalr, totalc;
const int maxn = 110;//�������
const int maxm = 110;//�������
const int maxp = 550;//x����y�����Ԫ��
const int INF = 0x7fffffff;
bool mp[maxp][maxp];//1��ʾ��ij����ƥ��
int cx[maxp];//��¼x������ƥ���yԪ������һ��
int dx[maxp];
int cy[maxp];//��¼y������ƥ���xԪ������һ��
int dy[maxp];
int vis[maxp];//��Ǹö����Ƿ���ʹ�

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
//��������=�ڵ��ܸ���-��С���Ǽ�����С���Ǽ�=���ƥ�䣬������������=�ڵ��ܸ���-���ƥ��
//���Aϲ���Ķ�����B��ϲ���Ķ������A��ϲ���Ķ�����Bϲ���Ķ����ôA��B֮��Ͳ�����ì�ܣ����Ǿ���A��B֮�佨��һ���ߣ�Ȼ���������ж��ٶԺ���֮�����ì�ܣ�������������2�������ƥ������
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