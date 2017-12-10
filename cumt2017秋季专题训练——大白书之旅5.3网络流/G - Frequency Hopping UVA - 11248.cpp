#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
//Dicnicģ��
//��С���У�����ߵ�����=������������ߵ�����=0������С������������ߵ�����֮��=�����
const int maxn = 110;
const int maxe = 10010*2;
const int INF = 0x3f3f3f3f;
struct edge
{
    int from, to, cap, flow,next;//�ߵ���㡢�յ㡢������������ͬ������һ���ߵı��
    edge(int ff=0,int tt=0,int cc=0,int fw=0,int nn=0):from(ff),to(tt),cap(cc),flow(fw),next(nn){ }
    friend bool operator <(const edge&a, const edge&b)
    {
        if (a.from == b.from)
        {
            if (a.to < b.to) return true;
            else return false;
        }
        else if (a.from < b.from) return true;
        else return false;
    }
}Edge[maxe];
int Head[maxn],tmp_head[maxn],totedge;
vector<edge>ans;

struct Dicnic
{
    int n;
    bool vis[maxn];
    int level[maxn];
    int st, ed;
    vector<int>mincut;
    int needflow;

    void Init(int nodes,int source,int dest)
    {
        n = nodes, st = source, ed = dest;
        memset(Head, -1, sizeof(Head));
        totedge = 0;
    }

    void addedge(int from, int to, int cap)
    {
        Edge[totedge] = edge(from, to, cap, 0, Head[from]);
        Head[from] = totedge++;
        Edge[totedge] = edge(to, from, 0, 0, Head[to]);
        Head[to] = totedge++;
    }

    bool Dicnic_bfs()//���ɲ��ͼ
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
            q.pop();
            if (u == ed) return true;
            for (int i = Head[u]; i != -1; i = Edge[i].next)
            {
                v = Edge[i].to;
                if (Edge[i].cap > Edge[i].flow && !vis[v] && level[v] == -1)
                {//��֤��������ʣ�����������ڲ�������
                    vis[v] = true;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return false;
    }

    int Dinic_dfs(int u, int maxf)
    {
        if (u == ed||maxf==0) return maxf;

        int flow = 0,f;
        for (int& i = tmp_head[u]; i != -1; i = Edge[i].next)
        {
            int v = Edge[i].to;
            if (Edge[i].cap - Edge[i].flow > 0 && level[v] == level[u] + 1)
            {
                f = Dinic_dfs(v, min(maxf, Edge[i].cap - Edge[i].flow));
                if (f > 0)
                {
                    Edge[i].flow += f;
                    Edge[i ^ 1].flow -= f;
                    flow += f;
                    maxf -= f;
                    if (0 == maxf) break;
                    if (flow >= needflow) return flow;
                }
            }
        }
        return flow;
    }

    int Dinic_maxflow(int needf=INF)//�������
    {
        int ret = 0;
        needflow = needf;//��Ҫ����
        while (Dicnic_bfs())
        {
            memcpy(tmp_head, Head, sizeof(Head));
            ret += Dinic_dfs(st, INF);
            if (ret >= needflow) return ret;
        }
        return ret;
    }

    void GetMincut()//�����С��
    {
        mincut.clear();
        for (int i = 0; i < totedge; i++)
        {
            if (vis[Edge[i].from] && !vis[Edge[i].to] && Edge[i].cap > 0) mincut.push_back(i);
        }
    }

    void Reduce()//��ʣ������
    {
        for (int i = 0; i < totedge; i++) Edge[i].cap -= Edge[i].flow;
    }

    void Clearflow()//�ѵ�ǰ��������
    {
        for (int i = 0; i < totedge; i++) Edge[i].flow = 0;
    }

}dnc;
int main()
{
    int N, E, C;
    int Case = 1;
    while (~scanf("%d%d%d", &N, &E, &C))
    {
        if (N == 0 && E == 0 && C == 0) break;
        dnc.Init(N, 1, N);
        for (int i = 1; i <= E; i++)
        {
            int from, to, cap;
            scanf("%d%d%d", &from, &to, &cap);
            dnc.addedge(from, to, cap);
        }
        int flow = dnc.Dinic_maxflow(C);
        printf("Case %d: ", Case++);
        if (flow >= C) printf("possible\n");
        else
        {
            dnc.GetMincut();
            dnc.Reduce();
            ans.clear();
            int sz = dnc.mincut.size();
            for (int i = 0; i < sz; i++)
            {
                edge &tmp = Edge[dnc.mincut[i]];
                tmp.cap = C;
                dnc.Clearflow();
                if (flow + dnc.Dinic_maxflow(C - flow) >= C) ans.push_back(tmp);
                tmp.cap =0;
            }
            if (ans.empty()) printf("not possible\n");
            else
            {
                sort(ans.begin(), ans.end());
                printf("possible option:");
                sz = ans.size();
                for (int i = 0; i < sz; i++)
                {
                    if (i) printf(",");
                    printf("(%d,%d)", ans[i].from, ans[i].to);
                }
                printf("\n");
            }
        }
    }
    return 0;
}