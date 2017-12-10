#include<iostream>
using namespace std;
const int maxn = 1010;
int pre[maxn];
int cnt;
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
    if (fx != fy) pre[fx] = fy, cnt--;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        cnt = n;
        for (int i = 1; i <= n; i++) pre[i] = i;
        for (int i = 0; i < m; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            Join(x, y);
        }
        printf("%d\n", cnt);
    }
    return 0;
}