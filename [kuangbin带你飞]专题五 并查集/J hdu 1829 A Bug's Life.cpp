#include<iostream>
using namespace std;
const int maxn = 2100;
int pre[maxn];
int r[maxn];
int n, m;
void Init()
{
    for (int i = 0; i <= n; i++)
    {
        pre[i] = i;
        r[i] = 0;
    }
}
int Find(int x)
{
    if (pre[x] == x)return x;
    else
    {
        int fa = pre[x];
        pre[x] = Find(fa);
        r[x] = r[x] ^ r[fa];
        return pre[x];
    }
}

bool Join(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx == fy)return true;
    else
    {
        pre[fx] = fy;
        r[fx] = r[x] ^ r[y] ^ 1;
        return false;
    }
}
int main()
{
    int t;
    int Case = 1;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        Init();
        bool flag = true;
        while (m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if (!flag)continue;
            if (Join(u, v))
            {
                if (r[u] ^ r[v] != 1)
                {
                    flag = false;
                }
            }
        }
        if (flag) printf("Scenario #%d:\nNo suspicious bugs found!\n\n", Case++);
        else printf("Scenario #%d:\nSuspicious bugs found!\n\n", Case++);
    }
    return 0;
}