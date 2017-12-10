#include<iostream>
#include<queue>
#include<memory.h>
using namespace std;
int n, p;
const int maxn = 310;//���ѧ����
const int maxp = 110;//���ѧ����
bool mp[maxp][maxn];//1��ʾ��ij����ƥ��
int cx[maxp];//��¼x������ƥ���yԪ������һ��
int cy[maxn];//��¼y������ƥ���xԪ������һ��
int vis[maxn];//��Ǹö����Ƿ���ʹ�
bool dfs(int u)
{
    for (int v = 1; v <= n; v++)
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
    for (int i = 1; i <= p; i++)
        if (cx[i] == -1)//���iδƥ��
        {
            memset(vis, 0, sizeof(vis));
            ans += dfs(i);
        }
    return ans;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &p, &n);
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= p; i++)
        {
            int count;
            scanf("%d", &count);
            for (int j = 1; j <= count; j++)
            {
                int v;
                scanf("%d", &v);
                mp[i][v] = true;
            }
       }
        int ans = maxmatch();
        if (ans < p)printf("NO\n");
        else printf("YES\n");
    }

    return 0;
}