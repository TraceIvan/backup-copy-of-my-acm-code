#include<iostream>
#include<algorithm>
using namespace std;
int n;
const int maxn = 10010;
const int maxt = 10010;
struct node
{
    int pi;
    int di;
}goods[maxn];

int pre[maxt];
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

void Union(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx != fy)
    {
        if (fx < fy) pre[fy] = fx;
        else pre[fx] = fy;
    }
}


void Init()
{
    for (int i = 0; i <maxt; i++)
    {
        pre[i] = i;
    }
}
bool Cmp(const node&a, const node&b)
{
    if (a.pi == b.pi)return a.di > b.di;
    else return a.pi > b.pi;
}
int main()
{
    while (~scanf("%d", &n))
    {
        Init();
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &goods[i].pi, &goods[i].di);
        }
        sort(goods, goods + n, Cmp);

        int sum = 0;
        
        for (int i = 0; i < n; i++)
        {
            int tt = goods[i].di;
            int ff = Find(tt);
            if (ff > 0)
            {
                Union(ff, ff - 1);
                sum += goods[i].pi;
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}