#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
const int maxn = 210;
const double INF = 1e9;
int n;
struct node
{
    int x;
    int y;
    node(int xx=0,int yy=0):x(xx),y(yy){ }
};
node points[maxn];
double dis[maxn];
double D[maxn][maxn];
bool vis[maxn];
int cnt[maxn];
int id;
bool SPFA(int root)
{
    for (int i = 0; i <= id; i++) dis[i] = INF;
    memset(vis, 0, sizeof(vis));
    queue<int>q;
    q.push(root);
    dis[root] = 0, vis[root] = true, cnt[root] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = 1; i <= id; i++)
        {
            if (dis[u] + D[u][i] < dis[i])
            {
                dis[i] = dis[u] + D[u][i];
                if (!vis[i])
                {
                    vis[i] = true;
                    cnt[i]++;
                    q.push(i);
                    if (cnt[i] > id)return false;
                }
            }
        }
    }
    return true;
}
int main()
{
    //freopen("in.txt", "r", stdin);
    double v1 = 40000.0 / 60.0;
    double v2 = 10000.0 / 60.0;
    while (~scanf("%d%d%d%d", &points[1].x, &points[1].y, &points[2].x, &points[2].y))
    {
        memset(D, 0, sizeof(D));
        id = 2;
        bool isfirst = true;
        int tx, ty;
        while (~scanf("%d%d", &tx, &ty))
        {
            if (tx == -1 && ty == -1)
            {
                isfirst = true;
                continue;
            }
            if (isfirst)
            {
                isfirst = false;
                id++;
                points[id].x = tx, points[id].y = ty;
            }
            else
            {
                id++;
                points[id].x = tx, points[id].y = ty;
                D[id][id - 1]=D[id - 1][id] = sqrt(1.0*(points[id].x - points[id - 1].x)*(points[id].x - points[id - 1].x) + (points[id].y - points[id - 1].y)*(points[id].y - points[id - 1].y))/v1;
            }
        }
        for (int i = 1; i <= id; i++)
        {
            for (int j = i+1; j <= id; j++)
            {
                if (D[i][j] == 0)
                {
                    D[i][j]=D[j][i]= sqrt(1.0*(points[i].x - points[j].x)*(points[i].x - points[j].x) + (points[i].y - points[j].y)*(points[i].y - points[j].y)) / v2;
                }
            }
        }//以上预处理各点间的距离，只有相邻车站才能用地铁，否则都为步行
        SPFA(1);
        printf("%.0lf\n", dis[2]);
    }
    return 0;
}