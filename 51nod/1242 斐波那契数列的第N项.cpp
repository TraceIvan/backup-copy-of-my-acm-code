#include <cstdio>    
#include <iostream>    
#include <vector>
#include<cstring>
using namespace std;   
const long long MOD = 1000000009;
long long n;
long long re[2][2];
void mul(long long (*a)[2],long long (*b)[2])  //æÿ’Û≥À∑®    
{
    memset(re, 0, sizeof(re));
    for(long long i=0;i<2;i++)    
    {    
        for(long long k=0;k<2;k++)    
        {    
            for(long long j=0;j<2;j++)    
                re[i][j] = ( re[i][j] + a[i][k] * b[k][j] ) % MOD;    
        }    
    }    
}    
    
void solve_pow(long long(*a)[2],long long n) //øÏÀŸ√›    
{    
    long long b[2][2] = {0};
    for(long long i=0;i<2;i++)
        b[i][i]=1;   
    while(n>0)    
    {    
        if (n & 1)
        {
            mul(b, a);
            memcpy(b, re, sizeof(re));
        }
        mul(a,a);
        memcpy(a, re, sizeof(re));
        n >>= 1;    
    }
    memcpy(re, b, sizeof(b));
}    
 
void solve()    
{    
    long long a[2][2];
    while(~scanf("%lld",&n) && n!=-1)    
    {    
        a[0][0]=1,a[0][1]=1;    
        a[1][0]=1,a[1][1]=0;    
        solve_pow(a,n);    
        printf("%lld\n",re[1][0]);    
    }    
}    
int main()    
{    
    solve();    
    return 0;    
}    