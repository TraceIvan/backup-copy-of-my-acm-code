#include<iostream>
#include<queue>
using namespace std;
int n,m;
const int maxn = 210;//x���Ϻ�y���������ĵ���
bool mp[maxn][maxn];//1��ʾ��ij����ƥ��
int cx[maxn];//��¼x������ƥ���yԪ������һ��
int cy[maxn];//��¼y������ƥ���xԪ������һ��
int vis[maxn];//��Ǹö����Ƿ���ʹ�
int cntx;
bool dfs(int u)
{
    for (int v = 1; v <= n; v++)//���������ڹ���n��Ԫ��
    {
        if (mp[u][v] && !vis[v])
        {
            vis[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))//)//���y�����е�vԪ��û��ƥ�������v�Ѿ�ƥ�䣬���Ǵ�cy[v]���ܹ��ҵ�һ������·
            {
                cx[u] = v; cy[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
int maxmatch()//�������㷨������
{
    int ans = 0;
    memset(cx, 0xff, sizeof cx);//��ʼֵΪ-1��ʾ���������ж�û��ƥ���Ԫ�أ�
    memset(cy, 0xff, sizeof cy);
    for (int i = 1; i <= n; i++)
        if (cx[i] == -1)//���iδƥ��
        {
            memset(vis, 0, sizeof(vis));
            ans += dfs(i);
        }
    return ans/2;//����������Ķ�ƥ���ˣ��������൱��ƥ����������  
}
bool istwo()
{//�ж��Ƿ�Ϊ����ͼ
    queue<int>q;
    memset(vis, 0, sizeof(vis));
    q.push(1);
    vis[1] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 1; i <= n; i++)
        {
            if (mp[u][i])
            {
                if (vis[i] == 0)
                {
                    if (vis[u] == 1) vis[i] = 2;
                    else vis[i] = 1;
                    q.push(i);
                }
                else
                {
                    if (vis[i] == vis[u]) return false;
                }
            }
        }
    }
    return true;
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        memset(mp ,0, sizeof(mp));
        while (m--)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            mp[a][b] = mp[b][a] = 1;
        }
        if (!istwo()|| n == 1)
        {
            printf("No\n");
        }
        else
        {
            int ans = maxmatch();
            printf("%d\n", ans);
        }
    }

    return 0;
}