#include<iostream>
#include<memory.h>
using namespace std;
int n, m;
const int maxn = 110;
int dis[maxn][maxn];
void Run()
{
    memset(dis, 0, sizeof(dis));
    for (int i = 0; i < m; i++)
    {
        int winner, failer;
        scanf("%d%d", &winner, &failer);
        dis[winner][failer] = 1;
        dis[failer][winner] = -1;
    }
    //类Floyd
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dis[i][k] == dis[k][j] && (dis[i][k] == 1 || dis[i][k] == -1))
                {//闭包传递性
                    dis[i][j] = dis[i][k];
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int ct = 0;
        for (int j = 1; j <= n; j++)
        {
            if (dis[i][j] != 0) ct++;
        }
        if (ct == n - 1) ans++;
    }
    printf("%d\n", ans);
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        Run();
    }
    return 0;
}