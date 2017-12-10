//��С������������С��������һ���ߵõ�.
//���⣺
//��n�����У���ʼ��Ҫ����n-1��·��������������Ҫ�����һ������������Ե�������������㡣��ʼ��ϣ��������n-1��·����֮����̡�Ȼ���츣ͻȻ��ð������˵������ħ�������Բ��������������ͱ����������һ��·������
//��ʼ��ϣ���츣�ܰ�Ҫ�޵�n - 1��·���������������������츣ϣ���ܰ�Ҫ������������������������������ÿ��·����Ҫ����������ָ����·���ӵ��������е�����֮�͡�
//���գ���ʼ�ʸ�����һ����ʽ��A / B��A��ָҪ�츣��ħ�����������·���������� B��ָ�����츣�����������֮�������n - 2��·������֮�ͣ�ѡʹ��A / Bֵ����������

#include<iostream>
#include<algorithm>
using namespace std;
int n;//��㣨���У���Ŀ
const int maxn = 1010;
struct node
{
    int x;
    int y;
    int v;
}points[maxn];//��¼ÿ�����е����꣬�Լ����е��˿�(���ֵ)
double dis[maxn][maxn];//���ݵ������õ�����֮��ľ���
bool mintree[maxn][maxn];//�����С�������ı�
double pathmax[maxn][maxn];//��¼��С�������������·�������Ȩֵ
int pre[maxn];//���������С�������У�ÿ�����ĸ����
bool vis[maxn];//��¼������С�������Ľ��

void Init()//��ʼ�����õ�����ľ���
{
    for (int i = 1; i <= n; i++)
    {
        dis[i][i] = 0;
        for (int j = i + 1; j <= n; j++)
        {
            double distance = sqrt((points[i].x - points[j].x)*(points[i].x - points[j].x) + (points[i].y - points[j].y)*(points[i].y - points[j].y));
            dis[i][j] = dis[j][i] = distance;
        }
    }
}

double Prime()
{
    memset(vis, 0, sizeof(vis));
    memset(mintree, 0, sizeof(mintree));
    memset(pathmax, 0, sizeof(pathmax));
    double sum = 0;
    double mincost[maxn];//��¼��ǰȨֵ
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
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d", &points[i].x, &points[i].y, &points[i].v);
        }
        Init();
        double inilen=Prime();
        double ratio = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j) continue;
                if (mintree[i][j])//���ѡ�������С�������е�һ���ߣ���ʣ�µ�·����Ϊinilen - dis[i][j]
                {
                    ratio = max(ratio, (points[i].v + points[j].v) / (inilen - dis[i][j]));
                }
                else//���ѡ��Ĳ�����С�������еıߣ���ô��������ߺ�ͻ��γ�һ��������Ҫɾȥ��С��������i��j��·����Ȩֵ���ı�
                {
                    ratio = max(ratio, (points[i].v + points[j].v) / (inilen - pathmax[i][j]));
                }
            }
        }
        printf("%.2lf\n", ratio);
    }
    return 0;
}