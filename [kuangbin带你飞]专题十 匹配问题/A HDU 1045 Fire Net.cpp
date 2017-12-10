#include<iostream>
using namespace std;
int n;
char mp[5][5];
int ans;
bool check(int r, int c)
{
    for (int i = r; i>=0; i--)
    {
        if (mp[i][c] == '#') return false;
        if (mp[i][c] == 'X') break;
    }
    for (int i = c; i >= 0; i--)
    {
        if (mp[r][i] == '#') return false;
        if (mp[r][i] == 'X')break;
    }
    return true;
}
void DFS(int r, int c,int num)
{
    if (r == n&& c ==0)
    {
        if (num > ans) ans = num;
        return;
    }
    if (mp[r][c] == '.'&&check(r, c))
    {
        mp[r][c] = '#';
        DFS(r + (c + 1) / n, (c + 1) % n, num + 1);
        mp[r][c] = '.';
    }
    DFS(r + (c + 1) / n, (c + 1) % n, num);
}
int main()
{
    while (~scanf("%d", &n))
    {
        if (n == 0)break;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> mp[i][j];
            }
        }
        ans = 0;
        DFS(0,0,0);
        printf("%d\n", ans);
    }
    return 0;
}