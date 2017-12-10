#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
int c[3], d;
const int maxv = 210;
int dist[maxv];//�õ�����Ϊi���ٵĵ�ˮ���
bool vis[maxv][maxv];//��ʾa��b��c״̬Ϊi��j��d-i-j�Ƿ���ʹ�
struct node
{
    int dis;//�ӿ�ʼ����ǰ�ѵ�����ˮ�����
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
                if (!vis[tmp.v[0]][tmp.v[1]])//���ڿ϶���Խ����dis�϶�Խ�����Ե�������������ظ��ģ��������
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