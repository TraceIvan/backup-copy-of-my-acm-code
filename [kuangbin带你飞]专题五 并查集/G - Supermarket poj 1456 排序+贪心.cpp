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

bool vis[maxt];
bool Cmp(const node&a,const node&b)
{
    if (a.pi == b.pi)return a.di > b.di;
    else return a.pi > b.pi;
}
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &goods[i].pi, &goods[i].di);
        }
        sort(goods, goods + n,Cmp);
        memset(vis, 0, sizeof(vis));
        int sum = 0;
        for (int i = 0; i < n; i++)
        {//从利润最大的开始选择
            int tt = goods[i].di;
            for (int j = tt; j >= 1; j--)
            {//从其保质期到期往前，找到第一个可以放的位置
                if (!vis[j])
                {
                    vis[j] = true;
                    sum += goods[i].pi;
                    break;
                }
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}