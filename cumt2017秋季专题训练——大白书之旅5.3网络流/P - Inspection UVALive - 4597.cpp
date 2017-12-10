#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;


const int maxn = 210;
const int maxe = 100 * 100 * 2 + 100 * 4 + 100;
const int INF = 0x3f3f3f3f;
int dindgree[maxn], n;//dindgree[i]�����i�����ȼ�ȥ���ȵ�ֵ
vector<int>result;
struct edge
{
    int from, to, cap, flow, next;
    edge(int ff=0,int tt=0,int cc=0,int ww=0,int nn=0):from(ff),to(tt),cap(cc),flow(ww),next(nn){ }
}Edge[maxe];
int Head[maxn], tmp_head[maxn], totedge;
struct dicnic
{
    int n, st, ed;
    int level[maxn];
    bool vis[maxn];

    void Init()
    {
        memset(Head, -1, sizeof(Head));
        totedge = 0;
    }
    void set(int nodes, int source, int dest)
    {
        n = nodes, st = source, ed = dest;
    }
    void addedge(int from, int to, int cap)
    {
        Edge[totedge] = edge(from, to, cap, 0, Head[from]);
        Head[from] = totedge++;
        Edge[totedge] = edge(to, from, 0, 0, Head[to]);
        Head[to] = totedge++;
    }
    bool dicnic_bfs()
    {
        memset(level, -1, sizeof(level));
        memset(vis, 0, sizeof(vis));
        queue<int>q;
        q.push(st);
        vis[st] = true;
        level[st] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == ed) return true;
            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                int v = Edge[i].to;
                if (Edge[i].cap > Edge[i].flow && !vis[v])
                {
                    vis[v] = true;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return false;
    }
    int dicnic_dfs(int u, int maxf)
    {
        if (u == ed || maxf == 0) return maxf;

        int flow = 0, f;
        for (int &i = tmp_head[u]; i != -1; i = Edge[i].next)
        {
            int v = Edge[i].to;
            if (Edge[i].cap > Edge[i].flow&&level[v] == level[u] + 1)
            {
                int f = dicnic_dfs(v, min(maxf, Edge[i].cap - Edge[i].flow));
                if (f > 0)
                {
                    Edge[i].flow += f;
                    if(Edge[i].cap>0) dindgree[v] += f;//Ĭ��ÿ�����߹�һ�Σ���Ϊ0.�����ӵ�����ʾ�ظ����߹��Ĵ���
                    Edge[i ^ 1].flow -= f;
                    flow += f;
                    maxf -= f;
                    if (maxf == 0) break;
                }
            }
        }
        return flow;
    }

    int cal_maxflow()
    {
        int ret = 0;
        while (dicnic_bfs())
        {
            memcpy(tmp_head, Head, sizeof(Head));
            ret += dicnic_dfs(st, INF);
        }
        return ret;
    }
}dnc;



int main()
{
    while (~scanf("%d", &n)&&n)
    {
        dnc.Init();
        dnc.set(n + 2, 0, n + 1);
        memset(dindgree, 0, sizeof(dindgree));
        for (int i = 1; i <= n; i++)
        {
            int k;
            scanf("%d", &k);
            dindgree[i] -= k;
            for (int j = 1; j <= k; j++)
            {
                int to;
                scanf("%d", &to);
                dnc.addedge(i, to, INF);//ÿ���߿����߶�Σ���������ΪINF
                dindgree[to]++;
            }
        }
        int nowedge = totedge;
        int ans = 0;//ans��ֵ�������������
        for (int i = 1; i <= n; i++)
        {
            /*���򽨱ߡ�ԭ������Ӧ����Դ��������ȴ�����ȵĵ㣬��ȴ��ڳ��ȵĵ������㡣
            �������ǳ��ȴ�����ȵĵ������㣬Դ��������ȴ��ڳ��ȵĵ㡣*/
            if (dindgree[i]<0) dnc.addedge(i,n+1, -dindgree[i]),ans+= - dindgree[i];
            if (dindgree[i] >0) dnc.addedge(0,i, dindgree[i]);
        }
        ans -= dnc.cal_maxflow();//��ȥ���������
        printf("%d\n", ans);

        
        for (int i = 1; i <= n; i++)
        {
            while (dindgree[i] < 0)
            {//��ʾ���ܽ���i��Ϊĳһ��·�ߵ���㣨���ȴ�
                dindgree[i]++;//�޸���������Ϊ���Ĵ���
                result.clear();//result��¼����·��
                result.push_back(i);
                int u = i;
                while (1)
                {
                    bool ok = false;//��ʾ�ܷ�Ӹõ�����������
                    for (int i = Head[u]; i != -1; i = Edge[i].next)
                    {
                        ////Ĭ��ÿ�����߹�һ�Σ���Ϊ0.���������Ϊ1����ʾ�������������ߡ���ѡ��ı�Ӧ��Ϊ����ߣ���û�к������Դ���������
                        if (Edge[i].flow == -1 || Edge[i].cap == 0 || Edge[i].to == n + 1 || Edge[i].to == 0)continue;
                        
                        ok = true;
                        Edge[i].flow--;
                        u = Edge[i].to;
                        result.push_back(u);
                        break;
                    }
                    if (!ok) break;//���ܼ����ߣ��˳���ӡ·��
                }
                int sz = result.size();
                for (int i = 0; i < sz; i++)
                {
                    if (i) printf(" ");
                    printf("%d", result[i]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}