#include<iostream>
#include<vector>
using namespace std;
int mp[5][5];
struct node
{
    int r;
    int c;
    int pre;
    node(int rr=0,int cc=0,int pp=0):r(rr),c(cc),pre(pp){ }
};
bool vis[5][5];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
vector<node>q;
void Print(int id)
{
    if (id == 0) printf("(0, 0)\n");
    else if (id != 0)
    {
        Print(q[id].pre);
        printf("(%d, %d)\n", q[id].r, q[id].c);
    }
}
void BFS()
{
    q.push_back(node(0, 0,0));
    vis[0][0] = true;
    int first = 0, len = 1;
    while (first!=len)
    {
        node t = q[first];
        first++;
        if (t.r == 4 && t.c == 4)
        {
            Print(first - 1);
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int tr = t.r + dx[i];
            int tc = t.c + dy[i];
            if (tr < 5 && tr >= 0 && tc < 5 && tc >= 0)
            {
                if (mp[tr][tc] != 1 && !vis[tr][tc])
                {
                    vis[tr][tc] =true;
                    q.push_back(node(tr, tc,first-1));
                    len++;
                }
            }
        }
    }
}

int main()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            scanf("%d", &mp[i][j]);
        }
    }
    BFS();

    return 0;
}