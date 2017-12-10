#include<iostream>
using namespace std;
int m,nx,ny;
const int maxn = 10;//x���Ϻ�y�������ĵ���
bool mp[maxn][maxn];//1��ʾ��ij����ƥ��
int cx[maxn];//��¼x������ƥ���yԪ������һ��
int cy[maxn];//��¼y������ƥ���xԪ������һ��
int vis[maxn];//��Ǹö����Ƿ���ʹ�
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
    for (int i = 0; i <= nx; i++)
        if (cx[i] == -1)//���iδƥ��
        {
            memset(vis, false, sizeof(vis));
            ans += dfs(i);
        }
    return ans;
}