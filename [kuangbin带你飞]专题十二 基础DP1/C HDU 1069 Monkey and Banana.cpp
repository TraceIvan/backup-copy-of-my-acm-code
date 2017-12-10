#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 40;
struct node
{
    int l;
    int w;
    int h;
}blocks[maxn*6];
int dp[maxn * 6];//以i为底的最高高度
bool Cmp(const node&a, const node&b)
{
    if (a.l == b.l)return a.w > b.w;
    else return a.l > b.l;
}
int main()
{
    int n;
    int Case = 1;
    while (~scanf("%d", &n))
    {
        if (n == 0)break;
        int cnt = 0;
        while (n--)
        {
            int xi, yi, zi;
            scanf("%d%d%d", &xi, &yi, &zi);
            blocks[cnt].l = xi, blocks[cnt].w = yi, blocks[cnt].h = zi;
            cnt++;
            blocks[cnt].l = yi, blocks[cnt].w = xi, blocks[cnt].h = zi;
            cnt++;
            blocks[cnt].l = xi, blocks[cnt].w = zi, blocks[cnt].h = yi;
            cnt++;
            blocks[cnt].l = zi, blocks[cnt].w = xi, blocks[cnt].h = yi;
            cnt++;
            blocks[cnt].l = yi, blocks[cnt].w = zi, blocks[cnt].h = xi;
            cnt++;
            blocks[cnt].l = zi, blocks[cnt].w = yi, blocks[cnt].h = xi;
            cnt++;
        }
        sort(blocks, blocks + cnt, Cmp);
        for (int i = 0; i < cnt; i++) dp[i] = blocks[i].h;
        for (int i = cnt - 2; i >= 0; --i)
        {//从小的开始DP
            for (int j = i + 1; j < cnt; j++)
            {
                if (blocks[j].l < blocks[i].l&&blocks[j].w < blocks[i].w)
                {
                    if (dp[j] + blocks[i].h > dp[i])
                    {
                        dp[i] = dp[j] + blocks[i].h;
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < cnt; i++)
        {
            ans = max(ans, dp[i]);
        }
        printf("Case %d: maximum height = %d\n", Case++, ans);
    }


    return 0;
}