#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;
long long n, m, x, k;
long long mp[15][210],p1[15][210];
bool visr[15];
long long col[210];
long long ans;
void Cal(int cnt)
{
    memset(col, 0, sizeof(col));
    long long sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (visr[i]) p1[i][j] = x;
            else p1[i][j] = mp[i][j];
            col[j] += p1[i][j];
            sum += p1[i][j];
        }
    }
    long long remain = k - cnt;
    sort(col, col + m);
    remain = min(remain, m);
    for (int i = 0; i < m; i++)
    {
        if (remain>0&&col[i] < n*x)
        {
            sum += n*x;
            sum -= col[i];
            remain--;
        }
    }
    ans = max(ans, sum);
}
void DFS(int r, int cnt)
{
    if (cnt > k) return;
    if (r == n)
    {
        Cal(cnt);
        return;
    }
    
    visr[r] = true;
    DFS(r + 1, cnt + 1);
    visr[r] = false;
    DFS(r + 1, cnt);
}
int main()
{
    while (~scanf("%lld%lld%lld%lld", &n, &m, &x, &k))
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++) scanf("%lld", &mp[i][j]);
        }
        ans = 0;
        memset(visr, 0, sizeof(visr));
        DFS(0, 0);
        printf("%lld\n", ans);
    }
    return 0;
}