#include <cstdio>    
#include <iostream>    
#include <vector>
#include<cstring>
using namespace std;
const int maxn = 110;
const long long MOD = 1e9+7;
int n,m;
long long re[maxn][maxn];
long long tmp[maxn][maxn];
long long mp[maxn][maxn];

void mul(long long(*a)[maxn], long long(*b)[maxn])  //æÿ’Û≥À∑®    
{
    memset(re, 0, sizeof(re));
    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
        {
            for (int k= 0; k<n; k++)
                re[i][j] = (re[i][j] + a[i][k] * b[k][j]) % MOD;
        }
    }
}

void solve_pow() //øÏÀŸ√›
{
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i<n; i++)
        tmp[i][i] = 1;
    while (m>0)
    {
        if (m & 1)
        {
            mul(tmp, mp);
            memcpy(tmp, re, sizeof(re));
        }
        mul(mp, mp);
        memcpy(mp, re, sizeof(re));
        m>>= 1;
    }
    memcpy(re, tmp, sizeof(tmp));
}

void solve()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &mp[i][j]);
        }
    }
    solve_pow();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j > 0) printf(" ");
            printf("%lld", re[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        solve();
    }
    return 0;
}