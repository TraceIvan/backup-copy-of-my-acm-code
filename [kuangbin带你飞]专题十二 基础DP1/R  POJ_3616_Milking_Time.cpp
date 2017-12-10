#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;
int n, m, r;
struct node
{
    int st;
    int ed;
    int f;
}pds[1010];
int dp[2000010];
bool Cmp(const node&a, const node&b)
{
    if (a.st == b.st)return a.ed < b.ed;
    else return a.st < b.st;
}
int main()
{
    while (~scanf("%d%d%d", &n, &m, &r))
    {
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &pds[i].st, &pds[i].ed, &pds[i].f);
        }
        
        sort(pds+1, pds + m+1, Cmp);
        pds[0].st = 0, pds[0].ed = 0, pds[0].f = 0;
        memset(dp, 0, sizeof(dp));
        int ans = 0;
        for (int i = 1; i <= m; i++)
        {
            int ed = pds[i].ed + r;
            int ee = pds[i].st;
            if (ed > n + r)continue;
            for (int j = 0; j < i; j++)
            {
                int te;
                if (j == 0) te = pds[j].ed;
                else te = pds[j].ed + r;
                if (te <= ee)
                {
                    dp[ed] = max(dp[ed], dp[te] + pds[i].f);
                    ans = max(dp[ed], ans);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}