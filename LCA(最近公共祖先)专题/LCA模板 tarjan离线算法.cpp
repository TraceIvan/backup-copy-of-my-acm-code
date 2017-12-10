#include<iostream>
#include<cstdio>
#include<vector>
#include<memory.h>
using namespace std;
const int maxn = 10005;
const int maxq = 10000;
vector<int> node[maxn];//�ڽӱ�
vector<int>query[maxn];//����ѯ��
int nstf[maxn][maxn];//�����ѯ���
int n, qnum,s;
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
        int j = pre[i];
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
    int q = query[root].size();
    for (int i = 0; i < q; i++)//�������к�root��ѯ�ʹ�ϵ�ĵ�
    {
        if (vis[query[root][i]])//��������ʹ�
        {
            nstf[root][query[root][i]] = nstf[query[root][i]][root] = f[Find(query[root][i])];
        }
    }
}
void Init()//��ʼ��
{
    for (int i = 0; i <= n; i++)
    {
        node[i].clear();
        query[i].clear();
        pre[i] = i;
    }
    memset(nstf, 0, sizeof(nstf));
    memset(vis, 0, sizeof(vis));
    memset(f, 0, sizeof(f));
}
int main()
{
    scanf("%d%d%d", &n, &qnum, &s);
    Init();
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        node[u].push_back(v);
        node[v].push_back(u);
    }
    scanf("%d", &qnum);
    pair<int, int>p;
    for (int i = 0; i < qnum; i++)
    {
        scanf("%d%d", &p.first, &p.second);
        query[p.first].push_back(p.second);
        query[p.second].push_back(p.first);
        queq[i] = p;
    }
    int root = s;
    LCA(root);
    for (int i = 0; i < qnum; i++)
    {
        printf("%d\n", nstf[queq[i].first][queq[i].second]);
    }
    return 0;
}