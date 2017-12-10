#include<iostream>
#include<memory.h>
#include<queue>
using namespace std;
int m, n, k, d;//行数，列数，炮塔数，总能量
const int maxn = 105;
const int maxt = 1005;
bool iscan[maxn][maxn][maxt];//第i行第j列第dt时间能不能通过
bool vis[maxn][maxn][maxt];//第i行第j列第dt时间是否曾经走过
struct node
{
    int r;
    int c;
    int t;
    node(int rr=0,int cc=0,int tt=0):r(rr),c(cc),t(tt){ }
};

bool ppos[maxn][maxn];//第i行第j列是否有炮塔

int dr[] = { 0,0,0,-1,1 };
int dc[] = { 0,1,-1,0,0 };
struct pao
{
    int r;
    int c;
    int v;//子弹速度
    int period;//周期
    char dir;//朝向'N'上'S'下'W'左'E'右
}Pao[maxn];
void Init()//初始化iscan数组
{
    memset(vis, 0, sizeof(vis));
    memset(iscan, true, sizeof(iscan));
    memset(ppos, 0, sizeof(ppos));
    pao temp;
    char op[3];
    for (int i = 0; i < k; i++)
    {
        scanf("%s%d%d%d%d", &op, &temp.period, &temp.v, &temp.r, &temp.c);
        temp.dir = op[0];
        ppos[temp.r][temp.c] = true;
        Pao[i] = temp;
    }
    memset(iscan[0][0], false, sizeof(iscan[0][0]));//敌人大本营肯定不能待
    for (int i = 0; i < k; i++)
    {//分别对每个炮塔进行初始化
        pao p = Pao[i];
        memset(iscan[p.r][p.c], false , sizeof(iscan[p.r][p.c]));
        bool flag = false;
        //先判断在朝向上有无炮塔
        int edr = 0, edc=0;
        switch (p.dir)//找到子弹能够射的距离
        {
        case 'N':
            edc = p.c;
            for (edr = p.r - 1; edr >= 0; edr--) if (ppos[edr][edc])break;
            if (edr < 0)edr = 0;
            for (int ps = p.r - p.v,init=1; ps >= edr;init++, ps -= p.v)
            {//枚举位置
                for (int t = init; t <= d; t += p.period) iscan[ps][p.c][t] = false;
            }
            break;
        case 'S':
            edc = p.c;
            for (edr = p.r + 1; edr <= m; edr++)if (ppos[edr][edc])break;
            if (edr > m) edr = m;
            for (int ps = p.r + p.v, init = 1; ps <= edr; init++, ps += p.v)
            {//枚举位置
                for (int t = init; t <= d; t += p.period) iscan[ps][p.c][t] = false;
            }
            break;
        case 'W':
            edr = p.r;
            for (edc = p.c - 1; edc >= 0; edc--)if (ppos[edr][edc])break;
            if (edc < 0)edc = 0;
            for (int ps = p.c-p.v, init = 1; ps >= edc; init++, ps -= p.v)
            {//枚举位置
                for (int t = init; t <= d; t += p.period) iscan[p.r][ps][t] = false;
            }
            break;
        case 'E':
            edr = p.r;
            for (edc = p.c + 1; edc <=n; edc++)if (ppos[edr][edc])break;
            if (edc > n)edc = n;
            for (int ps = p.r + p.v, init = 1; ps <= edr; init++, ps += p.v)
            {//枚举位置
                for (int t = init; t <= d; t += p.period) iscan[p.r][ps][t] = false;
            }
            break;
        }   
    }
}
void BFS()
{
    queue<node>q;
    q.push(node(0, 0,0));
    vis[0][0][0] = true;
    while (!q.empty())
    {
        node u = q.front();
        q.pop();
        if (u.r == m&&u.c == n)
        {
            printf("%d\n", u.t);
            return;
        }
        for (int i = 0; i < 5; i++)
        {
            int tr = u.r + dr[i];
            int tc = u.c + dc[i];
            int tt = u.t + 1;
            if (tr <= m&&tr >= 0 && tc <= n&&tc >= 0)
            {//没有超范围
                if (!ppos[tr][tc]&&!vis[tr][tc][tt] && iscan[tr][tc][tt]&&tt<=d)
                {//没有访问过且能够走
                    q.push(node(tr, tc, tt));
                    vis[tr][tc][tt] = true;
                }
            }
        }
    }
    printf("Bad luck!\n");
}
int main()
{
    while (~scanf("%d%d%d%d", &m, &n, &k, &d))
    {
        Init();
        BFS();
    }
    return 0;
}