#include<iostream>
#include<queue>
#include<memory.h>
#include<algorithm>
using namespace std;
int n;
const int maxr = 110;//�������
const int maxc = 110;//�������
const int maxk = 1010;//���ɷ�λ��
bool mp[maxr][maxc];//1��ʾ��ij����ƥ��
int cx[maxc];//��¼x������ƥ���yԪ������һ��
int cy[maxr];//��¼y������ƥ���xԪ������һ��
int vis[maxr];//��Ǹö����Ƿ���ʹ�
struct stp
{
    int x;
    int y;
}stps[maxk];
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
    while (~scanf("%d", &n))
    {
        memset(mp, 0, sizeof(mp));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int v;
                scanf("%d", &v);
                if (v > 0) mp[i][j] = 1;
            }
        }
        int ans = maxmatch();
        if (ans < n)printf("-1\n");
        else
        {
            int t = 0;
            for (int i = 1; i <= n; i++)
            {
                int j;
                for (j = 1; j <= n; j++) if (cy[j] == i)break;
                if (i != j)
                {
                    stps[t].x = i, stps[t].y = j;
                    t++;
                    swap(cy[i], cy[j]);
                }
            }
            printf("%d\n", t);
            for (int i = 0; i < t; i++)
            {
                printf("C %d %d\n", stps[i].x, stps[i].y);
            }
        }
    }

    return 0;
}