#include<iostream>
using namespace std;
const int maxn = 510;
const int maxm = 2010;
int n, m;
int pre[maxn];
int r[maxn];//0：平局；1：pre[x]赢了x;2:x赢了pre[x]
void Init()
{
    for (int i = 0; i <= n; i++)
    {
        pre[i] = i;
        r[i] = 0;
    }
}
struct stp
{
    int u;
    int v;
    int d;
}stps[maxm];

int ok[maxn];

int Find(int x)
{
    if (pre[x] == x)return x;
    else
    {
        int fa = pre[x];
        pre[x] = Find(fa);
        r[x] = (r[x] + r[fa]) % 3;
        return pre[x];
    }
}
bool Union(int x, int y,int d)
{
    int fx = Find(x), fy = Find(y);
    if (fx == fy)return true;
    else
    {
        pre[fx] = fy;
        r[fx] = (3 - r[x] + d + r[y]) % 3;
        return false;
    }
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 0; i < m; i++)
        {
            int u, v,d;
            char c;
            scanf("%d%c%d", &u, &c, &v);
            if (c == '=')d = 0;
            else if (c == '<') d = 1;
            else d = 2;
            stps[i].u = u, stps[i].v=v, stps[i].d=d;
        }
        memset(ok, 0, sizeof(ok));
        for (int i = 0; i < n; i++)
        {
            Init();
            for (int j = 0; j < m; j++)
            {
                if (stps[j].u == i || stps[j].v == i)continue;
                if (Union(stps[j].u, stps[j].v, stps[j].d))
                {
                    if ((r[stps[j].u]+3-r[stps[j].v]) % 3 != stps[j].d)
                    {
                        ok[i] = j + 1;
                        break;
                    }
                }
            }
        }
        int cnt = 0,rline=0,judgeperson=0;
        for (int i = 0; i < n; i++)
        {
            if (ok[i]== 0)
            {
                cnt++;
                judgeperson = i;
            }
            if (ok[i] > rline) rline = ok[i];
        }
        if (cnt == 0)printf("Impossible\n");
        else if (cnt == 1)printf("Player %d can be determined to be the judge after %d lines\n",judgeperson,rline);
        else printf("Can not determine\n");
    }
    return 0;
}