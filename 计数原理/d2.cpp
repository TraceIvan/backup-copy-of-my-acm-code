#include<stdio.h>
#include<string.h>
typedef long long LL;
int A, B, K, a[11], f[11][110][110];
LL solve(int limit)
{
    int s1 = 0, s2 = 0;
    for (int i = 10; i >= 0; i--) a[i] = limit % 10, limit /= 10;
    memset(f, 0, sizeof(f));
    for (int i = 0; i < 10; i++)
    {
        s1 = (s1 + a[i]) % K, s2 = (s2 * 10 + a[i]) % K;
        for (int j = 0; j < K; j++)
            for (int k = 0; k < K; k++)
                for (int d = 0; d < 10; d++)
                    f[i + 1][(j + d) % K][(k * 10 + d) % K] += f[i][j][k];
        for (int d = 0; d < a[i + 1]; d++) ++f[i + 1][(s1 + d) % K][(s2 * 10 + d) % K];
    }
    LL ans = f[10][0][0];
    if ((s1 + a[10]) % K == 0 && (s2 * 10 + a[10]) % K == 0) ++ans;
    return ans;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d%d", &A, &B, &K);
        if (K >= 100) printf("0\n");
        else printf("%lld\n", solve(B) - solve(A - 1));
    }
    return 0;
}