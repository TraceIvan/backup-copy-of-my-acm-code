#include<iostream>
#include<cstdio>
#include<vector>
#include<memory.h>
using namespace std;
const int maxn = 10010;
const int maxq = 10;
vector<int> node[maxn];//�ڽӱ�
int q1, q2, ans;
int n, qnum;
int index[maxn];//���
int pre[maxn];//���鼯
bool vis[maxn];//����Ƿ���ʹ�
pair<int, int>queq[maxq];//�����ѯ˳��
int f[maxn];//������ʱ����
int Find(int x)
{
    int r = x;
    while (pre[r] != r)
    {
        r = pre[r];
    }
    int i = x, j;
    while (i != r)
    {
        j = pre[i];
        if (j != r) pre[i] = r;
        i = j;
    }
    return r;
}
void Join(int root, int child)
{
    int rx = Find(root), ry = Find(child);
    if (rx != ry) pre[child] = root;
}
void LCA(int root)
{
    f[Find(root)] = root;
    vis[root] = true;//��Ǳ����ʹ�
    int sz = node[root].size();
    for (int i = 0; i < sz; i++)
    {//��������root�ӽڵ�
        if (!vis[node[root][i]])
        {
            LCA(node[root][i]);//�������±���
            Join(root, node[root][i]);//�ϲ�
            f[Find(root)] = root;
        }
    }
    if (q1 == root&&vis[q2]) ans = f[Find(q2)];
    else if (q2 == root&&vis[q1]) ans = f[Find(q1)];
}
void Init()//��ʼ��
{
    for (int i = 0; i <= n; i++)
    {
        node[i].clear();
        pre[i] = i;
    }
    memset(vis, 0, sizeof(vis));
    memset(f, 0, sizeof(f));
    memset(index, 0, sizeof(index));
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        Init();
        for (int i = 1; i <= n - 1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            node[u].push_back(v);//����ͼ
            index[v]++;
        }
        scanf("%d%d", &q1, &q2);
        int root = 1;
        for (; root <= n; root++) if (!index[root]) break;//���Ϊ0��Ϊ��
        LCA(root);
        printf("%d", ans);
        printf("\n");
    }
    return 0;
}