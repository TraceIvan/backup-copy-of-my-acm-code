#include<iostream>
#include<queue>
#include<map>
#include<string>
using namespace std;
const int INF = 0x3f3f3f3f;
struct node
{
    int from;
    int to;//��ָ��Ľڵ�
    int next;//�������һ����
    int cap;//�ߵ�����
    int flow;//�ߵ�����
}Eg[100000];

int head[1000], work[1000], level[1000];
/**head �ڵ������ͷ��work �����㷨�е���ʱ����ͷ��level �����ξ���*/
bool vis[15500];
int edges, st, ed,nodes;
int n,m,k;
map<string, int>gid;
int rpt[110];//��������Щ���Ͳ���
int devices[110];//�õ�����ͷ����
int adp[110][2];//ת����
/**��ʼ������ͼ����Ϣ*/
void Init(int _node, int _src, int _dest)
{
    nodes = _node, st = _src, ed = _dest;
    memset(head, -1, sizeof(head));
    edges = 0;
}
/**����һ��u ��v ����Ϊc �ı�*/
void addedge(int u, int v, int c)
{
    Eg[edges].from = u, Eg[edges].to = v, Eg[edges].cap = c, Eg[edges].flow = 0, Eg[edges].next = head[u], head[u] = edges++;
    Eg[edges].from = v, Eg[edges].to = u, Eg[edges].cap = 0, Eg[edges].flow = 0, Eg[edges].next = head[v], head[v] = edges++;
}
/**���Ѽ����ÿ������Դ�����̾��룬������ܵ�����˵���㷨����*/
void BuildGraph(int cnt)
{
    //Դ��Ϊ0���������Ϊ1~n,�õ���Ϊn+1~n+m,ת����Ϊn+m+1~n+m+k,���Ϊn+m+k+1.�Ӳ�������ͷ����
    Init(n+m+k+1, 0,n+m+k+1);
    //Դ��Ͳ�������
    for (int i = 1; i <= n; i++) addedge(st, i, 1);
    //�õ��������
    for (int i = 1; i <= m; i++) addedge(n+i, ed, 1);
    //�������õ�����������ֱ����
    for (int i = 1; i <= m; i++)
    {
        if (devices[i] <= n) addedge(devices[i], n + i, 1);
    }
    //������ת������ͷ
    for (int i = 1; i <= k; i++)
    {
        if (adp[i][1] <= n) addedge(adp[i][1], n + m + i, INF);
    }
    //ת������׵�ת������ͷ
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (i != j&&adp[i][0] == adp[j][1])
            {
                addedge(n + m + i, n + m + j,INF);
            }
        }
    }
    //ת������׵��õ���
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (adp[i][0] == devices[j])
            {
                addedge(n + m + i, n + j, INF);
            }
        }
    }
}
bool Dinic_bfs()
{
    queue<int>q;
    int i, u, v;
    memset(level, -1, sizeof(level));
    memset(vis, 0, sizeof(vis));
    q.push(st);
    level[st] = 0;
    vis[st] = true;
    while (!q.empty())
    {
        u = q.front();
        if (u == ed) return true;
        q.pop();
        for (i = head[u]; i != -1; i = Eg[i].next)
        {
            v = Eg[i].to;
            if (Eg[i].cap>Eg[i].flow && !vis[v] && level[v] == -1)
            {
                vis[v] = true;
                /**�����߱�����ʣ������*/
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return false;
}
/**Ѱ�ҿ�����������·�㷨�����ڵ�ľ������ң��ӿ��ٶ�*/
int Dinic_dfs(int u, int maxf)
{
    if (u == ed)return maxf;
    /**work ����ʱ����ͷ��������i ������������Ѱ�ҹ��ı߲���Ѱ��*/
    int flow = 0, f;
    for (int &i = work[u], v; i != -1; i = Eg[i].next)
    {
        v = Eg[i].to;
        if (Eg[i].cap - Eg[i].flow>0 && level[v] == level[u] + 1)
        {
            f = Dinic_dfs(v, min(maxf, Eg[i].cap - Eg[i].flow));
            Eg[i].flow += f;
            Eg[i ^ 1].flow -= f;
            /**������������ı�*/
            flow += f;
            if (flow == maxf) return flow;
        }
    }
    return flow;
}
int Dinic_flow()
{
    int ret = 0;
    while (Dinic_bfs())
    {
        memcpy(work, head, sizeof(head));
        ret += Dinic_dfs(st, INF);
    }
    return ret;
}
int main()
{
    string s;
    while (~scanf("%d",&n))
    {
        int cnt = 1;
        for (int i = 1; i <= n; i++)
        {
            cin >> s;
            if (!gid[s])
            {
                gid[s] = cnt++;
            }
        }
        n = cnt - 1;
        //����������1~n
        scanf("%d", &m);
        for (int i = 1; i <= m; i++)
        {
            cin >> s;
            cin >> s;
            if (!gid[s]) gid[s] = cnt++;
            int pos = gid[s];
            devices[i] = pos;
        }//�豸���n+1~n+m
        scanf("%d", &k);
        for (int i = 1; i <= k; i++)
        {
            cin >> s;
            if (!gid[s]) gid[s] = cnt++;
            int ff = gid[s];
            cin >> s;
            if (!gid[s]) gid[s] = cnt++;
            int tt = gid[s];
            adp[i][0] = ff;
            adp[i][1] = tt;
        }
        BuildGraph(cnt);
        printf("%d\n", m-Dinic_flow());
    }
    return 0;
}