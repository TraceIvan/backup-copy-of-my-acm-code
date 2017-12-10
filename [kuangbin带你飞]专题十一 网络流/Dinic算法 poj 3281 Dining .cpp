#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int INF = 250000;
/**oo ��ʾ�����*/
const int maxe = 250000;
/**mm ��ʾ�ߵ������������סҪ��ԭͼ���������ڼӱߵ�ʱ����˫���*/
const int maxn = 450;
/**mn ��ʾ����������*/
int nodes, st, ed, edges;
/**node ��ʾ�ڵ�����src ��ʾԴ�㣬dest ��ʾ��㣬edge ͳ�Ʊ���*/
struct node
{
    int from;
    int to;//��ָ��Ľڵ�
    int next;//�������һ����
    int cap;//�ߵ�����
    int flow;//�ߵ�����
}Eg[maxe];

int head[maxn], work[maxn],level[maxn];
/**head �ڵ������ͷ��work �����㷨�е���ʱ����ͷ��level �����ξ���*/
bool vis[maxn];

/**��ʼ������ͼ����Ϣ*/
void Init(int _node, int _src, int _dest)
{
    nodes = _node, st = _src, ed = _dest;
    memset(head,-1,sizeof(head));
    edges = 0;
}
/**����һ��u ��v ����Ϊc �ı�*/
void addedge(int u, int v, int c)
{
    Eg[edges].flow=u,Eg[edges].to = v, Eg[edges].cap = c,Eg[edges].flow=0,Eg[edges].next= head[u], head[u] = edges++;
    Eg[edges].from=v,Eg[edges].to = u, Eg[edges].cap = 0,Eg[edges].flow=0,Eg[edges].next = head[v], head[v] = edges++;
}
/**���Ѽ����ÿ������Դ�����̾��룬������ܵ�����˵���㷨����*/
bool Dinic_bfs()
{
    queue<int>q;
    int i, u, v;
    memset(level, -1, sizeof(level));
    memset(vis, 0, sizeof(vis));
    q.push(st);
    level[st] = 0;
    vis[st] = true;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        for (i = head[u]; i !=-1; i = Eg[i].next)
        {
            v = Eg[i].to;
            if (Eg[i].cap>Eg[i].flow &&!vis[v])
            {
                vis[v] = true;
                /**�����߱�����ʣ������*/
                level[v] = level[u] + 1;
                if (v == ed)return true;
                q.push(v);
            }
        }
    }
    return false;
}
/**Ѱ�ҿ�����������·�㷨�����ڵ�ľ������ң��ӿ��ٶ�*/
int Dinic_dfs(int u, int maxf)
{
    if (u == ed||maxf==0)return maxf;
    /**work ����ʱ����ͷ��������i ������������Ѱ�ҹ��ı߲���Ѱ��*/
    int flow = 0, f;
    for (int &i = work[u], v; i != -1; i = Eg[i].next)
    {
        v = Eg[i].to;
        if (level[v] == level[u] + 1 && (f = Dinic_dfs(v, min(maxf, Eg[i].cap - Eg[i].flow))) > 0)
        {
            Eg[i].flow += f;
            Eg[i ^ 1].flow -= f;
            /**������������ı�*/
            flow += f;
            maxf -= f;
            if (maxf == 0) break;
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
    int n, f, d;
    while (~scanf("%d%d%d", &n, &f, &d))
    {
        //��ͼ
        Init(2 * n + f + d + 1, 0, 2 * n + f + d + 1);
        for (int i = 1; i <= n; i++)
        {
            addedge(i,i+n,1);//ÿͷţ��㣬��ţ����ţ
            int fi, di;
            scanf("%d%d", &fi, &di);
            for (int j = 1; j <= fi; j++)
            {
                int ff;
                scanf("%d", &ff);
                addedge(2 * n + ff,i,1);//ʳ�ﵽ��ţ
            }
            for (int j = 1; j <= di; j++)
            {
                int dd;
                scanf("%d", &dd);
                addedge(i + n,2 * n + f + dd,1);//��ţ������
            }

        }
        for (int i = 1; i <= f; i++) addedge(0,2 * n + i,1);//Դ�㵽ʳ��
        for (int j = 1; j <= d; j++) addedge(2 * n + f + j,2 * n + f + d + 1,1);//���ϵ����

        int ans = Dinic_flow();

        printf("%d\n", ans);
    }
    return 0;
}