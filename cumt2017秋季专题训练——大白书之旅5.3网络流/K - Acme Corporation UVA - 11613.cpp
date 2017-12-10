#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int maxn = 510;
const int maxe = (maxn + maxn + maxn*maxn) * 2 + 10;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cap, flow, cost, next;
    edge(int ff=0,int tt=0,int cc=0,int ww=0,int ss=0,int nn=0):from(ff),to(tt),cap(cc),flow(ww),cost(ss),next(nn){ }
}Edge[maxe];
int Head[maxn], totedge;

struct MCMF
{
    int pre[maxn];//��¼������·���ϣ�����i�ıߵı��
    int dist[maxn];
    bool vis[maxn];
    int N,st,ed;

    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
    }

    void Set(int nodes, int source, int dest)
    {
        N = nodes, st = source, ed = dest;
    }

    void addedge(int from, int to, int cap, int cost)
    {
        Edge[totedge] = edge(from, to, cap, 0, cost, Head[from]);
        Head[from] = totedge++;
        Edge[totedge] = edge(to, from, 0, 0, -cost, Head[to]);
        Head[to] = totedge++;
    }

    bool SPFA(int s, int t)//��һ��SPFA ��s����t�����ٻ���·�� �Ҹ�·����ÿһ���߲������� ,������ ˵�����Լ������㣬��֮����  
    {
        queue<int>q;
        memset(dist, INF , sizeof(dist));
        memset(vis, 0, sizeof(vis));
        memset(pre, -1, sizeof(pre));
        
        dist[s] = 0;
        vis[s] = true;
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = false;

            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                if (dist[Edge[i].to] > dist[u] + Edge[i].cost&&Edge[i].cap > Edge[i].flow)
                {
                    dist[Edge[i].to] = dist[u] + Edge[i].cost;
                    pre[Edge[i].to] = i;
                    if (!vis[Edge[i].to])
                    {
                        vis[Edge[i].to] = true;
                        q.push(Edge[i].to);
                    }
                }
            }
        }
        return pre[t] != -1&&dist[t]<=0;
    }

    void cal_MCMF(long long&cost,long long&flow)
    {
        flow = 0, cost = 0;
        while (SPFA(st, ed))
        {
            //ͨ������,��Դ�㵽�������ٻ���·�� ����С������
            int Min = INF;
            for (int i = pre[ed]; i != -1; i = pre[Edge[i ^ 1].to])
            {
                Min = min(Min, Edge[i].cap - Edge[i].flow);
            }
            //����
            for (int i = pre[ed]; i != -1; i = pre[Edge[i ^ 1].to])
            {
                Edge[i].flow += Min;
                Edge[i ^ 1].flow -= Min;
                cost +=1ll*Edge[i].cost*Min;
            }
            flow += Min;
        }
    }
}mcmf;

int M, I;//���·ݣ�ÿ����һ���µĻ���
struct node
{
    int mi, ni, pi, si, Ei;//��λ�������ã��������������λ���ۼ۸�������������ƣ��ɱ����·�
    node(int mm=0,int nn=0,int pp=0,int ss=0,int ee=0):mi(mm),ni(nn),pi(pp),si(ss),Ei(ee){ }
}parameters[110];
int main()
{
    int t;
    scanf("%d", &t);
    int Case = 1;
    while (t--)
    {
        scanf("%d%d", &M, &I);
        for (int i = 1; i <= M; i++)
        {
            scanf("%d%d%d%d%d", &parameters[i].mi, &parameters[i].ni, &parameters[i].pi, &parameters[i].si, &parameters[i].Ei);
        }
        mcmf.Init();
        mcmf.Set(2 * M + 2, 0, 2 * M + 1);
        for (int i = 1; i <= M; i++)
        {
            mcmf.addedge(0, 2 * i - 1, parameters[i].ni, parameters[i].mi);//������������󣬷���+
            mcmf.addedge(2 * i, 2 * M + 1, parameters[i].si,-parameters[i].pi);//�����������������-
        }
        for (int i = 1; i <= M; i++)
        {
            for (int j = i; j <= min(i + parameters[i].Ei, M); j++)
            {
                mcmf.addedge(2 * i - 1, 2 * j, INF, I*(j - i));//I*(j - i)��ʾÿ��λ��i�±�����j����Ҫ�ķ���
            }
        }
        long long flow, cost;
        mcmf.cal_MCMF(cost, flow);
        printf("Case %d: %lld\n", Case++, -cost);
    }
    return 0;
}