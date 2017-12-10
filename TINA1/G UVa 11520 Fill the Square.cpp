#include<iostream>
#include<cstdio>
using namespace std;
char m[15][15];
int n;
void Fill(int r, int c)
{
    for (char C = 'A'; C <= 'Z'; C++)
    {
        if (r - 1 >= 0 && m[r - 1][c] == C) continue;
        else if (c - 1 >= 0 && m[r][c - 1] == C) continue;
        else if (c + 1 < n&&m[r][c + 1] == C) continue;
        else if (r + 1 < n&&m[r + 1][c] == C) continue;
        m[r][c] = C;
        return;
    }
}
int main()
{
    int Case=1,N;
    cin >> N;
    while (N--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) cin >> m[i][j];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (m[i][j] == '.') Fill(i, j);
            }
        }
        printf("Case %d:\n", Case++);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) cout << m[i][j];
            cout << endl;
        }
    }
    return 0;
}