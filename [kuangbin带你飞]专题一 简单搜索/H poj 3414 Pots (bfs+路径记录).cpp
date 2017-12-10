#include<iostream>
#include<queue>
#include<memory.h>
#include<cstdio>
using namespace std;
int A, B, C;
struct opt
{
    int a;
    int b;
    char op;
    char from;
    char to;
    int pre;
    int cnt;
    opt(int aa=0,int bb=0,char opp='f',char fr='0',char too='1',int pr=0,int ct=0):a(aa),b(bb),op(opp),from(fr),to(too),pre(pr),cnt(ct){ }
};
bool vis[110][110];
opt ed;
opt q[1000005];
void Print(int id)
{
    if (id != 0)
    {
        Print(q[id].pre);
        switch (q[id].op)
        {
        case 'd':printf("DROP(%c)\n", q[id].from);
            break;
        case 'f':printf("FILL(%c)\n", q[id].from);
            break;
        case 'p':printf("POUR(%c,%c)\n", q[id].from, q[id].to);
        }
    }
}
int main()
{
    while (~scanf("%d%d%d", &A, &B, &C))
    {
        memset(vis, 0, sizeof(vis));
        memset(q, 0, sizeof(q));
        vis[0][0] = true;
        int first = 0;
        int len = 1;
        bool flag = false;
        while (first<len)
        {
            opt t = q[first];
            first++;
            if (t.a == C || t.b == C)
            {
                flag = true;
                ed = t;
                break;
            }
            if (t.a == 0 && t.b == 0)
            {
                if(!vis[A][0])q[len++]=opt(A, 0,'f','1','1',first-1,t.cnt+1),vis[A][0]=true;
                if(!vis[0][B])q[len++]=opt(0, B, 'f', '2','2', first - 1, t.cnt + 1),vis[0][B]=true;
            }
            else if(t.a==0)
            {
                int ta = min(A,t.b), tb = (min(A, t.b) == A ? t.b - A : 0);
                if(!vis[ta][tb])q[len++]=opt(ta,tb, 'p', '2', '1', first - 1, t.cnt + 1),vis[ta][tb]=true;
                if(!vis[A][t.b])q[len++]=opt(A, t.b, 'f', '1', '1', first - 1, t.cnt + 1),vis[A][t.b]=true;
                if(!vis[0][B])q[len++]=opt(0, B, 'f', '2', '2', first - 1, t.cnt + 1),vis[0][B]=true;
            }
            else if (t.b == 0)
            {
                int ta = (min(t.a, B) == t.a ? 0 : t.a - B),tb= min(t.a, B);
                if(!vis[ta][tb])q[len++]=opt(ta,tb, 'p', '1', '2', first - 1, t.cnt + 1),vis[ta][tb]=true;
                if (!vis[t.a][B])q[len++]=opt(t.a,B, 'f', '2', '2', first - 1, t.cnt + 1), vis[t.a][B] = true;
                if (!vis[A][0])q[len++]=opt(A, 0, 'f', '1', '1', first - 1, t.cnt + 1), vis[A][0] = true;
            }
            else
            {
                if (!vis[t.a][0])q[len++]=opt(t.a, 0, 'd', '2', '2', first - 1, t.cnt + 1), vis[t.a][0] = true;
                if (!vis[0][t.b])q[len++]=opt(0, t.b, 'd', '1', '1', first - 1, t.cnt + 1), vis[0][t.b] = true;
                if (!vis[t.a][B])q[len++] = opt(t.a, B, 'f', '2', '2', first - 1, t.cnt + 1), vis[t.a][B] = true;
                if (!vis[A][t.b]) q[len++] = opt(A, t.b, 'f', '1', '1', first - 1, t.cnt + 1), vis[A][t.b] = true;
                int ta=(t.b-(A-t.a)>=0?A:t.a+t.b), tb=(t.b-(A-t.a)>=0?t.b-(A-t.a):0);
                if (!vis[ta][tb])q[len++] = opt(ta, tb, 'p', '2', '1', first - 1, t.cnt + 1), vis[ta][tb] = true;
                ta = (t.a - (B - t.b) >= 0 ? t.a - (B - t.b) : 0), tb = (t.a - (B - t.b) >= 0 ? B : t.b + t.a);
                if (!vis[ta][tb])q[len++] = opt(ta, tb, 'p', '1', '2', first - 1, t.cnt + 1), vis[ta][tb] = true;
            }
        }
        if (flag)
        {
            printf("%d\n", ed.cnt);
            Print(first - 1);
        }
        else printf("impossible\n");
    }
    return 0;
}