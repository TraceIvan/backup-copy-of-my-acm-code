#include<iostream>
#include<algorithm>
#include<memory.h>
#include<cstdio>
using namespace std;
const int maxn = 1010;
struct node
{
    int dscore;
    int deadline;
}homeworks[maxn];
bool Cmp(const node&a, const node&b)
{
    if (a.dscore == b.dscore) return a.deadline < b.deadline;
    else return a.dscore > b.dscore;
}

bool vis[maxn];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &homeworks[i].deadline);
        for (int i = 0; i < n; i++) scanf("%d", &homeworks[i].dscore);
        sort(homeworks, homeworks + n, Cmp);
        memset(vis, 0, sizeof(vis));
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            int t = homeworks[i].deadline;
            int j;
            for (j = t; j >= 1; --j)
            {
                if (!vis[j])
                {
                    vis[j] = true;
                    break;
                }
            }
            if (j < 1) sum += homeworks[i].dscore;
        }
        printf("%d\n", sum);
    }
    return 0;
}