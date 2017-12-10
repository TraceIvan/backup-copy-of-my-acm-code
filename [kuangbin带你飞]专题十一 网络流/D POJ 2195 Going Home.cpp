#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
#define INF 0x3f3f3f
char maze[N][N];
int mp[N][N], match[N], lx[N], ly[N], visx[N], visy[N], slack[N];
int n, m,ny,nx;
//lx,ly为顶标，nx,ny分别为x点集y点集的个数
//match数组记录右边y端点所连的左端点x，visx，visy数组记录是否曾访问过，也是判断是否在增广路上
struct node
{
    int a, b;
}sa[N], sb[N];
//KM求二分图最小匹配模板：只需把权值都变成负的，再用KM算出最大权匹配，然后取反就是答案
//学习KM地址http://blog.sina.com.cn/s/blog_691ce2b701016reh.html
bool dfs(int x)
{
    visx[x] = 1;
    for (int y = 1; y <= ny; y++)
    {
        if (visy[y]) continue;
        int t = lx[x] + ly[y] - mp[x][y];
        if (t == 0)//(x,y)在相等子图中
        {
            visy[y] = 1;
            if (match[y] == -1 || dfs(match[y]))
            {//注意这里要搜match[y]而不是y，因为我们只搜索x侧的，不需要搜索y侧的 
                match[y] = x;
                return true;
            }
        }
        else if (slack[y]>t) slack[y] = t;//(x,y)不在相等子图中且y不在交错树中slack 取最小的
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
        {//lx初始化为与它关联边中最大的
            if (mp[i][j]>lx[i]) lx[i] = mp[i][j];
        }
    }
    for (int x = 1; x <= nx; x++)
    {
        for (int y = 1; y <= ny; y++)
            slack[y] = INF; //每次换新的x结点都要初始化slack
        while (1)
        {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));//这两个初始化必须放在这里,因此每次dfs()都要更新
            if (dfs(x)) break;
            //若成功（找到了增广轨），则该点增广完成，进入下一个点的增广
            //若失败（没有找到增广轨），则需要改变一些点的标号，使得图中可行边的数量增加。方法为：将所有在增广轨中（就是在增广过程中遍历到）的X方点的标号全部减去一个常数d，所有在增广轨中的Y方点的标号全部加上一个常数d.
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
            {//修改顶标后，要把所有不在交错树中的Y顶点的slack值都减去d,这是因为lx[i] 减小了delta,slack[j] = min(lx[i] + ly[j] -w[i][j]) --j不属于交错树--也需要减少delta，第二类边
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
                mp[i][j] = -mp[i][j];//取反求最大权匹配（也可以用一个极大值减去原来的值求最大权匹配）
            }
        }
        ny = nx = cnt;
        printf("%d\n", -KM());//再取反则为最小权
    }
    return 0;
}