#include<iostream>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
int n, m;
const int maxn = 210;//x���Ϻ�y���������ĵ���
bool mp[maxn][maxn];//1��ʾ��ij����ƥ��
int cx[maxn];//��¼x������ƥ���yԪ������һ��
int cy[maxn];//��¼y������ƥ���xԪ������һ��
int vis[maxn];//��Ǹö����Ƿ���ʹ�
int cntx;
bool dfs(int u)
{
    for (int v = m+1; v <= n; v++)
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
    for (int i = 1; i <= m; i++)
        if (cx[i] == -1)//���iδƥ��
        {
            memset(vis, 0, sizeof(vis));
            ans += dfs(i);
        }
    return ans; 
}

int main()
{
    while (~scanf("%d%d", &m, &n))
    {
        memset(mp, 0, sizeof(mp));
        int a, b;
        while (scanf("%d%d", &a, &b))
        {
            if (a == -1 && b == -1)break;
            mp[a][b] = mp[b][a] = 1;
        }

        int ans = maxmatch();
        if(ans>0)printf("%d\n", ans);
        else printf("No Solution!\n");

    }

    return 0;
}