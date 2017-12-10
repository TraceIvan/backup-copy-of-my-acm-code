#include<algorithm>
using namespace std;
const int maxn = 100010;
int pre[maxn];
bool vis[maxn];
int Find(int x)
{
    if (pre[x] == x)return x;
    else
    {
        int fa = pre[x];
        pre[x] = Find(fa);
        return pre[x];
    }
}

bool Union(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx == fy)return true;
    else
    {
        pre[fx] = fy;
        return false;
    }
}
int main()
{
    int u, v;
    int Case = 1;
    while (~scanf("%d%d", &u, &v))
    {
        if (u<0 && v <0)break;
        if (u == 0 && v == 0)
        {
            printf("Case %d is a tree.\n",Case++);
            continue;
        }
        for (int i = 0; i < maxn; i++)pre[i] = i;
        bool flag = true;
        do
        {
            if (!flag)continue;
            if (Union(u, v))
            {
                flag = false;
            }
        } while (scanf("%d%d", &u, &v) && u != 0 && v != 0);
        if (!flag) printf("Case %d is not a tree.\n",Case++);
        else
        {
            memset(vis, 0, sizeof(vis));
            int cnt = 0;
            for (int i = 0; i < maxn; i++)
            {
                if (pre[i] == i)continue;
                int f = Find(i);
                if (!vis[f])
                {
                    cnt++;
                    vis[f] = true;
                }
            }
            if (cnt == 1) printf("Case %d is a tree.\n", Case++);//ֻ����һ����ͨ��
            else printf("Case %d is not a tree.\n",Case++);
        }
    }
    return 0;
}