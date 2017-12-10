#include<iostream>
#include<queue>
#include<set>
using namespace std;
int st[4][8];
long long qz[32];
int des[4][8] = 
{
    {11,12,13,14,15,16,17,0},
    {21,22,23,24,25,26,27,0},
    {31,32,33,34,35,36,37,0},
    {41,42,43,44,45,46,47,0}
};
int pos[4][2];
set<long long>vis;
int ans;

void Pre()
{
    qz[0] = 1;
    for (int i = 1; i < 32; i++) qz[i] = qz[i - 1] * 2;
}

long long Hush(int (*s)[8])
{
    long long ans = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++) ans +=1ll*qz[i * 8 + j] * s[i][j];
    }
    return ans;
}

struct node
{
    int p[4][2];//存0的位置
    int s[4][8];//存状态
    int step;//存步数
};
int BFS()
{
    queue<node>q;
    node start;
    memcpy(start.p, pos, sizeof(pos));
    memcpy(start.s, st, sizeof(st));
    start.step = 0;
    q.push(start);
    long long v = Hush(st);
    vis.insert(v);
    while (!q.empty())
    {
        node u = q.front();
        q.pop();
        if (memcmp(u.s, des, sizeof(des)) == 0)
        {
            return u.step;
        }
        int tp[4][2];
        int ts[4][8];
        for (int i = 0; i < 4; i++)
        {
            memcpy(tp, u.p, sizeof(tp));
            memcpy(ts, u.s, sizeof(ts));
            int r = tp[i][0];
            int c = tp[i][1];
            int lv = ts[r][c - 1];
            if (lv % 10 == 7||lv==0)continue;
            int desr, desc;
            int flag = true;
            for (int i = 0; flag&&i < 4; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (ts[i][j] == lv + 1)
                    {
                        desr = i;
                        desc = j;
                        flag = false;
                    }
                }
            }
            if (flag)continue;
            ts[r][c] = lv + 1;
            ts[desr][desc] = 0;
            tp[i][0] = desr;
            tp[i][1] = desc;
            long long tv = Hush(ts);
            if (!vis.count(tv))
            {
                vis.insert(tv);
                node t;
                memcpy(t.p, tp, sizeof(tp));
                memcpy(t.s, ts, sizeof(ts));
                t.step = u.step + 1;
                q.push(t);
            }
        }
    }
    return -1;
}
void Run()
{
    vis.clear();
    int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 8; j++)
        {
            scanf("%d", &st[i][j]);
            if (st[i][j] % 10 == 1)
            {
                st[st[i][j] / 10-1][0] = st[i][j];
                st[i][j] = 0;
                pos[cnt][0] = i;
                pos[cnt][1] = j;
                cnt++;
            }
        }
    }
    if (memcmp(st, des, sizeof(des))==0) printf("0\n");
    else printf("%d\n", BFS());
}
int main()
{
    Pre();
    int t;
    scanf("%d", &t);
    while (t--)
    {
        Run();
    }
    return 0;
}