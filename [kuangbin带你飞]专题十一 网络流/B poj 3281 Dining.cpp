#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int n, f, d,st,ed;
const int maxn = 450;
const int maxe = 250000;
const int INF = 0x7fffffff;

int mp[maxn][maxn];
int level[maxn];//�ֲ�
int vis[maxn];
int flow[maxn];
int prepath[maxn];

int BFS()
{
    queue<int>q;
    memset(prepath, 0, sizeof(prepath));
    memset(vis, 0, sizeof(vis));
    prepath[st] = st;
    flow[st] = INF;
    q.push(st);
    vis[st] = true;
    while (!q.empty())
    {//���������ȶ����Ż�
        int t = q.front();
        q.pop();
        if (t == ed)break;
        for (int i = 1; i <=ed; i++)
        {
            if (i != st && !vis[i] && mp[t][i])
            {
                vis[i] = true;//��ֹ�߷���
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
    while (~scanf("%d%d%d", &n, &f, &d))
    {
        //��ͼ
        st = 0, ed = 2 * n + f + d + 1;
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= n; i++)
        {
            mp[i][i + n] = 1;//ÿͷţ��㣬��ţ����ţ
            int fi, di;
            scanf("%d%d", &fi, &di);
            for (int j = 1; j <= fi; j++)
            {
                int ff;
                scanf("%d", &ff);
                mp[2 * n + ff][i] = 1;//ʳ�ﵽ��ţ
            }
            for (int j = 1; j <= di; j++)
            {
                int dd;
                scanf("%d", &dd);
                mp[i + n][2 * n + f + dd] = 1;//��ţ������
            }
            
        }
        for (int i = 1; i <= f; i++) mp[0][2 * n + i] = 1;//Դ�㵽ʳ��
        for (int j = 1; j <= d; j++)mp[2 * n + f + j][2 * n + f + d + 1] = 1;//���ϵ����

        //Edmonds_Karp�㷨
        int ans = Edmonds_Karp();

        printf("%d\n", ans);
    }
    return 0;
}