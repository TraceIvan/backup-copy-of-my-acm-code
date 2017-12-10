//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn = 880;
int n, m;
int dir[4][2] = { 1,0,-1,0,0,1,0,-1 };
char maps[maxn][maxn];
struct node
{
    int x, y;
} now, Next, b, g, z[2];
queue <node> q[2], qt;//q[0]为boy，q[1]为girl，qt为当前操作的队列
int step = 0;
void pre_maps()
{
    //多组输入，清零
    while (!q[0].empty())
        q[0].pop();
    while (!q[1].empty())
        q[1].pop();
    while (!qt.empty())
        qt.pop();

    int k = 0;
    for (int i = 0; i<n; i++)
        scanf("%s", maps[i]);
    for (int i = 0; i<n; i++)
        for (int j = 0; j<m; j++)
        {
            if (maps[i][j] == 'Z')
            {
                z[k].x = i;
                z[k].y = j;
                k++;
            }
            if (maps[i][j] == 'M')
            {
                b.x = i;
                b.y = j;
            }
            if (maps[i][j] == 'G')
            {
                g.x = i;
                g.y = j;
            }
        }
}

bool check(node a)
{
    if (a.x <0 || a.y <0 || a.x >= n || a.y >= m)//超出地图直接返回
        return true;
    for (int i = 0; i<2; i++)
    {
        if (maps[a.x][a.y] == 'X' || (abs(a.x - z[i].x) + abs(a.y - z[i].y)) <= 2 * step)//是墙，或者被鬼抓到返回
            return true;
    }
    return false;
}
bool bfs(int k, int num, char start, char End)
{
    qt = q[k];//用来表示当前层的搜索，队列也可以直接赋值
    for (int i = 0; i<num; i++)
    {
        while (!qt.empty())
        {
            now = qt.front();
            qt.pop();
            q[k].pop();
            if (check(now)) continue;
            for (int j = 0; j<4; j++)
            {
                Next.x = now.x + dir[j][0];
                Next.y = now.y + dir[j][1];
                if (check(Next)) continue;
                if (maps[Next.x][Next.y] == start) continue;//已经走过了
                if (maps[Next.x][Next.y] == End)//两个bfs相遇
                    return true;
                maps[Next.x][Next.y] = start;//走过的地点直接标记
                q[k].push(Next);
            }
        }
        qt = q[k];//将下一层的队列赋值给当前层
    }
    return false;
}

int solve()
{
    bool flag1 = false, flag2 = false;
    step = 0;
    q[0].push(b);
    q[1].push(g);
    while (!q[0].empty() && !q[1].empty())
    {
        step++;

        flag1 = bfs(0, 3, 'M', 'G');//boy的bfs
        flag2 = bfs(1, 1, 'G', 'M');//girl的bfs
        if (flag1 || flag2)//当有一方相遇了
            return step;
    }
    return -1;//没有找到
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        pre_maps();
        printf("%d\n", solve());
    }
}