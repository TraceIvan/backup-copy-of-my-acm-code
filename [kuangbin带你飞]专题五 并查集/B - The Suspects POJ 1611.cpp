#include<iostream>
using namespace std;
const int maxn = 30010;
int pre[maxn];
int Cnt[maxn];
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
    int fx = Find(x), fy = Find(y);
    if (fx != fy) pre[fx] = fy,Cnt[fy]+=Cnt[fx];
}
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 0; i <= n; i++) pre[i] = i,Cnt[i]=1;
        if (n == 0 && m == 0)break;
        for (int i = 0; i < m; i++)
        {
            int k;
            scanf("%d", &k);
            int pre, now;
            for (int i = 0; i < k; i++)
            {
                int x;
                scanf("%d", &x);
                if (i == 0) pre = now = x;
                else
                {
                    now = x;
                    Join(now, pre);
                    pre = now;
                }
            }
        }
        //int cnt = 0;
        //for (int i = 0; i < n; i++)
        //{
        //    if (Find(i) == Find(0)) cnt++;
        //}
        printf("%d\n", Cnt[Find(0)]);
    }
    return 0;
}