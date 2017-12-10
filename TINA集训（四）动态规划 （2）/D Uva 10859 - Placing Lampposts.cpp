//树形DP
//f(i,j)表示第i盏灯的父亲是否点亮所以j=0|1如果父亲放了，那么自己放或者不放都可以那么f(i,j)=max{∑f(ison,0)∑f(ison,1)}，如果父亲没有放置，那么自己必须放那么f(i,0)=∑f(ison,1)但是这个时候要让被灯照亮两次的边尽量多，那么应该让被照亮一次的边尽量的少，那么另m=n×x+yx代表覆盖当前的子树的灯的数量，y代表当前子树中覆盖完成的最少的被照亮一次的边的数量前提是让y的最大值小于n那么这样x就成为了首要重要的权值，y是次要的然后dp方程改一下

//f(i, 0) = (∑f(ison, 1)) + 1
//加1是因为自己和自己的父亲又有一条边被照亮一次所以加1，
//f(i, 1) = max{ (∑f(ison,0)) + 1,∑f(ison,1) }
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#define INF 0x3f3f3f3f
#define NODENUM 1005
#define EDGENUM 1005
#define MAXN 1005
using namespace std;
//优化x=M*v1+v2，其中M是比"比v2的最大理论值和v2的最小理论值之差"还要大的数。v1表示放置的路灯数目尽可能小，v2表示被一盏灯照亮的路尽可能小。v1=x/M,v2=x%M,v3=m-v2.(被两盏灯照亮的路)
int root;
const int m = 2000;//即理论的M

struct EdgeNode
{
    int to, next;
} E[2 * EDGENUM];
int edgenum, head[NODENUM], N, T, M;
bool vis[NODENUM];
int ans;
int dp[NODENUM][2];//[0]表示不放灯，[1]表示放灯

void init()
{
    edgenum = 0;//路条数为0
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    ans = 0;
}

void add(int x, int y)
{
    edgenum++;
    E[edgenum].next = head[x];
    head[x] = edgenum;
    E[edgenum].to = y;
}

void dfs(int s)
{
    vis[s] = 1;
    int sum0 = 0, sum1 = 0;

    for (int p = head[s]; p != -1; p = E[p].next)
    {
        int v = E[p].to;
        if (!vis[v])
        {
            dfs(v);
            sum0 += dp[v][0];
            sum1 += dp[v][1];
        }
    }
    if (s == root) dp[s][0] = min(sum1 + m, sum0), ans += dp[s][0];
    else dp[s][1] = min(sum0 + 1, sum1 + m), dp[s][0] = sum1 + m + 1;
}
//每放一盏灯 + 2000(m)（因为边的最大数量为1000），每增加1条照亮一次的边 + 1.
//决策一：节点i处不放街灯，那么i是根或者父亲节点放了街灯。所以dp(i,j)=sum{ dp(v,0) | v取遍i的所有儿子节点 }，如果i不是根节点，那么结果+1，因为i和父亲连接的这条边只被一盏灯照亮。
//决策二：节点i处放街灯，dp(i, j) = sum{ dp(v,1) | v取遍i的所有儿子节点 } +M，如果i不是根节点而且j = 0，那么结果 + 1。
void build()
{
    scanf("%d%d", &N, &M);
    for (int i = 0; i<M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);//无向边
        add(b, a);
    }
}

int main()
{
    scanf("%d", &T);//测试用例
    while (T--)
    {
        init();
        build();
        for (int i = 0; i<N; ++i) if (!vis[i]) dfs(root = i);//可能有多颗树
        printf("%d %d %d\n", ans / m, M - ans%m, ans%m);
    }
    return 0;
}