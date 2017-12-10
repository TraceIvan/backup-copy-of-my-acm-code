//bfs + ״̬ѹ������ʼʱ��ÿһ���㶼��ӣ�ģ��3���ƴ���ÿ��״̬����� + �Ż���
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
#define N 12//���12������
#define LL long long
const int inf = 0x3fffffff;//���ֵ
int g[N][N];
int n, m, ans;
int mark[N][60000];//3^10=59064  j״̬���ߵ�i��ʱ��
struct node
{
    int x, t, s, cnt;  //λ�á�ʱ�䡢״̬������
    friend bool operator<(node a, node b)
    {
        return a.t>b.t;
    }
};
int gettmp(int x, int k)  //�õ�X��3�����µĵ�Kλ�Ƕ���
{                        //�жϸõ��Ƿ񾭹��ˣ������˼���
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
void inti()//��ʼ������
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
    priority_queue<node>q;//ʱ��С�����ȼ���
    node cur, next;
    for (i = 1; i <= n; i++)
    {//һ��ʼ��ÿ���㶼�������
        cur.x = i;
        cur.s = pow(3, (i - 1));//״̬����ʾֻ�иõ��߹�
        cur.t = 0;
        cur.cnt = 1;//��������һ��
        q.push(cur);
        mark[i][0] = 0;
    }
    while (!q.empty())
    {
        cur = q.top();
        q.pop();
        for (i = 1; i <= n; i++)
        {
            if (g[cur.x][i] == inf)  //��·��ͨ
                continue;
            next.cnt = cur.cnt;
            next.s = cur.s;
            next.t = cur.t + g[cur.x][i];
            if (ans<next.t)    //�Ż�����Ҫ
                continue;
            next.x = i;
            int t = gettmp(next.s, i);  //�õ㾭���˼��Σ�
            if (t >= 2)                 //����2�κ�Ͳ�������
                continue;
            next.s += pow(3, (i - 1));    //�õ㾭��������һ
            if (t == 0)                 //����һ���¾���
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
            g[a][b] = g[b][a] = min(g[a][b], c);//���ǵ��ر�
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
