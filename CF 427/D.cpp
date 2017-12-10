#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 5010;

char a[maxn];
int dp[maxn][maxn];
int num[maxn];

int main()
{
    cin >> a;
    int maxnum = 0;
    int n = strlen(a);
    int i, j, l;
    for (l = 1; l <= n; l++)
    {
        for (i = 0; i + l <= n; i++)
        {
            j = i + l - 1;
            if (l == 1)
            {
                dp[i][i] = 1;
                num[1]++;
                maxnum = max(maxnum, 1);
            }
            else if (l == 2)
            {
                if (a[i] == a[j])
                {
                    dp[i][j] = 2;
                    num[2]++;
                    maxnum = max(maxnum, 2);
                }
            }
            else
            {
                int mid = dp[i + 1][j - 1];
                if (a[i] == a[j] && mid>0)
                {
                    if (dp[i][i + l / 2 - 1]>0 && dp[i + (l + 1) / 2][j]>0)
                    {
                        dp[i][j] = dp[i][i + l / 2 - 1] + 1;
                        num[dp[i][j]]++;
                        maxnum = max(maxnum, dp[i][j]);
                    }
                    else
                    {
                        dp[i][j] = 1;
                        num[1]++;
                    }
                }
            }
        }
    }
    for (i = maxnum; i>1; i--)
    {
        num[i - 1] += num[i];
    }
    for (i = 1; i <= n; i++)
    {
        if (i == 1) cout << num[i];
        else cout << " " << num[i];
    }
    cout << endl;
    return 0;
}