//����DP
//f(i,j)��ʾ��iյ�Ƶĸ����Ƿ��������j=0|1������׷��ˣ���ô�Լ��Ż��߲��Ŷ�������ôf(i,j)=max{��f(ison,0)��f(ison,1)}���������û�з��ã���ô�Լ��������ôf(i,0)=��f(ison,1)�������ʱ��Ҫ�ñ����������εı߾����࣬��ôӦ���ñ�����һ�εı߾������٣���ô��m=n��x+yx�����ǵ�ǰ�������ĵƵ�������y����ǰ�����и�����ɵ����ٵı�����һ�εıߵ�����ǰ������y�����ֵС��n��ô����x�ͳ�Ϊ����Ҫ��Ҫ��Ȩֵ��y�Ǵ�Ҫ��Ȼ��dp���̸�һ��

//f(i, 0) = (��f(ison, 1)) + 1
//��1����Ϊ�Լ����Լ��ĸ�������һ���߱�����һ�����Լ�1��
//f(i, 1) = max{ (��f(ison,0)) + 1,��f(ison,1) }
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
//�Ż�x=M*v1+v2������M�Ǳ�"��v2���������ֵ��v2����С����ֵ֮��"��Ҫ�������v1��ʾ���õ�·����Ŀ������С��v2��ʾ��һյ��������·������С��v1=x/M,v2=x%M,v3=m-v2.(����յ��������·)
int root;
const int m = 2000;//�����۵�M

struct EdgeNode
{
    int to, next;
} E[2 * EDGENUM];
int edgenum, head[NODENUM], N, T, M;
bool vis[NODENUM];
int ans;
int dp[NODENUM][2];//[0]��ʾ���ŵƣ�[1]��ʾ�ŵ�

void init()
{
    edgenum = 0;//·����Ϊ0
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
//ÿ��һյ�� + 2000(m)����Ϊ�ߵ��������Ϊ1000����ÿ����1������һ�εı� + 1.
//����һ���ڵ�i�����Žֵƣ���ôi�Ǹ����߸��׽ڵ���˽ֵơ�����dp(i,j)=sum{ dp(v,0) | vȡ��i�����ж��ӽڵ� }�����i���Ǹ��ڵ㣬��ô���+1����Ϊi�͸������ӵ�������ֻ��һյ��������
//���߶����ڵ�i���Žֵƣ�dp(i, j) = sum{ dp(v,1) | vȡ��i�����ж��ӽڵ� } +M�����i���Ǹ��ڵ����j = 0����ô��� + 1��
void build()
{
    scanf("%d%d", &N, &M);
    for (int i = 0; i<M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);//�����
        add(b, a);
    }
}

int main()
{
    scanf("%d", &T);//��������
    while (T--)
    {
        init();
        build();
        for (int i = 0; i<N; ++i) if (!vis[i]) dfs(root = i);//�����ж����
        printf("%d %d %d\n", ans / m, M - ans%m, ans%m);
    }
    return 0;
}