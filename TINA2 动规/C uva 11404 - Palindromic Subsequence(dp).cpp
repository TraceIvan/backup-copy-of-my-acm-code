#include<iostream>
#include<string>
#include<memory.h>
using namespace std;
const int maxn = 1005;
struct node
{
    int len;
    string str;
}dp[maxn][maxn];

int main()
{
    string s;
    while (cin >> s)
    {
        int len = s.length();
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < len; i++)
        {
            dp[i][i].len = 1;
            dp[i][i].str = s[i];
        }
        for (int i = len - 1; i >= 0; i--)
        {
            for (int j = i; j < len; j++)
            {

                if (s[i] == s[j])
                {
                    if (i == j)
                    {
                        dp[i][j].len = 1;
                        dp[i][j].str = s[i];
                    }
                    else
                    {
                        dp[i][j].len = dp[i + 1][j - 1].len + 2;
                        dp[i][j].str = s[i] + dp[i + 1][j - 1].str + s[j];
                    }
                }
                else
                {
                    if (dp[i + 1][j].len > dp[i][j - 1].len)
                    {
                        dp[i][j].len = dp[i + 1][j].len;
                        dp[i][j].str = dp[i + 1][j].str;
                    }
                    else if (dp[i + 1][j].len < dp[i][j - 1].len)
                    {
                        dp[i][j].len = dp[i][j - 1].len;
                        dp[i][j].str = dp[i][j - 1].str;
                    }
                    else
                    {
                        dp[i][j].len = dp[i][j - 1].len;
                        if (dp[i][j - 1].str < dp[i + 1][j].str) dp[i][j].str = dp[i][j - 1].str;
                        else dp[i][j].str = dp[i + 1][j].str;
                    }
                }
            }
        }
        cout << dp[0][len - 1].str << endl;
    }
    return 0;
}
