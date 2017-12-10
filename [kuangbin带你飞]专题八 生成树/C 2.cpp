#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;
int n,m;//��㣨���У���Ŀ
const int maxn = 110;
const int INF = 0x7fffffff;
int dis[maxn][maxn];//���ݵ������õ�����֮��ľ���
bool mintree[maxn][maxn];//�����С�������ı�
int pathmax[maxn][maxn];//��¼��С�������������·�������Ȩֵ
int pre[maxn];//���������С�������У�ÿ�����ĸ����
bool vis[maxn];//��¼������С�������Ľ��

int Prime()
{
    memset(vis, 0, sizeof(vis));
    memset(mintree, 0, sizeof(mintree));
    memset(pathmax, 0, sizeof(pathmax));
    int sum = 0;
    int mincost[maxn];//��¼��ǰȨֵ
    for (int i = 1; i <= n; i++)
    {
        mincost[i] = dis[1][i];
        pre[i] = 1;
    }
    vis[1] = true;
    for (int i = 1; i < n; i++)
    {//ÿ��ѡ1�������
        int u = 0;
        for (int j = 1; j <= n; j++)
        {//��δ����ĵ��ҵ�һ����С�ı�
            if (!vis[j])
            {
                if (u == 0 || mincost[j] < mincost[u])
                {
                    u = j;
                }
            }
        }
        mintree[u][pre[u]] = mintree[pre[u]][u] = true;
        sum += dis[u][pre[u]];
        vis[u] = true;

        for (int j = 1; j <= n; j++)
        {
            if (vis[j] && j != u)
            {//������������·�������Ȩֵ
                pathmax[u][j] = pathmax[j][u] = max(pathmax[j][pre[u]], dis[u][pre[u]]);
            }
            else if (!vis[j])
            {//������ѡ��㵽δѡ������̾���
                if (dis[u][j] < mincost[j])
                {
                    mincost[j] = dis[u][j];
                    pre[j] = u;
                }
            }
        }
    }
    return sum;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)//t���������
    {
        scanf("%d%d", &n,&m);
        for (int i = 1; i <= n; i++)
        {
            dis[i][i] = 0;
            for (int j = i+1; j <= n; j++)
            {
                dis[i][j] = dis[j][i] = INF;
            }
        }
        for (int i = 1; i <= m; i++)
        {
            int u, v, l;
            scanf("%d%d%d", &u, &v, &l);
            dis[u][v] = dis[v][u] = l;
        }
        int inilen = Prime();
        int len2 = INF;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j||dis[i][j]==INF) continue;
                if (mintree[i][j])continue;
                len2 = min(len2, inilen + dis[i][j] - pathmax[i][j]);
                
            }
        }
        printf("%d %d\n", inilen, len2);
    }
    return 0;
}