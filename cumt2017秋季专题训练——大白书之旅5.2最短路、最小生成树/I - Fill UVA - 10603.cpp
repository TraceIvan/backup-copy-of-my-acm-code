#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
int c[3], d;
const int maxv = 210;
int dist[maxv];//得到容量为i最少的倒水体积
bool vis[maxv][maxv];//表示a、b、c状态为i、j、d-i-j是否访问过
struct node
{
    int dis;//从开始到当前已倒过的水的体积
    int v[3];
    node(int dd=0,int vva=0,int vvb=0,int vvc=0):dis(dd)
    {
        v[0] = vva, v[1] = vvb, v[2] = vvc;
    }
    friend bool operator<(const node&a, const node&b)
    {
        return a.dis > b.dis;
    }
};
void BFS()
{
    memset(dist, -1, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    priority_queue<node>q;
    q.push(node(0, 0, 0, c[2]));
    vis[0][0] = true;
    while (!q.empty())
    {
        node cur = q.top();
        q.pop();
        for (int i = 0; i < 3; i++)
        {
            if (dist[cur.v[i]] == -1 || dist[cur.v[i]] > cur.dis) dist[cur.v[i]] = cur.dis;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i == j || cur.v[i] == 0 || cur.v[j] == c[j]) continue;
                int add = min(cur.v[i], c[j] - cur.v[j]);
                node tmp = cur;
                tmp.v[i] -= add;
                tmp.v[j] += add;
                tmp.dis += add;
                if (!vis[tmp.v[0]][tmp.v[1]])//由于肯定会越倒，dis肯定越大，所以到后面如果出现重复的，则不再添加
                {
                    vis[tmp.v[0]][tmp.v[1]] = 1;
                    q.push(tmp);
                }
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        for (int i = 0; i <= 2; i++) scanf("%d", &c[i]);
        scanf("%d", &d);
        BFS();
        while (d >= 0)
        {
            if (dist[d] >= 0)
            {
                printf("%d %d\n", dist[d], d);
                break;
            }
            d--;
        }
    }
    return 0;
}