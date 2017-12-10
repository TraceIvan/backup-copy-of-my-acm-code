//bfs + 状态压缩：开始时把每一个点都入队，模拟3进制处理每个状态，最后 + 优化。
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
#define N 12//最多12个城市
#define LL long long
const int inf = 0x3fffffff;//最大值
int g[N][N];
int n, m, ans;
int mark[N][60000];//3^10=59064  j状态下走到i的时间
struct node
{
    int x, t, s, cnt;  //位置、时间、状态、个数
    friend bool operator<(node a, node b)
    {
        return a.t>b.t;
    }
};
int gettmp(int x, int k)  //得到X在3进制下的第K位是多少
{                        //判断该点是否经过了，经过了几次
    int t;
    while (x)
    {
        t = x % 3;
        k--;
        if (k == 0)
            break;
        x /= 3;
    }
    return k ? 0 : t;
}
void inti()//初始化数组
{
    int i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 0; j<(int)pow(3, n); j++)
            mark[i][j] = inf;
    }
}
void bfs()
{
    int i;
    priority_queue<node>q;//时间小的优先级高
    node cur, next;
    for (i = 1; i <= n; i++)
    {//一开始把每个点都加入队列
        cur.x = i;
        cur.s = pow(3, (i - 1));//状态，表示只有该点走过
        cur.t = 0;
        cur.cnt = 1;//经过城市一个
        q.push(cur);
        mark[i][0] = 0;
    }
    while (!q.empty())
    {
        cur = q.top();
        q.pop();
        for (i = 1; i <= n; i++)
        {
            if (g[cur.x][i] == inf)  //此路不通
                continue;
            next.cnt = cur.cnt;
            next.s = cur.s;
            next.t = cur.t + g[cur.x][i];
            if (ans<next.t)    //优化很重要
                continue;
            next.x = i;
            int t = gettmp(next.s, i);  //该点经过了几次，
            if (t >= 2)                 //经过2次后就不能走了
                continue;
            next.s += pow(3, (i - 1));    //该点经过次数加一
            if (t == 0)                 //经过一个新景点
            {
                next.cnt++;
                if (next.cnt == n)
                {
                    ans = min(ans, next.t);
                    continue;
                }
            }
            if (next.t<mark[i][next.s])
            {
                mark[i][next.s] = next.t;
                q.push(next);
            }
        }
    }
}
int main()
{
    int a, b, c, i, j;
    while (scanf("%d%d", &n, &m) != -1)
    {
        for (i = 0; i <= n; i++)
            for (j = 1; j <= n; j++)
                g[i][j] = (i == j ? 0 : inf);
        for (i = 0; i<m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            g[a][b] = g[b][a] = min(g[a][b], c);//考虑到重边
        }
        ans = inf;
        inti();
        bfs();
        if (ans == inf)
            ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}
