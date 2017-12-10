#include<iostream>
using namespace std;
int a[110][110], b[110][110];
int re[110][110];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <=n; i++)
        {
            for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++) scanf("%d", &b[i][j]);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                re[i][j] = 0;
                for (int k = 1; k <= n; k++)
                {
                    re[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j > 1) printf(" ");
                printf("%d", re[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}