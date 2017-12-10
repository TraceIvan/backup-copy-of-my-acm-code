#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <queue>
using namespace std;

const int maxn = 155;
const int INF = 0x3f3f3f3f;
typedef long long ll;
int A, B, M, L, K;
int mp[maxn][maxn];

void floyd()
{
    for (int k = 1; k <= A; k++)
    {
        for (int i = 1; i <= A + B; i++)
        {
            for (int j = 1; j <= A + B; j++)
            {
                if (mp[i][j] > mp[i][k] + mp[k][j])
                {
                    mp[i][j] = mp[i][k] + mp[k][j];
                }
            }
        }
    }
}

struct node
{
    int u, k, cos;//当前结点、剩余次数、花费
    node(int uu = 0, int kk = 0, int cc = 0) :u(uu), k(kk), cos(cc)
    {}
    bool operator <(const node& a)const
    {
        return cos > a.cos;
    }
};
int dis[maxn][15];
int spfa()
{
    priority_queue<node> Q;
    for (int i = 0; i <= A + B; i++)
    {
        for (int j = 0; j <= 12; j++)
        {
            dis[i][j] = INF;
        }
    }
    Q.push(node(A + B, K, 0));
    dis[A + B][K] = 0;
    while (!Q.empty())
    {
        int u = Q.top().u;
        int k = Q.top().k;
        if (u == 1) return Q.top().cos;
        Q.pop();
        for (int i = 1; i <= A + B; i++)
        {
            if (i == u) continue;
            if (mp[u][i] == INF) continue;
            if (dis[i][k] > dis[u][k] + mp[u][i])
            {//不坐时
                dis[i][k] = dis[u][k] + mp[u][i];
                Q.push(node(i, k, dis[i][k]));
            }
            if (mp[u][i] <= L && dis[i][k - 1] > dis[u][k] && k != 0)
            {//如果可以花费一次使用次数从u直接到i
                dis[i][k - 1] = dis[u][k];
                Q.push(node(i, k - 1, dis[i][k - 1]));
            }
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d %d %d %d", &A, &B, &M, &L, &K);
        memset(mp, INF, sizeof(mp));
        for (int i = 1; i <= A + B; i++)
        {
            mp[i][i] = 0;
        }
        int a, b, c;
        for (int i = 0; i < M; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            mp[a][b] = mp[b][a] = c;
        }
        floyd();
        printf("%d\n", spfa());
    }
    return 0;
}