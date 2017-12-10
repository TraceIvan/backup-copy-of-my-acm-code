#include<iostream>
#include<memory.h>
#include<string.h>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn = 1005;
char s[maxn];
int dp[maxn];
int n;
bool Judge(int st, int ed)
{
    for (; st <= ed; st++, ed--)
    {
        if (s[st] != s[ed]) return false;
    }
    return true;
}
int main()
{
    cin >> n;
    while (n--)
    {
        scanf("%s", s);
        memset(dp, 0, sizeof(dp));
        int sz = strlen(s);
        for (int i = 0; i < sz; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                if (Judge(j, i))
                {
                    if (j == 0) dp[i] = 1;
                    else dp[i] = dp[i] == 0 ? dp[j - 1] + 1 : min(dp[i], dp[j - 1] + 1);
                }
            }
        }
        cout << dp[sz - 1] << endl;
    }
    return 0;
}