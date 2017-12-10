#include<iostream>
#include<cstdio>
#include<queue>
#include<memory.h>
using namespace std;
int S, N, M;
struct node
{
    int s;
    int n;
    int m;
    int step;
    node(int ss=0,int nn=0,int mm=0,int st=0):s(ss),n(nn),m(mm),step(st){ }
};
bool vis[110][110][110];
int main()
{
    while (~scanf("%d%d%d", &S, &N, &M))
    {
        if (S == 0 && N == 0 && M == 0) break;
        if (S % 2 == 1)
        {
            printf("NO\n");
            continue;
        }
        memset(vis, 0, sizeof(vis));
        queue<node>q;
        q.push(node(S, 0, 0, 0));
        vis[S][0][0] = true;
        bool flag = false;
        int ans;
        while (!q.empty())
        {
            node t = q.front();
            q.pop();
            if ((t.s == S / 2 && t.n == S / 2) || (t.s == S / 2 && t.m == S / 2) || (t.n == S / 2 && t.m == S / 2))
            {
                flag = true;
                ans = t.step;
                break;
            }
            if (t.s)
            {
                int ts = (t.s - (N - t.n) >= 0 ? t.s - (N - t.n) : 0);
                int tn = (t.s - (N - t.n) >= 0 ? N : t.s + t.n);
                if (!vis[ts][tn][t.m]) q.push(node(ts, tn, t.m, t.step + 1)),vis[ts][tn][t.m]=true;
                ts = (t.s - (M - t.m) >= 0 ? t.s - (M - t.m) : 0);
                int tm = (t.s - (M - t.m) >= 0 ? M : t.s + t.m);
                if (!vis[ts][t.n][tm]) q.push(node(ts, t.n, tm, t.step + 1)), vis[ts][t.n][tm] = true;
            }
            if (t.n)
            {
                int tn = 0, ts = t.s + t.n;
                if (!vis[ts][tn][t.m]) q.push(node(ts, tn, t.m, t.step + 1)), vis[ts][tn][t.m] = true;
                tn = (t.n - (M - t.m) >= 0 ? t.n - (M - t.m) : 0);
                int tm = (t.n - (M - t.m) >= 0 ? M : t.n + t.m);
                if (!vis[t.s][tn][tm])q.push(node(t.s, tn, tm, t.step + 1)), vis[t.s][tn][tm] = true;
            }
            if (t.m)
            {
                int tm = 0, ts = t.s + t.m;
                if (!vis[ts][t.n][tm])q.push(node(ts, t.n, tm, t.step + 1)), vis[ts][t.n][tm] = true;
                tm = (t.m - (N - t.n) >= 0 ? t.m - (N - t.n) : 0);
                int tn = (t.m - (N - t.n) >= 0 ? N : t.m + t.n);
                if (!vis[t.s][tn][tm])q.push(node(t.s, tn, tm, t.step + 1)), vis[t.s][tn][tm] = true;
            }
        }
        if (flag)printf("%d\n", ans);
        else printf("NO\n");
    }


    return 0;
}