#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
char v[35][35][35];//[k][i][j]第k层第i行第j列
struct node
{
    int k;
    int r;
    int c;
    int steps;
    node(int kk = 0, int rr = 0, int cc = 0,int ss=0):k(kk),r(rr),c(cc),steps(ss){ }
};
node st, ed;
int L, R, C;
int dr[] = {1,-1,0,0,0,0};
int dc[] = {0,0,1,-1,0,0};
int dl[] = {0,0,0,0,1,-1};
int main()
{
    while (~scanf("%d%d%d",&L,&R,&C))
    {
        if (L == 0 && R == 0 && C == 0)break;
        for (int k = 0; k < L; k++)
        {
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    cin >> v[k][i][j];
                    if (v[k][i][j] == 'S') st.k = k, st.r = i, st.c = j,st.steps=0;
                    if (v[k][i][j] == 'E') ed.k = k, ed.r = i, ed.c = j;
                }
            }
        }
        //BFS
        queue<node>q;
        q.push(st);
        v[st.k][st.r][st.c] = '#';
        bool Find = false;
        while (!q.empty())
        {
            node cur = q.front();
            q.pop();
            if (cur.k == ed.k&&cur.r == ed.r&&cur.c == ed.c)
            {
                ed.steps = cur.steps;
                Find = true;
                break;
            }
            int stp = cur.steps;
            for (int i = 0; i < 6; i++)
            {
                int tr = cur.r + dr[i];
                int tc = cur.c + dc[i];
                int tl = cur.k + dl[i];
                if (tr >= 0 && tr < R&&tc >= 0 && tc < C&&tl >= 0 && tl < L&&v[tl][tr][tc] != '#')
                {
                    q.push(node(tl, tr, tc, stp + 1));
                    v[tl][tr][tc] = '#';
                }
            }
        }
        if (Find) printf("Escaped in %d minute(s).\n", ed.steps);
        else printf("Trapped!\n");
    }
    return 0;
}