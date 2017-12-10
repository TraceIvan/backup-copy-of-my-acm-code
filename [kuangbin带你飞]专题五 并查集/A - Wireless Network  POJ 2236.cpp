#include<iostream>
#include<cstdio>
#include<memory.h>
#include<cmath>
using namespace std;
int n, d;
const int maxn = 1200;
int pre[maxn];
struct node
{
    int x;
    int y;
}cpt[maxn];
int Find(int x)
{
    int r = x;
    while (r != pre[r])
    {
        r = pre[r];
    }
    int i = x, j;
    while (pre[i] != r)
    {
        j = pre[i];
        pre[i] = r;
        i = j;
    }
    return r;
}
void Join(int x, int y)
{
    int px = Find(x), py = Find(y);
    if (px != py) pre[px] = py;
}
int main()
{
    while (~scanf("%d%d", &n, &d))
    {
        for (int i = 1; i <= n; i++) scanf("%d%d", &cpt[i].x, &cpt[i].y);
        memset(pre, 0, sizeof(pre));
        char op[3];
        while (~scanf("%s", op))
        {
            if (op[0] == 'O')
            {
                int p;
                scanf("%d", &p);
                pre[p] = p;
                for (int i = 1; i <= n; i++)
                {
                    if (i == p)continue;
                    double dis = sqrt(1.0*(cpt[i].x - cpt[p].x)*(cpt[i].x - cpt[p].x) + (cpt[i].y - cpt[p].y)*(cpt[i].y - cpt[p].y));
                    if (dis <= d&&pre[i]!=0)
                    {
                        Join(i, p);
                    }
                }
            }
            else
            {
                int p, q;
                scanf("%d%d", &p, &q);
                if (Find(p) != Find(q))printf("FAIL\n");
                else printf("SUCCESS\n");
            }
        }
    }
    return 0;
}