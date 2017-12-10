#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
#define INF 0x3f3f3f
char maze[N][N];
int mp[N][N], match[N], lx[N], ly[N], visx[N], visy[N], slack[N];
int n, m,ny,nx;
//lx,lyΪ���꣬nx,ny�ֱ�Ϊx�㼯y�㼯�ĸ���
//match�����¼�ұ�y�˵���������˵�x��visx��visy�����¼�Ƿ������ʹ���Ҳ���ж��Ƿ�������·��
struct node
{
    int a, b;
}sa[N], sb[N];
//KM�����ͼ��Сƥ��ģ�壺ֻ���Ȩֵ����ɸ��ģ�����KM������Ȩƥ�䣬Ȼ��ȡ�����Ǵ�
//ѧϰKM��ַhttp://blog.sina.com.cn/s/blog_691ce2b701016reh.html
bool dfs(int x)
{
    visx[x] = 1;
    for (int y = 1; y <= ny; y++)
    {
        if (visy[y]) continue;
        int t = lx[x] + ly[y] - mp[x][y];
        if (t == 0)//(x,y)�������ͼ��
        {
            visy[y] = 1;
            if (match[y] == -1 || dfs(match[y]))
            {//ע������Ҫ��match[y]������y����Ϊ����ֻ����x��ģ�����Ҫ����y��� 
                match[y] = x;
                return true;
            }
        }
        else if (slack[y]>t) slack[y] = t;//(x,y)���������ͼ����y���ڽ�������slack ȡ��С��
    }
    return false;
}

int KM()
{
    memset(match, -1, sizeof(match));
    memset(lx, -INF, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for (int i = 1; i <= nx; i++)
    {
        for (int j = 1; j <= ny; j++)
        {//lx��ʼ��Ϊ����������������
            if (mp[i][j]>lx[i]) lx[i] = mp[i][j];
        }
    }
    for (int x = 1; x <= nx; x++)
    {
        for (int y = 1; y <= ny; y++)
            slack[y] = INF; //ÿ�λ��µ�x��㶼Ҫ��ʼ��slack
        while (1)
        {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));//��������ʼ�������������,���ÿ��dfs()��Ҫ����
            if (dfs(x)) break;
            //���ɹ����ҵ�������죩����õ�������ɣ�������һ���������
            //��ʧ�ܣ�û���ҵ�����죩������Ҫ�ı�һЩ��ı�ţ�ʹ��ͼ�п��бߵ��������ӡ�����Ϊ����������������У���������������б���������X����ı��ȫ����ȥһ������d��������������е�Y����ı��ȫ������һ������d.
            int d = INF;
            for (int y = 1; y <= ny; y++)
            {
                if (!visy[y] && d>slack[y]) d = slack[y];
            }
            for (int x = 1; x <= nx; x++)
            {
                if (visx[x]) lx[x] -= d;
            }
            for (int y = 1; y <= ny; y++)
            {//�޸Ķ����Ҫ�����в��ڽ������е�Y�����slackֵ����ȥd,������Ϊlx[i] ��С��delta,slack[j] = min(lx[i] + ly[j] -w[i][j]) --j�����ڽ�����--Ҳ��Ҫ����delta���ڶ����
                if (visy[y]) ly[y] += d;
                else slack[y] -= d;
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= ny; i++)
    {
        if (match[i]>-1) res += mp[match[i]][i];
    }
    return res;
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        if (n + m == 0) break;
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", maze[i] + 1);
        }
        int cnt1 = 0, cnt2 = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (maze[i][j] == 'm')
                {
                    sa[++cnt1].a = i;
                    sa[cnt1].b = j;
                }
                if (maze[i][j] == 'H')
                {
                    sb[++cnt2].a = i;
                    sb[cnt2].b = j;
                }
            }
        }
        int cnt = cnt1;
        for (int i = 1; i <= cnt1; i++)
        {
            for (int j = 1; j <= cnt2; j++)
            {
                mp[i][j] = abs(sa[i].a - sb[j].a) + abs(sa[i].b - sb[j].b);
                mp[i][j] = -mp[i][j];//ȡ�������Ȩƥ�䣨Ҳ������һ������ֵ��ȥԭ����ֵ�����Ȩƥ�䣩
            }
        }
        ny = nx = cnt;
        printf("%d\n", -KM());//��ȡ����Ϊ��СȨ
    }
    return 0;
}