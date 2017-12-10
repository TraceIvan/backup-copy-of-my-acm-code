#define _CRT_SECURE_NO_DEPRECATE 

#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#define INF 99999999;
using namespace std;

int n;
int a[110][110];
int match[110];
int vis[110];

int dfs(int u)
{
    for (int v = 1; v <= n; v++)
    {
        if (a[u][v] && !vis[v])
        {
            vis[v] = 1;
            if (match[v] == -1 || dfs(match[v]))
            {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int hungarian()
{
    int ans = 0;
    memset(match, -1, sizeof(match));

    for (int i = 1; i <= n; i++)
    {
        memset(vis, 0, sizeof(vis));
        ans += dfs(i);
    }
    return ans;
}

int main()
{
    while (~scanf("%d", &n))
    {
        memset(a, 0, sizeof(a));

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                scanf("%d", &a[i][j]);

        if (hungarian() != n)
            printf("-1\n");
        else
        {
            int num = 0;
            int L[110], R[110];
            for (int i = 1; i <= n; i++)
            {
                if (i != match[i])
                {
                    for (int j = 1; j <= n; j++)
                    {
                        if (i == match[j])
                        {
                            L[num] = i;
                            R[num] = j;
                            num++;
                            swap(match[i], match[j]);
                            break;
                        }
                    }
                }
            }

            printf("%d\n", num);
            for (int i = 0; i < num; i++)
                printf("C %d %d\n", L[i], R[i]);
        }
    }
    return 0;
}