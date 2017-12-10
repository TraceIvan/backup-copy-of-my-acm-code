#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 1010;
struct node
{
    int w;
    int v;
    int id;
}mice[maxn];
int dp[maxn];
int pre[maxn];
bool Cmp(const node&a, const node&b)
{
    return a.v > b.v;
}
void Print(int r,int num)
{
    if (r != -1)
    {
        Print(pre[r],num+1);
        printf("%d\n", mice[r].id);
    }
    else printf("%d\n", num);
}
int main()
{
    int cnt = 0;
    while (~scanf("%d%d", &mice[cnt].w, &mice[cnt].v))
    {
        mice[cnt].id = cnt + 1;
        cnt++;
    }
    sort(mice, mice + cnt, Cmp);
    for (int i = 0; i < cnt; i++) dp[i] = 1, pre[i] = -1;
    int re = 0,maxl=0;
    for (int i = 0; i < cnt; i++)
    {
        int ans = 0,pos=i;
        for (int j = 0; j < i; j++)
        {
            if (dp[j]+1 > dp[i]&&mice[i].w > mice[j].w&&mice[i].v<mice[j].v)
            {
                dp[i] = dp[j] + 1;
                pre[i] = j;
                pos = j;
            }
        }
        if (dp[i] > maxl) maxl = dp[i], re = i;
    }
    Print(re,0);
    return 0;
}