//Ford-Fulkerson方法
//为什么叫Ford-Fulkerson方法而不是算法，原因在于可以用多种方式实现这一方法，
//方式并不唯一。
//下面介绍一种基于广度优先搜索(BFS)来计算增广路径P的算法：Edmonds-Karp算法。
#include <iostream>
#include <conio.h>
#include <limits>
#include <queue>

using namespace std;

const int N = 210;
const int INF = INT_MAX; //无穷大
int n, m, map[N][N], prepath[N], flow[N], start, End;
queue<int> q;   //先进先出队列——用于表达节点搜索顺序

                //广度优先搜索
int bfs()
{
    int i, t;
    while (!q.empty()) q.pop();
    memset(prepath, -1, sizeof(prepath));
    prepath[start] = 0;
    flow[start] = INF;
    q.push(start);
    while (!q.empty())
    {
        t = q.front();				//取队列的首元素
        q.pop();					//把队列首元素弹出
        if (t == End) break;
        cout << "bfs path=";
        for (i = 1; i <= m; i++)
        {
            if (i != start && prepath[i] == -1 && map[t][i])
            {
                flow[i] = flow[t] < map[t][i] ? flow[t] : map[t][i];
                q.push(i);
                prepath[i] = t;
                cout << t << ", ";
            }
        }
        cout << endl;
    }
    if (prepath[End] == -1)
        return -1;
    return flow[End];                   //一次遍历之后的流量增量
}

int Edmonds_Karp()
{
    int max_flow = 0, step, now, pre;
    while (true)
    {
        step = bfs();
        if (step == -1) break;		//找不到增路径时退出
        max_flow += step;
        now = End;
        while (now != start)
        {
            pre = prepath[now];
            map[pre][now] -= step;      //更新正向边的实际容量
            map[now][pre] += step;      //添加反向边
            now = pre;
        }
    }
    return max_flow;
}

int main()
{
    //用邻接矩阵表示图的邻接关系，初始化所有权重为0
    memset(map, 0, sizeof(map));

    n = 5;    //边的数量
    m = 4;    //节点数量：这里为查看方便，节点编号从1~4编号	

              //图的连接关系与边的容量数据
    float edgeCosts[][3] = { { 1, 2, 40 },{ 1, 4, 20 },{ 2, 4, 20 },{ 2, 3, 30 },{ 3, 4, 10 } };
    for (int i = 0; i < n; i++)
        map[(int)edgeCosts[i][0]][(int)edgeCosts[i][1]] = edgeCosts[i][2];

    start = 1;    //搜索源点
    End = m;      //搜索汇点

                  //计算图的最大流
    int maxflow = Edmonds_Karp();			//计算最大流
    printf("网络的最大流=%d\n", maxflow);	//输出
    getch();
    return 0;
}