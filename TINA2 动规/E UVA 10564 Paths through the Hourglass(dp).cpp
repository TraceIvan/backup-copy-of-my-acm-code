//f[i][j][k] 代表从(i, j)点往下走到最后一层和为k的方案数
//那么，显然可以得到状态转移：
//f[i][j][k] = f[i + 1][left][k - val] + f[i + 1][right][k - val], val = (i, j)格上的数字，left是往坐下走的坐标，right往右下走的坐标
#include<iostream>
#include<memory.h>
#include<cstdio>
using namespace std;
typedef long long ll;
int N, S;
ll dp[50][50][510];
int m[50][50];
void Input()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N - i+1; j++)
        {
            scanf("%d", &m[i][j]);
        }
    }
    for (int i = N+1; i <= 2 * N - 1; i++)
    {
        for (int j = 1; j <= i - N + 1; j++)
        {
            scanf("%d", &m[i][j]);
        }
    }
}
void Print()
{
    int pos;
    for (int i = 1; i <= N; i++)
    {
        if (dp[1][i][S])
        {
            cout <<i-1<< ' ';
            pos = i;
            break;
        }
    }
    int sum = S;
    for (int i = 2; i <= N; i++)
    {
            if (dp[i][pos - 1][sum - m[i - 1][pos]])
            {
                cout << 'L';
                sum -= m[i - 1][pos];
                pos--;
            }
            else
            {
                cout << 'R';
                sum -= m[i - 1][pos];
            }
    }
    for (int j = N+1; j <= 2 * N - 1; j++)
    {
        if (dp[j][pos][sum - m[j - 1][pos]])
        {
            cout << 'L';
            sum -= m[j - 1][pos];
        }
        else
        {
            cout << 'R';
            sum -= m[j - 1][pos];
            pos++;
        }
    }
    cout << endl;
}

int main()
{
    while (cin >> N >> S, N != 0 || S != 0)
    {
        Input();
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= N; i++) dp[2 * N - 1][i][m[2 * N - 1][i]] = 1;
        for (int i = 2 * N - 2; i >= N; i--)
        {
            for (int j = 1; j <= i - N + 1; j++)
            {
                int v = m[i][j];
                for (int tv = v; tv <= S; tv++)
                {
                    dp[i][j][tv] = dp[i + 1][j][tv-v] + dp[i + 1][j + 1][tv-v];
                }
            }
        }
        for (int i = N - 1; i >= 1; i--)
        {
            for (int j = 1; j <= N - i+1; j++)
            {
                int v = m[i][j];
                for (int tv = v; tv <= S; tv++)
                {
                    dp[i][j][tv] = dp[i + 1][j][tv-v] + dp[i + 1][j - 1][tv-v];
                }
            }
        }
        ll ans = 0;
        for (int i = 1; i <= N; i++) ans += dp[1][i][S];
        if (ans == 0) cout << ans << endl << endl;
        else
        {
            printf("%lld\n", ans);
            Print();
        }
    }
    return 0;
}