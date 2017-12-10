#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxm = 15;
const int maxn = 55;
const int INF = 0x3f3f3f3f;
int mp[maxn][maxn*maxm],lx[maxn],ly[maxn*maxm],slack[maxn*maxm],match[maxn*maxm],visx[maxn],visy[maxn*maxm];
int m, n,nx,ny;

int totmem[maxm];
struct node
{
    int k, mem[maxm], tm[maxm];
}pg[maxn];

struct re
{
    int id, l, r;
}result[maxn];
bool dfs(int x)
{
    visx[x] = 1;
    for (int y = 1; y <= ny; y++)
    {
        if (visy[y])continue;
        int t = lx[x] + ly[y] - mp[x][y];
        if (t == 0)
        {
            visy[y] = 1;
            if (match[y] == -1 || dfs(match[y]))
            {
                match[y] = x;
                return true;
            }
        }
        else if (slack[y] > t) slack[y] = t;
    }
    return false;
}

void KM()
{
    memset(match, -1, sizeof(match));
    memset(lx, -INF, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for (int i = 1; i <= nx; i++)
    {
        for (int j = 1; j <= ny; j++)
        {
            if (mp[i][j] > lx[i]) lx[i] = mp[i][j];
        }
    }

    for (int x = 1; x <= nx; x++)
    {
        for (int y = 1; y <= ny; y++) slack[y] = INF;
        while (1)
        {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));

            if (dfs(x)) break;
            int d = INF;
            for (int y = 1; y <= ny; y++)
            {
                if (!visy[y] && d > slack[y]) d = slack[y];
            }
            for (int xx = 1; xx <= nx; xx++)
            {
                if (visx[xx]) lx[xx] -= d;
            }
            for (int y = 1; y <= ny; y++)
            {
                if (visy[y]) ly[y]+= d;
                else slack[y] -= d;
            }
        }
    }
}

void Oput()
{
    int ans = 0;
    for (int i = 1; i <= nx; i++) ans += lx[i];
    for (int i = 1; i <= ny; i++) ans += ly[i];
    printf("Average turnaround time = %.2lf\n", n?-1.0*ans / n:0);
    int time[11];//记录每个内存当前运行结束时间
    memset(time, 0, sizeof(time));
    for (int i = 1; i <= m; i++)
    {//枚举内存
        int p;
        for (p = 1; p <= n; p++) if (match[(i - 1)*n + p]==-1) break;//找到该内存的第一个程序位置
        for (p = p - 1; p >= 1; --p)
        {
            int x = match[(i - 1)*n + p];//所对应的程序
            result[x].id = i;//程序所对应的内存
            result[x].l = time[i];
            time[i] += (-mp[x][(i - 1)*n + p] / p);
            result[x].r = time[i];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("Program %d runs in region %d from %d to %d\n", i, result[i].id, result[i].l, result[i].r);
    }
}


int main()
{
    int Case = 1;
    while (~scanf("%d%d", &m, &n)&&n&&m)
    {
        for (int i = 1; i <= m; i++) scanf("%d", &totmem[i]);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &pg[i].k);
            for (int j = 1; j <= pg[i].k; j++) scanf("%d%d", &pg[i].mem[j], &pg[i].tm[j]);
        }
        for (int i = 1; i <= n; i++)
        {//枚举当前程序
            for (int j = 1; j <= m; j++)
            {//枚举当前内存
                int tmp;//在当前内存的运行时间
                if (totmem[j] < pg[i].mem[1]) tmp = INF;
                else
                {
                    int pos;
                    for (pos = 1; pos <= pg[i].k; pos++)
                    {
                        if (pg[i].mem[pos] > totmem[j]) break;
                    }
                    tmp = pg[i].tm[pos - 1];
                }
                for (int k = 1; k <= n; k++)
                {//当前程序在当前内存是倒数第k个程序，则对总时间的贡献为k*tmp
                    if (tmp == INF) mp[i][(j - 1)*n + k] = -INF;
                    else mp[i][(j - 1)*n + k] = -k*tmp;//求最小权匹配，取负
                }
            }
        }
        nx = n, ny = n*m;
        KM();
        if (Case > 1) printf("\n");
        printf("Case %d\n", Case++);
        Oput();
    }
    return 0;
}