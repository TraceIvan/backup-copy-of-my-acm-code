#include<iostream>
#include<queue>
using namespace std;
const int maxn = 210;
const int maxm = 210;
const int INF = 0x7fffffff;
int n, m;//�㡢��
int st, ed;//Դ�㡢���
int mp[maxn][maxn];//��ʼ����
int prepath[maxn];//��¼ÿ������·����ǰ��
int flow[maxn];//��¼ÿ��BFS������·��ʱ������
int BFS()
{
    queue<int>q;
    memset(prepath, 0, sizeof(prepath));
    prepath[st] = st;
    flow[st] = INF;
    q.push(st);
    while (!q.empty())
    {//���������ȶ����Ż�
        int t = q.front();
        q.pop();
        if (t == ed)break;
        for (int i = 1; i <= n; i++)
        {
            if (i != st&&prepath[i] == 0 && mp[t][i])
            {
                flow[i] = flow[t] < mp[t][i] ? flow[t] : mp[t][i];
                q.push(i);
                prepath[i] = t;
            }
        }
    }
    if (prepath[ed] == 0) return -1;
    else return flow[ed];
}
int Edmonds_Karp()
{
    int maxflow = 0, dflow, cur, pre;
    while (1)
    {
        dflow = BFS();
        if (dflow == -1)break;
        maxflow += dflow;
        cur = ed;
        while (cur != st)
        {
            pre = prepath[cur];
            mp[pre][cur] -= dflow;//���������
            mp[cur][pre] += dflow;//��ӷ����
            cur = pre;
        }
    }
    return maxflow;
}
int main()
{
    while (~scanf("%d%d", &m, &n))
    {
        memset(mp, 0, sizeof(mp));
        st = 1, ed = n;
        for (int i = 0; i < m; i++)
        {
            int from, to, cap;
            scanf("%d%d%d", &from, &to, &cap);
            mp[from][to] += cap;
        }
        int maxflow = Edmonds_Karp();
        printf("%d\n", maxflow);
    }
    return 0;
}