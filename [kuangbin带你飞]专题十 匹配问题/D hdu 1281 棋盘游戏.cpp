#include<iostream>
#include<queue>
#include<memory.h>
using namespace std;
int n, m, k;
const int maxr = 110;//�������
const int maxc = 110;//�������
const int maxk = 10010;//���ɷ�λ��
bool mp[maxr][maxc];//1��ʾ��ij����ƥ��
int cx[maxc];//��¼x������ƥ���yԪ������һ��
int cy[maxr];//��¼y������ƥ���xԪ������һ��
int vis[maxr];//��Ǹö����Ƿ���ʹ�
struct point
{
    int x;
    int y;
}points[maxk];
bool dfs(int u)
{
    for (int v = 1; v <= m; v++)
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
    return ans;
}

int main()
{
    int Case = 1;
    while (~scanf("%d%d%d", &n, &m, &k))
    {
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= k; i++)
        {
            scanf("%d%d", &points[i].x, &points[i].y);
            mp[points[i].x][points[i].y] = 1;
        }
        int ans = maxmatch();
        int import = 0;
        for (int i = 1; i <= k; i++)
        {
            mp[points[i].x][points[i].y] = 0;
            int tmp = maxmatch();
            mp[points[i].x][points[i].y] = 1;
            if (tmp < ans) import++;
        }
        printf("Board %d have %d important blanks for %d chessmen.\n", Case++, import, ans);
    }

    return 0;
}