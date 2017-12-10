#include<iostream>
using namespace std;
int n, k;
char m[10][10];
int cnt = 0;
bool Judge(int r, int c)
{
    for (int i = 0; i < n; i++)
    {//判断列是否只有一个
        if (i == r) continue;
        if (m[i][c] == '@') return false;
    }
    return true;
}
void DFS(int r, int num)
{//按行放
    if (num == 0)
    {
        cnt++;
        return;
    }
    if (r == n)return;
    for (int i = 0; i < n; i++)
    {
        if (m[r][i] == '#')
        {
            if (Judge(r, i))
            {
                m[r][i] = '@';
                DFS(r + 1, num - 1);
                m[r][i] = '#';
            }
        }
    }
    DFS(r + 1, num);//如果这一行不放棋子
}
int main()
{
    while (~scanf("%d%d", &n, &k))
    {
        if (n == -1 && k == -1)break;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) cin >> m[i][j];
        }
        cnt = 0;
        DFS(0, k);
        printf("%d\n", cnt);
    }
    return 0;
}